# Branch Predictor CS204

The project contains a program that applies four differnet branch prediction algorithms to a program run trace and give the accuracy of the chosen prediction model along with its branch target buffer. It is a part of the CS204 - Computer Architecture course being taught under Prof. T.V. Kalyan and Prof. Neeraj Goyal at IIT Ropar. The language used in the program is **C++ version 20** and can be compiled using **g++ compiler version 13+**.

## Authors

- [@shivambhagat79](https://www.github.com/shivambhagat79) Shivam Bhagat (2022CSB1123)
- [@saharsh18](https://github.com/saharsh18) Saharsh Saxena (2022CSB1116)
- [@Pratibha0934](https://github.com/Pratibha0934) Pratibha Garg (2022EEB1204)

## Compiling and running the program

The program can be run by using the following commands.

For Compiling the program, use the following command in the terminal in the folder where the files are stored.

```bash
g++ branchPredictor.cpp
```

To run the program, run the following command.

```bash
<!-- for Linux/Mac -->
./a.out

<!-- For windows -->
./a.exe
```

## Usage Instructions

- At the beginning, the program will ask for the name/location of the trace file you want to run the prediction models on.
- Place the trace file in the same or any directory nad enter its name/location.
- The trace must have the follownig format:

  core 0: Program Counter (Instruction code) Instruction command

  For example :

  core 0: 0x80004938 (0x00442803) lw a6, 4(s0)

  NO OTHER FORMAT IS ACCEPTABLE BY THE PROGRAM.

- After this, the program will ask for which prediction model to run. Enter the option from the given menu and press enter.
- The output will be shown in the terminal which will show the accuracy of prediction model along with the Branch Target Buffer of each branch command.
