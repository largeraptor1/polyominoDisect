# Polyomino Grid Enumeration

This code repo has the functionality for enumerating NxN polyomino grid coverings for all values of N from 1 to 7.
The value for N is currently capped at 7 due to the 64 bit-masking used to find full covers as quickly as possible (I think this could be somewhat easily fixed by just adding an additional integer for each polyomino placement to store grid cells >= 64).
The repo builds off of the libexact software for combinatorial exact covering problems. 

Important notice: Multi-processing is used for value N > 3, so how well this program functions will depend significantly on your local device's core count.

Installation and usage Instructions: 
1) Clone the repo to your local system.
2) Ensure you are in a Linux environment with make and gcc installed, then run the 'make' command
3) Open covers.c, change the value for P to the desired polyomino size you want.
4) Run the command './covers' to start the polyomino grid covers enumeration.

Upon completion of the enumeration, information will be printed to the command line like so:

Count of polyomino positions = *number*<br>

** Eliminating the invalid polyomino positions **

total valid polyomino positions: *number*<br>
Total unique covers: *number*<br>
TBA ... skipped, covp set to copp = *number*<br>
CPU time = *time in seconds*<br>

Note: the CPU time is incorrect for values of P < 3 due to multi-processing.
For the correct run-time, you can the program with the time command like so: 'time ./covers'
