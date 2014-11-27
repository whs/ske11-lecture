# Comp Arch Lecture 11 - 26 November 2014

## Cache performance

The CPU time when taking cache performance in is = IC * (CPI + memory stall cycles) * CC. The brackets here is called stalled CPI.

For write-through cache the memory stall cycle = miss rate * miss penalty. Normally the miss penalty is measured in the number of clock cycles so the problem is when we have CPU with faster clock rate the miss penalty here will increase.

For example if CPI = 2, 100 cycle miss penalty, 36% load-store instructions and 2% instruction memory miss 4% data memory miss:

Memory stall cycle = 2% * 100 + 36% * 4% * 100 = 3.44 so stalled CPI = 2+3.44 = 5.44

If the ideal CPI is reduced be much less then the memory stall cycle will starting to get more visible.

## Reducing miss rate

The access time of memory is hit time + miss rate * miss penalty and we want this access time to be small.

First we want to improve the miss rate:

### Set associative cache

- If we use direct mapped cache (a memory block maps to only 1 cache block) we might get a ping-pong effect where several memory block are competing for only one block when the cache is not distributed enough
- We also can use fully associative cache where memory blocks can be placed anywhere.
- Another way which combines these together is to dividing cache to n slots (called n ways). A memory block is mapped to any of the slot (similar to fully associative cache) and then inside the slot the block location will be determined by a function (like modulo the memory block with number of set in a slot -- similar to direct mapped cache). This is called **set associative cache**

In set associative cache when searching for memory we have to search in every slots but the set inside the slot is fixed. We need a hardware to perform this search in parallel for every slots.

To place a block inside set associative cache when a miss occur, we consider the least recently used (LRU) policy. In this policy, the block that get replaced by a new block is the block that was unused for the longest time.

The cons of this techniques is if we have n ways we have to have n comparators and LRU is costly to implement if there are so many slots.

### Multi level cache

In computers nowadays we have several cache already from L1, L2 and sometimes L3. Sometimes these cache may store only data or instruction or sometimes both together which is called unified cache (L2 normally is a unified cache).

For example, if CPI = 2, 100 cycle miss penalty, 36% load-store instructions, 2% L1 instruction memory misses, 4% L1 data memory misses, Unified L2 has 25 cycle miss penalty and 0.5% miss rate

Stalled CPI = 2 + 0.02 * 25 + 0.36 * 0.04 * 25 + 0.005 * 100 + 0.36 * 0.005 * 100 = 3.54

(In this case if there is no L2 the stalled CPI will be 5.44)

----

L1 and L2 has different goals:

- L1 is primary cache focused on minimizing hit time
- L2 is secondary cache focused on reducing miss rate