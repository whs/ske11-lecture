# ADT Lecture 12 - 3 November 2014

## Splay tree

	     Y
	    / \
	   X    (C)
	 /  \
	(A) (B)

Note that A, B, C are subtrees.

From this we can infer that`X`<`Y`, `A`<`X`<`Y`, `X`<`B`<`Y`, `C`>`Y` from the properties of BST.

From this BST we can build a splay tree by performing **tree rotation**. To rotate the tree *right* at `X` we will get:

	     X
	  /  | \
	(A) (B)  Y
	         |
	        (C)

Since `B` > `X` and `B` < `Y` we can put `B` in the left subtree of `Y`

	    X
	   / \
	(A)  Y
	    /  \
	   (B) (C)

### Zig-zag

Suppose we have a tree

	     G
	    /  \
	   P   (D)
	  / \
	(A)  X
	    / \
	  (B) (C)

When we search for `X` in a splay tree we want to bring `X` to the top to speed up subsequence calls without adding a cache by doing tree rotations or **zig-zag operations**. In this case, `X` is the right child of `P` so we move X up by doing left rotation at `X`:

	        G
	      /  \
	     X   (D)
	    / \
	   P   (C)
	  / \
	(A) (B)

Then do a right rotation at `X`:

	       X
	     /   \
	    P      G
	   / \   /  \
	(A) (B) (C)  (D)

Similarly, if `X` is the left child of right child we rotate X right then left.

	Original:

	   G
	  / \
	(D)   P
	     / \
	    X  (A)
	   / \
	 (C) (B)

	Rotate right:

	   G
	  / \
	(D)   X
	     / \
	    (C) P
	       /\
	     (B) (A)

	 Rotate left:

	       X
	    /     \
	   G       P
	  / \     / \
	(D) (C) (B) (A)

### Zig-zig

If `X` is the left child of left child, we perform a **zig-zig operations**: rotate `G` right then rotate `P` right

	Original:

		   G
	     /  \
	    P   (D)
	   /  \
	  X   (C)
	 /  \
	(A) (B)

	Rotate G right:

	       P
	     /   \
	   X       G
	  / \     / \
	(A) (B) (C) (P)

	Rotate P right:

	  X
	  /\
	(A) P
	   / \
	  (B) G
	     / \
	   (C)  (D)

### Zig

If `P` which is parent of `X` is at the root

	     P
	    / \
	   X  (C)
	  / \
	(A) (B)

Rotate X right:

	  X
	 / \
	A   P
	   / \
	 (B) (C)

### When to use what

1. Zig-zag
  - X is **left** child of **right** child
  - X is **right** child of **left** child
2. Zig-zig
  - X is **left** child of **left** child
  - X is **right** child of **right** child
3. Zig
  - X is direct left or right child of the root

### Example

	  11
	  /\
	 1 12
	 /\
	0  9
	   /\
	  3 10
	 /\
	2 5
	 / \
	4   7
	   /\
	  6  8

Here we want to bring 7 to the root.

	Zig-zig:

	    5
	   /  \
	 3     7
	 /\   /\
	2  4 6  8
	(tree root omitted)

         11
         / \
        1  12
       / \
      0   9
         /\
	    7 10
	   /\
	  5  8
	  /\
	 3  6
	 /\
	2  4

	Zig-zag:

	   1
       /\
	  0  7
        /   \
	   5     9
	  / \    /\
	 3   6  8  10
	 /\
	2   4
	(root of tree omitted)

	     11
	     / \
	    7   12
	  /  \
	 1    9
	 /\   /\
	0  5 8  10
	  / \
	  3  6
      /\
	 2  4

Since 7 is next the root, the next operation is zig

	Zig:

	      7
	    /   \
	  1       11
	 /\       /\
	0  5     9  12
	   /\   /\
	  3  6 8  10
	 /\
	2  4

We can sort this by doing a in-order traversal: ((0) 1 ((2 3 4) 5 (6))) 7 ((8 9 10) 11 (12))

## Deleting from splay tree

To delete from splay tree, we perform normal BST removal then splay the parent of the removed node. For example if 2 is removed from the following tree, 4 will be *removed* to be the new root and the parent of 4 in the old location (5) get splayed.

	Original:

	 2 
	 /\
	1  7
	  /\
	 5  8
	 |
	 4

	Removed:

	 4
	 /\
	1  7
	   /\
	  5  8

	Splay:

	  4
	 /\
	1  5
	   |
	   7
	   |
	   8

	  5
	 /\
	4  7
	|  |
	1  8

## Bag interface

```java
interface Bag<E> {
	void insert(E obj);
	E extract(); // extract some element
	boolean isEmpty();
}
```

Eg. Stack, Queue, PriorityQueueRobots & c

## Priority queue

Priority queue is a bag which items are comparable. The priority of items does not depend on the value of the item but the context. Items which has *less* value has *more* priority.

Priority queue is used in: job scheduling (Operating system scheduling jobs -- priority = arrival time), airline check-in process (priority = class, same class = FIFO)

## Heap

Heap is a concrete data structure that can be used to implement priority queues. Insertion and removal from heap takes O(log n) time and to process n elements it takes O(n log n).

Note that this heap data structure is not related with heap memory.

Heap is a binary tree (not BST!) that is complete (have all levels filled up except for the very last level) and every nodes obeys to the heap property.

The heap property is that the least (highest priority) element of any subtree is found at the root of that subtree.

Example of heap:

	          4
	        /   \
	      6        14
	    /  \       /\
	  21     8    19 35
	  / \   / \   |
	22  38 55  10 20

Example of heap data: ages of people in a family tree, salary of employees

The example heap can be stored in an ArrayList where children of node `n` is found at index 2n+1 and 2n+2. Thus the array will be: 4, 6, 14, 21, 8, 19, 35, 22, 38, 55, 10, 20

### Heap insertion

To insert element into heap, just add it to the end of the list. However, if it violates the heap property it must be bubbled upwards with upper elements coming down to replace the element's old position.
