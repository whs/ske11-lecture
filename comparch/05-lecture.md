# Performance - Comp Arch lecture 5 - 1 October 2014

How to compare performance between computers?

1. Response time (latency) - How fast is applications are ran
2. Throughput or execution rate - How many jobs can be done in a time period

If we add more machines, we improve the throughput but not latency. If we upgrade the CPU, the response time is improved and also the throughput.

## Execution time

Execution time is how long a program takes to execute. Measuring this can be done by many ways

- Elapsed time/wallclock time: compute the difference between the time of program start and stop. This would be useful if you're the only user in the system. It takes I/O time in consideration too which can be both good (like disk I/O) and bad (like waiting for user's input).
- CPU time/execution time: The time a program occupy the CPU not counting the time waiting for I/O. Can be seperated to:

For example, our program runs in machine A in 20s and in machine B in 25s. Thus machine A is faster.

Comparing the execution time:

- performance = 1/execution_time
- performance[x]/performance[y] = execution_time[y]/execution_time[x] = n

CPU execution time can be computed by measuring the number of clock cycles elapsed.

- CPU execution time = clock_cycles * clock_cycle_time
- CPU execution time = clock_cycles/clock_rate

Thus to minimize execution time we need to buy CPU with faster clock rate or optimize our application to use less clock cycles.

Different instructions use different clock cycles.

## Cycles

A program will use some instructions, cycles and seconds.

- CPI is the cycles taken to run one instructions. Normally we use the average number
- MIPS stands for million instructions per second.

for example, machine A has cycle time of 10ns, CPI 2 and machine B has cycle time of 20ns and CPI 1.2. A is faster. (multiply the numbers together)

If the two machines have the same instruction set the number of instructions and CPI should be the same.

A machine may have multiple type of instructions. Suppose that we have 3 classes each can take different amount of cycles. We can compare two code's run speed by taking this cycle amount for each instructions in consideration.

So,

- CPU time = instruction_count * cpu / clock_rate

For example,

Op    | Freq    | CPI  | Freq * cpi
------|---------|------|-------------
ALU   | 50%     | 1    | 0.5
Load  | 20%     | 5    | 1.0
Store | 10%     | 3    | 0.3
Branch| 20%     | 2    | 0.4
------|---------|------|-------------
      |         |      | sum = 2.2

If we add a better cache that make load time from 5 to 2, the average CPI will become 1.6, 2.2/1.6 = 37.5% faster execution.

If we use a branch predictor (a system that try to predict and preload the branch target beforehand to save loading time after jumping), the branch can probably be twice faster (take 1 CPI) and it make our computer 2.2/2.0 = 10% faster

If we make that the ALU can execute two instructions at once (CPI = 0.5), 2.2/1.95 = 12.8% faster.

Thus in this example if we have to chose one we will add a better cache so that it runs 37.5% faster
