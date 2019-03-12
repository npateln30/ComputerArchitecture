# ComputerArchitecture
C Programming projects from Rutgers University CS211 (Computer Architecture)

## Overview
There were a total of 5 projects in CS211 (Computer Architecture) at Rutgers
University. Only 4 are listed here since the 3rd project was done remotely, due to
the nature of the project.

Projects are specified by the name convention: 
`pa2` (Project Assignment 2)

---
## Project Assignment 1 [(pa1)](pa1)
### gcd.c
Returns the greatest largest denominator for two integer arguments
Example: `./gcd 445 25` returns `5`

### rle.c
Compresses a string based on the number of consecutive letters
Example: `./rle aaaabbc` returns `a4b2c1`

### rot13.c
Encodes a string by shifting each letter by 13 characters.
Example: `./rle tester` returns `grfgre`

---
## Project Assignment 2 [(pa2)](pa2)
### bst
C implementation of a Binary Search Tree, with the following functionalities:
* Printing
* Node Creation
* Insertion
* Deletion
* Search

### life
Simple C implemention of Game of Life. Generates a board of "organisms" in "colonies", based on game rules and a given number of generations (rounds).

### llist
C implementation of a Linked List, with the following functionalities:
* Printing
* Insertion
* Deletion
* Search

### mexp
Reads a matrix through a file, and uses linear algebraic principles to raise a matrix by a given power (example: raises given a `5x5` matrix to the 6th power)

### queens
Evaluates a chess board consisting of only a given number of queens in specific positions, to see if there can be any moves to eliminate another queen. Also includes a Warrior Queen, a special type of queen that has additional movement patterns.

### stddev
Takes in a list of numbers, and finds the mean and standard deviation of the set.

---
## Project Assignment 4 [(pa4)](pa4)
### truthtable.c
Project 4 involves reading and interpreting a written circuit diagram. Specific directives are written in a file, and the program reads and interprets the directives, producing a truth table with the various inputs and their respective outputs, based on the circuit diagram. Includes support for the following logical circuit components:
* NOT, AND, OR, XOR
* NAND, NOR, PASS
* DECODER
* MUX

---
## Project Assignment 5 [(pa5)](pa5)
### cachesim.c
PA5 is a cache simulator, which reads a file and simulates the cache fetching, reading, and writing process. It returns the simulated number of reads, writes, and cache hits and cache misses done during the simulation.




