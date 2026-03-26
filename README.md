# polyominoDisect

This code repo has the functionality for enumerating NxN polyomino grid coverings for all values of N from 1 to 7.
The value for N is currently capped at 7 due to the 64 bit-masking used to find full covers as quickly as possible (I think this could be somewhat easily fixed by just adding an additional integer for each polyomino placement to store grid cells >= 64).
The repo builds off of the libexact software for combinatorial exact covering problems.


Installation and usage Instructions: 
1) Clone the repo to your local system.
2) Ensure you are in a Linux environment with make and gcc installed, then run the 'make' command
3) Open covers.c, change the value for P to the desired polyomino size you want.
4) Run the command './covers' to start the polyomino grid covers enumeration.
