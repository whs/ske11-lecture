# ADT Lecture 11 - 20 October 2014

## Queue

Queue is a form of list similar to stack but is FIFO (first-in, first-out). In other words, the data in the queue get treated fairly as when they come first, they will get served first.

```java
public interface QueueOfStrings {
	// create an empty queue
	public QueueOfStrings();
	// insert new string into queue
	public void enqueue(String item);
	// remove and return the first string added
	public String dequeue();
	// is the queue empty
	public boolean isEmpty();
	// number of string on queue
	public int size();
}
```

Inside the implementation they will be a pointer to first and last node of the linkedlist

```java
public class LinkedQueueOfStrings {
	private Node first, last;
	private class Node {
		String item;
		Node next;
	}

	public boolean isEmpty(){
		return first == null;
	}

	public void enqueue(String item){
		// operate on last item
		Node oldlast = last;
		last = new Node();
		last.item = item;
		last.next = null;
		if(isEmpty()){
			// special case
			first = last;
		}else{
			oldlast.next = last;
		}
	}

	public String dequeue(){
		// operate on front item
		String item = first.item;
		first = first.next;
		if(isEmpty()){
			// special case
			last = null;
		}
		return item;
	}
}
```

## Binary search tree and quick sort

To sort with BST:

1. BST insertion
2. In-order traversal -- travese in following order: recurse left, self, recurse right

	6 10 13 5 8 3 2 11

	1. Build BST

	(How to do insertion see lecture 9)

	6
	| \
	5  10
	|  / \
	3 8  13
	|     |
	2     11

	2. In-order traversal

	2 3 5 6 8 10 11 13

The running time of this algorithm is depending on running time of BST build operation. Each item needs to do O(n) comparison with existing items thus the total running time is O(n^2). This only happen if the list is turned out to be a linked list with only one branch on every nodes.

But in the best case if the tree is really balanced, the comparison only need to done to half of the tree thus there will be only O(log n) comparisons and O(n log n) total running time.

In the balanced tree with n nodes there will be log n (base 2) levels.

## QuickSort

To sort 6 10 13 5 8 3 2 11

1. There is a pivot element: 6
2. For every elements if it is less than pivot, move it to the left otherwise move it to the right: [5, 3, 2] 6 [10, 13, 8, 11]
3. For every subgroup, recurse
   3.1. For left:
       3.1.1. Pivot: 5
       3.1.2. 2 5 3
   3.2. For right:
       3.2.1. Pivot: 11
       3.2.2. [8 10] 11 13
       3.2.3. Recurse on the left so that we get 8 10

So to code this, we have 3 pointers: pivot, `i`, `j`.

- For each item, if it is greater than the pivot advance `j`.
- If it is less than the pivot, advance the `i` pointer and swap data pointed by `i` and `j`
- Thus the area next to pivot up to `i` is less than the pivot and the rest is greater than the pivot.
- Then we swap data pointed by `i` with the pivot so the pivot is in the middle.