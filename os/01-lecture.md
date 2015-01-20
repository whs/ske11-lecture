# OS Lecture 1 - 16 Jan 2015

OS is a software that is an interface between software and hardware. The goals is to run users' program and make computer convenient to use and manage hardware in an efficient manner.

What OS does?

- From the user perspective it gives them convenience. They doesn't care about resource utilization but only performance.
- In shared computer OS must manage resource sharing so that every users are happy
- So, OS is a resource allocator that manage resource requests and conflicts
- And OS is a control program that prevent errors and provide security in the system.

In hardware the CPU can read data from other hardware by doing interrupts. Modern hardware has "DMA" (direct memory access) so other hardware can write to the memory directly and skip the CPU to be faster.

Most computer nowadays are general purpose and also use general purpose processor. Multiprocessor system is more popular (> 1 processors, not > 1 cores). There is two type of multiprocessing:

- Asymmetric multiprocessing - each CPU can do seperate tasks like hardware interrupts, IO (appear in large scale computer)
- Symmetric multiprocessing - all CPU perform same kind of tasks (our PC use this)

Nowadays we have clustered system (a.k.a. web scale) that use software to coordinate between several computers. It might use SAN or storage area network. It make computing "highly-available" - have high uptime. It has two style: aymmetric (one working, one standby) and symmetric (all nodes run tasks and monitoring each others)

Hardware is driven by interrupt. Software also has interrupt such as exception