# Computer Architecture lecture 8

## MIPS Pipelining Basic

In single cycle design the system have to wait for instructions to complete before proceeding. This can be improved by performing other instruction that does not use the unit that is processing current job at the same time. This is called superscalar.

For example, in laundry you have the washing machine, drying machine, folding, storing. Instead of doing one at a time you can allow other jobs to use the machine that you doesn't use at the moment so everyone finish earlier.

This is normally done by splitting a cycle to two half -- first and last.

The MIPS datapath is modified to accomodate this by having *state registers* between each pipeline stage.

## Structure hazard

Sometimes there is a conflict when using same resource at the same time such as if we have a single memory, it could be that in the same time an instruction tries to read data from the memory while another instruction just ran tries to fetch the instruction from the memory.

Normally this is solved by delaying other instructions that tries to do this or seperating the memory to data memory and instruction memory.

## Data hazard

If we have a statements that write to register and another one tries to read from the same register, the read might be ran before the write occured. This is called read before write.

One way to fix this is to add a new instruction "stall" that pause operation in that cycle. The problem with this technique is that it will decrease CPI.

Another way commonly used to fix this is forwarding the result as soon as it is available to the next instructions that requires it. This still requires stall in some cases as we cannot send data backwards in time.

## Control hazard

Control/Branch hazard is the worst one. When branch instruction encountered you cannot know the next instruction beforehand and we have to stall the operation until the branch is resolved.

The compiler can help avoiding this by untaken branch prediction. The compiler will assume that the branch is not taken then put the related code next to the branch operation.