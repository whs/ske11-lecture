# Trees - ADT Lecture - 2 October 2014

Property of tree:

- Each cell may have 0 or more successors (children)
- Each cell must have only 1 parent except the *root* which have no parent.
- Every cell can be traced up to the root.

General tree:

	5
	|     \
	4      2
	|\ \
	7 8 9

Binary tree: Each cell must have at most 2 children which are called left child and right child.

	5
	|   \
	4    2
	|\ 
	7 8

Not a tree:

	5
	| \
	4  \
	|\ /
	7 8

List-like tree:

	5
	|
	6
	|
	8

## Terminology

	  M
	 / \
	G   W
	|\  |
	D J P
	|\  |\
	B H N S

- M is called *root*
- G is called *root* of the *left subtree* of M
- B, H, J, N, S are *leaves* (the nodes which have no successors)
- N is the *left child* of P; S is the *right child*
- P is the *parent* of N
- M and G are *ancestors* of D
- P is the *parent* of N
- M, G are *ancestors* of D
- P, n, S are *descendants* of W
- J is at *depth* 2 (depth is the number of step from the root, or number of edges in graph term)
- W is at *height* 2 (height is the length of longest path to a leaf)
- A collection of several trees are called *forest*

## Binary tree cell

```java
class TreeCell<T> { 
	private T datum;
	// if we have 1 child, one of these will be null
	private TreeCell<T> left, right;

	public TreeCell(T x) {
		datum = x;
	}

	public TreeCell(T x, TreeCell<T> lft, TreeCell<T> rgt) {
		datum = x;
		left = lft;
		right = rgt;
	}

	// getDatum, setDatum
	// getLeft, setLeft
	// getRight, setRight
}
```

## General Tree

We represent this by converting the tree to binary tree.

	    5
	   /  \
	  4    2 
	 /\ \
	7  8 9
	|\   |\
	7 8  3 1

	Converted:

	5
	|
	4 --> 2
	|
	7 --> 8 --> 9
	|           |
	7 --> 8     3 --> 1

We avoid using array to store the childrens as array have fixed size. Using linked sublings solve this problem similar to linked list.

```java
class GTreeCell {
	private Object datum;
	private GTreeCell left;
	private GTreeCell sibling;

	// getter and setters
}
```

## Application of tree

Programs are represented in the compiler as an "Abstract Syntax Tree".

Eg:

- `E` -> Integer
  - E can be integer
- `E` -> (`E` + `E`)
  - E can be string `'('` followed by an `E` followed by `'+'` followed by an `E` followed by `')'`
- Example of valid E
  - 2
  - (3+34)
  - ((4+23)+89)
  - ((89+23)+(23+(34+12)))
- Example of invalid E
  - (3
  - 3+4
  - 3+4+5

This tree structure of E also enforce the evaluation of expression from the deepest level up.

	  +
	 /  \
	+    89
	|\
	4 23    <- this level have to be computed first

Recursive is used to compute the result of this tree. The *base case* of recursion is when the tree is empty or the given node is a leaf (no children); otherwise we just recursively compute the result of left and right subtrees until we get the solution for the full tree.

The tree also can be used to generate prefix and postfix notation (normally we use infix notation, ((8-5)*((4+2)/3)). The prefix form is + - 8 5 / + 4 2 3 and the postfix form is 8 5 - 4 2 + 3 / * which is used by the computer)

To convert a tree to the prefix form:

```py
def process(node):e
	print node.datum
	process(node.left)
	process(node.right)
```

The tree above would be `+ + 4 23 89` in prefix form.

To convert a tree to the postfix form:

```py
def process(node):
	process(node.left)
	process(node.right)
	print node.datum
```

The tree above would be `4 23 + 89 +`. We can find the result of this expression by doing 4 + 23 then use the result to add with 89.

## Searching in a binary tree

```java
public static boolean treeSearch(Object x, TreeCell node) {
	// empty tree contains nothing
	if(node == null){
		return false;
	}
	if(node.datum.equals(x)){
		return true;
	}
	// we still have more leaves, search the left and right subtree
	return treeSearch(x, node.left) || treeSearch(x, node.right);
}
```

This search can be written recursively easier than iteratively.

## Binary Search Tree (BST)

If the tree are ordered (left node's datum will always come before the node itself, and the right node's datum will always come after the node itself)

	    5
	   / \
	 2    8
	 /\   /\
	0  3 7  9

```java
public static boolean treeSearch(Object x, TreeCell node) {
	if(node == null){
		return false;
	}
	if(node.datum.equals(x)){
		return true;
	}
	if(node.datum.compareTo(x) > 0){
		return treeSearch(x, node.left);
	}
	return treeSearch(x, node.right);
}
```

This search is only O(log n) as each comparison will cut out half of the tree.

To build a binary search tree, use similar algorithm to searching and put the item at the location where you cannot find anything.

## Tree traversal

Vising every nodes in the tree are called tree traversal. There are several ways to do this:

- Preorder traversal
  - Visit the node
  - Visit left subtree
  - Visit right subtree
- Postorder traversal
  - Visit left subtree
  - Visit right subtree
  - Visit node
- Level-order traversal
  - Does not use recursive, but a queue
