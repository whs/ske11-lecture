# Computer Organization Lecture 6 - 8 October 2014

Average execution time is called arithmetric mean (AM)

AM = (1/n) * sum of execution time

Where n is the number programs ran

Example of benchmarks from spec.org:

- Integer benchmark
  - gzip
  - gcc
  - chess program
- Floating benchmark
  - facial image recognition

Other performance metrics:

- Power consumption (affects battery life)

So, the metrics are:

- Design metrics: is the hardware viable? is the programming of the machine easy?
- Static metrics: the program memory footprint
- Dynamic metrics: execution time, *real* instruction count (some commands generated multiple instructions)

## Processor

CPU operation are divided to:

- Fetch: Get an instruction from memory
- Decode: Interpret instruction
- Execute

The program counter (PC) is a special register which stores the current address of the current executing instruction.

## Clocking

ALU operation should fit in one cycle. In each cycle the ALU will read from a state element (register-like element), perform computation and write back to state element.

## Fetch instruction

Fetch is to get one instruction from memory specified by PC then increase the PC to the next instruction (4 bytes or 32 bit)

## Decode

After we fetch an instruction, we try to read the operand by going to the register file. (eg. in R type the operands are op, rs, rt, rd, shamt and funct) then perform the operation `op`, `funct` in `rs`, `rt` then store back to register file.

## Single cycle design

In this design the cycle time is designed to accommodate the slowest instruction to perform every instructions in one cycle. There will be wasted time in this design, but it is the simplest design.

## Multicycle datapath

Let one instruction takes more than 1 cycle to complete by dividing it to multiple steps where each step take a cycle. Each steps should have balanced amount of work.

After a cycle ends, the values needed to be reused will be saved to an internal register to be used by later cycle.

## Exam

The exam will be from start until single cycle design.