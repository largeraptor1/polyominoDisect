
/* tiles.c  :  3 Dec 24 .. 4 Dec 24  :  Colin Ramsay */

/* Ex desk4-OptiPlex-9020/EXWORK/PC00328/Orig30Jun09/Archive1/poly/enum/ */
/**************************************************************************

	enum2.c		Colin Ramsay		28 April 2002

This is a very noddy implementation of the DH Redelmeier algorithm, as 
given, just to get us started.  There are no attempts at efficiency, just a
verbatim implementation. 

**************************************************************************/

#include <stdlib.h>          /* EXIT_SUCCESS ... */
#include <stdio.h>           /* printf() ... */
#include <time.h>            /* time() ... */

#define  True   1
#define  False  0

#define  Pmin  1
#define  Pmax  16

#define  P  4                /* `target' tile size */

int tile[P][2];              /* the tile's x/y coords */
int t[P+1];                  /* count of (fixed) tiles */

/* Note that x can run from -(P-2) to +(P-1) and y can run from 0 to +(P-1).  
With a 1 wide guard all round, we need -(P-1) .. +P and -1 .. +P.  So the 
indexing offsets are +(P-1) & +1.  We use -P as an end-of-stack value, since 
it's never used. */

int freept[2*P][P+2];        /* the free points - boolean */
int succpt[2*P][P+2][2];     /* the successor points - x/y */

#define  Xoff  (P-1)
#define  Yoff  1
#define  Eos   -P

void prtfree(void)
  {
  int x,y;

  for (y = P; y >= -1; y--)
    {
    for (x = -P+1; x <= P; x++)
      {
      if (y == -1)
        { printf(" -"); }
      else if (y == 0 && x < 0)
        { printf(" -"); }
      else if (x >= 0 && y >= P-x)
        { printf(" -"); }
      else if (x < 0 && y >= P+x)
        { printf(" -"); }
      else
        { printf(" %d", freept[x+Xoff][y+Yoff]); }
      }
    printf("\n");
    }
  }

void prttile(int tsiz)
  {
  int i,x,y;

  printf("# %d\n", t[tsiz]);
  for (y = P-1; y >= 0; y--)
    {
    for (x = -P+1; x <= P; x++)
      {
      if (y == 0 && x < 0)
        { printf(" -"); }
      else if (x >= 0 && y >= P-x)
        { printf(" -"); }
      else if (x < 0 && y >= P+x)
        { printf(" -"); }
      else
        {
        for (i = 0; i < tsiz; i++)
          {
          if (tile[i][0] == x && tile[i][1] == y)
            {
            printf(" X");
            break;
            }
          }
        if (i == tsiz)
          { printf("  "); }
          /*{ printf(" %d", freept[x+Xoff][y+Yoff]); }*/
        }
      }
    printf("\n");
    }
  }

/* tsiz is the size of the current tile at entry, and is thus the index for the 
point(s) to be added.  x/y are the point at the head of the untried stack. */

void recurse(int tsiz, int x, int y)
  {
  int i,ix,iy,tx,ty,cx,cy;
  int tl,tr,tu,td;

  /*
  printf("** %d:", tsiz);
  for (i = 0; i < tsiz; i++)
    { printf(" %d,%d", tile[i][0], tile[i][1]); }
  printf("  / ");
  ix = x;
  iy = y;
  while (ix != Eos && iy != Eos)
    {
    printf(" %d,%d", ix, iy);
    tx = succpt[ix+Xoff][iy+Yoff][0];
    ty = succpt[ix+Xoff][iy+Yoff][1];
    ix = tx;
    iy = ty;
    }
  printf("\n"); 
  */
  /*prtfree();*/
  

  /* Repeat until the untried set is exhausted ... */

  ix = x;
  iy = y;
  while (ix != Eos && iy != Eos)
    {

  /* 1. Remove an (arbitrary) element from the untried set ... */

    cx = succpt[ix+Xoff][iy+Yoff][0];
    cy = succpt[ix+Xoff][iy+Yoff][1];

  /* 2. Place a cell at this point ... */

    tile[tsiz][0] = ix;
    tile[tsiz][1] = iy;

  /* 3. Count this new polynomio ... */

    t[tsiz+1]++;

    /*
    printf("%d:", tsiz+1);
    printf("\n");
    for (i = 0; i <= tsiz; i++)
      { printf(" %d,%d", tile[i][0], tile[i][1]); }
    printf("\n");
    */
    if (tsiz == P - 1)
      {
      printf("\n");
      prttile(tsiz+1);
      }

  /* 4. If the size is less than P ... */

    if (tsiz < P-1)
      {

  /* (a) Add *new* neighbours to the untried set ... */

      if (freept[ix+Xoff][iy+Yoff + 1])
        {
        succpt[ix+Xoff][iy+Yoff + 1][0] = cx;
        succpt[ix+Xoff][iy+Yoff + 1][1] = cy;
        cx = ix;
        cy = iy + 1;

        freept[cx+Xoff][cy+Yoff] = False;
        tu = True;
        }
      else
        { tu = False; }
      if (freept[ix+Xoff + 1][iy+Yoff])
        {
        succpt[ix+Xoff + 1][iy+Yoff][0] = cx;
        succpt[ix+Xoff + 1][iy+Yoff][1] = cy;
        cx = ix + 1;
        cy = iy;

        freept[cx+Xoff][cy+Yoff] = False;
        tr = True;
        }
      else
        { tr = False; }
      if (freept[ix+Xoff - 1][iy+Yoff])
        {
        succpt[ix+Xoff - 1][iy+Yoff][0] = cx;
        succpt[ix+Xoff - 1][iy+Yoff][1] = cy;
        cx = ix - 1;
        cy = iy;

        freept[cx+Xoff][cy+Yoff] = False;
        tl = True;
        }
      else
        { tl = False; }
      if (freept[ix+Xoff][iy+Yoff - 1])
        {
        succpt[ix+Xoff][iy+Yoff - 1][0] = cx;
        succpt[ix+Xoff][iy+Yoff - 1][1] = cy;
        cx = ix;
        cy = iy - 1;

        freept[cx+Xoff][cy+Yoff] = False;
        td = True;
        }
      else
        { td = False; }

  /* (b) Call this algorithm recursively ... */

      recurse(tsiz+1, cx,cy);

  /* (c) Remove the new neighbours from the untried set ... */

      if (td)
        { 
        freept[cx+Xoff][cy+Yoff] = True;

        tx = succpt[cx+Xoff][cy+Yoff][0];
        ty = succpt[cx+Xoff][cy+Yoff][1];
        cx = tx;
        cy = ty;
        }
      if (tl)
        {
        freept[cx+Xoff][cy+Yoff] = True;

        tx = succpt[cx+Xoff][cy+Yoff][0];
        ty = succpt[cx+Xoff][cy+Yoff][1];
        cx = tx;
        cy = ty;
        }
      if (tr)
        {
        freept[cx+Xoff][cy+Yoff] = True;

        tx = succpt[cx+Xoff][cy+Yoff][0];
        ty = succpt[cx+Xoff][cy+Yoff][1];
        cx = tx;
        cy = ty;
        }
      if (tu)
        {
        freept[cx+Xoff][cy+Yoff] = True;

        tx = succpt[cx+Xoff][cy+Yoff][0];
        ty = succpt[cx+Xoff][cy+Yoff][1];
        cx = tx;
        cy = ty;
        }
      }

  /* 5. Remove newest cell ... */

    /* n/a */

    tx = succpt[ix+Xoff][iy+Yoff][0];
    ty = succpt[ix+Xoff][iy+Yoff][1];
    ix = tx;
    iy = ty;
    }
  }

int main(void)
  {
  int i, x,y;
  clock_t t1, t2;

  if (P < Pmin || P > Pmax)
    {
    printf("\n** tile size must be in %d-%d **\n\n", Pmin, Pmax);
    exit(EXIT_FAILURE);
    }

  for (i = 1; i <= P; i++)
    { t[i] = 0; }

  for (x = -P+1; x <= P; x++)
    {
    for (y = -1; y <= P; y++)
      {
      if (y >= 0 && x >= 0 && x <= P-1-y)
        { freept[x+Xoff][y+Yoff] = True; }
      else if (y >= 1 && x < 0 && x >= -P+1+y)
        { freept[x+Xoff][y+Yoff] = True; }
      else
        { freept[x+Xoff][y+Yoff] = False; }

      succpt[x+Xoff][y+Yoff][0] = Eos;
      succpt[x+Xoff][y+Yoff][1] = Eos;
      }
    }

  printf("\n# Tile size = %d\n", P);

  /* The initial untried stack (head) is (0,0), which is not free ... */

  t1 = clock();
  freept[0+Xoff][0+Yoff] = False;
  recurse(0,0,0);
  t2 = clock();

  printf("\n# tile counts = [");
  for (i = 1; i <= P; i++)
    { printf(" %d", t[i]); }
  printf(" ]\n");
  printf("# CPU time = %0.3fs\n", (double)(t2-t1)/(double)CLOCKS_PER_SEC);
  printf("\n");

  return EXIT_SUCCESS;
  }


