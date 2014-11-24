# Computer Organization & Architecture Lecture 10 - 19 Nov 2014

## Memory design

CPU are now faster and faster yet memory speed increases at slower rate than the CPU. This is called Neumann Gap and it is becoming worser as time passes.

Previously when we talk about CPI we didn't take memory speed in account. In the following lecture we are looking on how memory reduces CPI.

When accessing memory is slow, there is a cache that store some instructions to be able to access instructions faster. This is designed as "memory hierachy". There are several memories levels (L1, L2, main, secondary memory) that sit further more and more from the CPU and the size is also increasing thus far memory are slower.

This memory hierachy also has a properties of *inclusive*, which means that if a data is in L1, it will also be in all further memory levels and if a data is not in L1, it might be able to be found in further memory levels.

## Memory Technology

- SRAM (static)
  - Use for cache
  - More expensive
  - Fast
  - Larger than DRAM (6 transistors)
- DRAM
  - Slower
  - Holds more data
  - Data need to be refreshed regularly

## Accesing memory

If the memory we're accessing is not in the caches, we have to add several stalls to wait for memory access. This affects CPI greatly.

## Locality

- Temporal locality: Most recently accessed item is closer, faster
- Spatial locality: Block containing continuous data are placed together

## Hit & miss

- Hit: data is in the higher level memory
  - Hit rate: fraction of memory access which hit
  - Hit time: time to access data in higher level memory
- Miss: data is not in higer level, must be retrieved in lower level memory
  - Miss rate: 1 - hit rate
  - Miss penalty: Time to replace block in upper level + time to deliver memory block to CPU

## Mapping
- Direct map
  - For every item in lower level cache, there is only one location in the cache it must be put
  - Address: `block_addr % no_block_in_cache`