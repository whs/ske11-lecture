# Database lecture 5 - 3 April 2015

## Physical database design
Physical database is how the data in database are stored on a disk. Normally, database abstract the file out but we need to know the actual structure in order to optimize it.

### Storage level
Several records in a database (called logical record -- LR) can be stored in a file (called a physical record -- PR). The  logical records may not be from the same table to store in the same physical record.

You access one logical record at a time, which DBMS will access it from one physical record at a time. The physical record is cached in the memory of DBMS. If you try to access a record not loaded to memory, DBMS and OS will locate and read it to memory. The application doesn't need to explicitly request for this.

### Benchmark
Response time of database is hard to benchmark, so we measure resource usage such as physical record transfer, CPU and memory usage, network usage instead. To increase the response time we can minimize the memory and disk usage, reducing physical record access time and CPU usage. Joining table is one way that consume lot of resources.

### Database design decision
To optimize, we need some data such as

- Table profile: Summary of a table, their column and their relationships.
   - Table: number of row and physical record (DBMS can generate this)
- Application profile
  - Query: what queries are used, their frequency
  - Form: frequency of select/insert/delete operation

### File structure
- Sequential files
  - Simple
  - Used in the past
  - Data are stored in a file
  - Unordered (ordered by insertion time) or ordered by key
  - Fast insertion: just append it
  - Slow deletion: physical record must be reorganized
  - Fast sequential search, slow key search
- Ordered sequential file
  - On insert, reorganize the physical record by key
  - Slow insertion 
  - Lookup by key or sequential lookup is fast
- Hash file
  - Fast access by unique key
  - Map key to physical record address by hashing it (mostly by using mod)
  - Good hash function should distribute data evenly
  - If physical record for a hash value is full, a new file is created and linked to old one (like HashMap)
  - One problem is the data may be too full in one file, and other files are empty so it would be slow to access most data, so data file sometimes need reorganization
  - Slow sequential search
- BTree
  - Popular, supported by most DBMS
  - Balanced  tree so all leaf nodes can be accessed by O(height) equally.
  - Bushy: a node has large number of edges
  - We want a tree that has low height, so the tree must be bushy
  - Each node in a tree is a physical record. It contains key and a pointer to physical record of the data. A node is filled to a half (d keys, d+1 pointers) and up to full (2d key, 2d+1 pointers)
  - The tree dynamically changes when physical record are inserted/deleted.
  - Good performance on both sequential and key search
  - **You should practice tree balancing (see slide)**
  - Cost of insertion: Cost of finding nearest key + cost of changing node (or adding new level)
  - Logarithmic search cost
- B+Tree
  - Improved sequential and range search performance
  - All keys are stored redundantly in leaf nodes
  - Similar algorithm to BTree, but data is not deleted from leaf nodes, only copied to parent nodes.
 
### Index matching
When we know what kind of queries we'll going to use we can also determine its index. It can be unique or non-unique index.
 
For example, if we select by department a lot, we might add index for department column.
 
#### Bitmap index
Bitmap is a table of possible values, and if an key contains that value, the bit for that will be true.
 
It is useful for non-unique column with few values
 
#### Bitmap join index
A special type of bitmap that optimize for joining. It is more suitable for data in data warehouse (data that are never changed) as if a data is inserted the entire bitmap needs to be updated.
 
### Query optimization
Another way to increase performance is to write better queries. Some DBMS may optimize queries automatically. The DBMS also plan how to search physical records of it automatically.
  
#### Access plan
Access plan is a plan for accessing physical record  and joining algorithm (sort before/after join, etc). DBMS will generate several plans and automatically choose the best one for you. You also can explictly send access plan to  the DBMS.

#### Adding index
Adding correct type of index can help increase performance

- Clustering index: data are stored sequentially 
- Nonclustering index: data are stored non-sequentially

#### Denormalization
Sometimes too much normalization can also slow data. It is useful in data warehouse.

#### Raid
Optimizing physical record to align with RAID can be useful

#### Other
- Data warehouse: store data in summarized form
- Parallel computing