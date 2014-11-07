# ADT Lecture 12 (optional class) - 6 November 2014

Note that these are **not** on the exam.

In computer architecture, we look on how to improve the performance of the machine. Our algorithm might run in O(n^2) time, and we can look at the actual runtime as like the hardware multiply that by a constant. The goal of computer architecture is to reduce that constant to be closest to zero.

In data structure, we improve what inside the Big O itself so it becomes order of magnitude faster.

## Merge sort

Merge sort is O(n log n). It works by dividing the array to smaller array then perform it recursively. When we have sorted the smallest array we can merge two sorted array easily by pulling elements from array that has the smallest value.

We can also implement merge sort iteratively by using other sort algorithms. We split the arrays to several small arrays (not necessary of size 2, something like 4) then we use other sort algorithm to sort these small arrays then perform merge of all of them.

## Cache

There is a cache inside the processor, but it is rather limited compared to memory. Every time the processor have to access the memory it has to pause. So modern computing has memory as one of the large bottleneck.

So why don't we just increase the cache? In computer architecture, big things are slow. So a large cache is just another memory. In our computer the way it works is there are several in-CPU cache levels that are sitting further from the CPU.

We have two keywords to identify the data:

- Temporal locality: the data is probably get accessed again (eg. next loop is going to read it again)
- Spatial locality: the next data is probably nearby

If we want our application to be fast, we want the cache to be hit as much as possible. How the cache can be missed?

- Compulsory miss: the data is accessed for the first time (bound to happen)
- Capacity miss: the data is larger than the cache
- Conflict miss: multiple data are stored in the same place in the cache

Locality reduces cache miss as when we request things from the cache, we likely to request subsequence items in the near future too; so we can just fetch everything beforehand to reduce cache trips.