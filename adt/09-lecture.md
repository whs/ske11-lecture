# ADT Lecture 9 - 6 October 2014

## Insert operation into BST

	Building a BST from: 18 12 25 4 15 25 30 1 13 17

	1. Add root
	18

	2. Add 12 by comparing with the root. It is less than, so it goes to left subtree

	18
	|
	12

	3. Add 25

	 18
	 /\
	12 25

	4. Add 4

	 18
	 /\
	12 25
	|
	4

	5. Add 15

	   18
	   /\
	 12 25
	 /\
	4  15

	6. Add 25. It is duplicated with a node already in a tree. We have to decide to place equal item somewhere and in this case, left.

	   18
	   /  \
	 12   25
	 /\    |
	4  15  25

	7. And so on...

	     18
	   /    \
	 12     25
	 /\     / \
	4  15  25 30
	|  / \
	1 13 17

```java
public static TreeCell insert(int x, TreeCell T){
	if(T == null){
		return new TreeCell(x, null, null);
	}
	if(T.getDatum().compareTo(x) >= 0){
		// Recursive insert on T.left
		T.left = insert(x, T.left);
	}else{
		// Recursive insert on T.right
		T.right = insert(x, T.right);
	}
	return T;
}
```

## Delete operation from BST

Easy to perform if:

- X is a leaf
- X has 1 child
- X is not in the tree

The algorithm:

1. Search for X
2. Check for the easy cases
3. Otherwise use the smallest element in the right subtree to be the replacement

For example if we're removing 12:

	     18
	   /    \
	 12     25
	 /\     / \
	4  15  25 30
	|  / \
	1 13 17

	     18
	   /    \
	 13     25
	 /\     / \
	4  15  25 30
	|  |
	1  17

The reason we use the right subtree as they're all greater than the left subtree and the smallest element in the right subtree are less than other elements in the right subtree so it would produce a valid subtree.

## Stacks

Stack is similar to list, but the operations are performed at the top of the stack. Sometimes we call stack as LIFO list (last in, first out)

```java
public interface Stack {
	public void push(Object x);
	public Object pop();
	public Object peek();
	public boolean isEmpty();
	public void clear();
}

class ArrayStack implements Stack {
	private Object[] array;
	private int index = 0;
	public ArrayStack(int maxSize){
		array = new Object[maxSize];
	}

	public void push(Object x){
		array[index++] = x;
	}

	public Object pop(){
		return array[--index];
	}

	public Object peek(){
		return array[index-1];
	}

	public boolean isEmpty(){
		return index == 0;
	}

	public void clear(){
		index = 0;
	}
}
```

Stack can be used for storing function call frames, evaluation of postfix and converting prefix to postfix notation.

### Evaluating postfix

- 1 2 + 3 + 4 2 3 * - +
- Scan from left to right and add them to the stack
- [1, 2, +] = [3] on the stack
- [3, 3, +] = [6] on the stack
- [6, 4, 2, 3, *] = [6, 4, 6] on the stack
- [6, 4, 6, -] = [6, -2] on the stack
- [6, -2, +] = [4] on the stack