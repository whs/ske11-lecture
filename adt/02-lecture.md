# ADT Lecture 2

## Abstract Data Type vs. Data Structure

- Set is an **abstract data type** which is collection of *unique* items.
- Set can be *written* using array or sorted array **data structure**.
- Sorted array implementation of set is more efficient (i.e. use less time to run) in some operations
  - So we can say that some data structures are more efficient in certain operations than others to implement the same abstract data type

## Data Structure & Algorithms

- Algorithm utilize data structures
- Example of operations are
  - Insertion
  - Deletion
  - Search

### Sorting problem

Suppose we have a list of `6 5 3 1 8 7 2 4` (in arbitrary order) and we would like to sort the list in descending (largest to smallest) order.

- This example use list abstraction to represent the numbers as it allows duplicated elements

#### Array

- We can use array data structure to implement list abstraction
- We then apply bubble sort to the array

.

	Original:       6 5 3 1 8 7 2 4
	Compare 6 to 5: 6 5 3 1 8 7 2 4
	Compare 5 to 3: 6 5 3 1 8 7 2 4
	Compare 3 to 1: 6 5 3 1 8 7 2 4
	Compare 1 to 8: 6 5 3 8 1 7 2 4
	Compare 1 to 7: 6 5 3 8 7 1 2 4
	Compare 1 to 2: 6 5 3 8 7 2 1 4
	Compare 1 to 4: 6 5 3 8 7 2 4 1
	Now 1 is sorted and can be ignored
	Round 2:        6 5 3 8 7 2 4 1
	Compare 6 to 5: 6 5 3 8 7 2 4 1
	Compare 5 to 3: 6 5 3 8 7 2 4 1
	Compare 3 to 8: 6 5 8 3 7 2 4 1
	Compare 3 to 7: 6 5 8 7 3 2 4 1
	Compare 3 to 2: 6 5 8 7 3 2 4 1
	Compare 2 to 4: 6 5 8 7 3 4 2 1
	Now 1, 2 are sorted and can be ignored

Using bubble sort the list can be sorted `n` rounds to sort a list with `n` elements. We can see that bubble sort is **inefficient** solution.

#### Heap

- Heap is a complete binary tree (except for the bottommost level)
- The root must be greater than the children

List: 6 5 3 1 8 7 2 4

	Building a binary tree

	      6
	     / \
	    5   3
	   / \  | \
	  1   8 <-- Cannot be inserted (root must be greater than children), perform bubble operation

	      6
	     / \
	    8  <-- Still not valid
	   / \
	  1   5

	    8
	   / \
	  6   3
	 / \  | \
	1   5 7 <-- Swap

	    8
	   / \
	  6   7
	 / \  | \
	1   5 3  2
	|
	4 <-- Swap

	    8           Completed tree
	   / \
	  6   7
	 / \  | \
	4   5 3  2
	|
	1

After we built a tree we can read out the values by pulling the root element one by one, replacing it by the bottommost item then correcting the result to be a valid heap

	    .			Sorted: 8
	   / \
	  6   7
	 / \  | \
	4   5 3  2
	|
	1

	    1  <-- Cut out the bottommost item* to root and perform
	   / \     heap correction
	  6   7
	 / \  | \
	4   5 3  2

	* Item can be selected at random as it will be pushed back later

	Heap correction:

	    7			Sorted: 8
	   / \
	  6   1
	 / \  | \
	4   5 3  2

	    7			Sorted: 8 7
	   / \
	  6   3
	 / \  | \
	4   5 1  2  <-- Cut off 7 and select 2 to be the next root

	    6			Sorted: 8 7 6 ...
	   / \
	  5   3
	 / \   \
	4   2   1

The heap algorithm is faster as a list of a million items can be represented by a tree with around 20 levels. (2<sup>20</sup> = 1,048,576 items in full binary tree of 20 levels)