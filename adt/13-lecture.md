# ADT Lecture 13 - 10 November 2014

## Heap

Continued from last lecture.

### Inserting to heap

To insert new item to the heap, the heap property must always be honored.

The insert operation is O(log n) as the tree is balanced.

```java
public void insert(E obj){
	super.add(obj); // add to end of array
	rotateUp(size() - 1);
}
private void rotateUp(int index){
	if(index == 0){
		return;
	}
	int parent = (index - 1)/2;
	if(elementAt(parent).compareTo(elementAt(index)) <= 0){
		// the new child is already at its position
		return;
	}
	// otherwise swap the child with its parent then rotate again
	swap(index, parent);
	rotateUp(parent);
}
```

### extract

Remove the highest priority element from the heap (the root). This can be done quickly, but the root must be refilled.

The extract time is O(log n)

```java
public E extract(){
	if(size() == 0){
		return null;
	}
	setElementAt(elementAt(size() - 1), 0);
	setSize(size() - 1);
	rotateDown(0);
	return temp;
}
private void rotateDown(int index){
	int child = 2*(index+1); // right child
	if(child >= size() || elementAt(child-1).compareTo(elementAt(child)) < 0){
		child -= 1; // choose left child instead
	}
	if(child >= size()){
		return;
	}
	if(elementAt(index).compareTo(elementAt(child <= 0)))
		return
	swap(index, child);
	rotateDown(index+1);
}
```

### Heapsort

We can sort an array by inserting the members into a heap (O(n log n)) then extract from the heap repeatedly (O(n log n)). 

## Symbol table

Symbol table is a table which has key and value pairs which is optimized for fast lookup. i.e. if you know the key the value can be found quickly without searching the entire table.

The operation in a symbol table are:

- put(key, val)
- get(key)
- delete(key)
- contains(key)
- isEmpty()
- size() : number of pairs
- keys() : all the keys

The assumptions:

- Value can be any type but null
- Keys should be immutable.
- Keys implements equals correctly:
  - Reflexive: `x.equals(x)` is `true`
  - Symmetric: `x.equals(y)` iff y.equals(x)
  - Transitive: if `x.equals(y)` and y.equals(z) then `x.equals(z)`
  - Non-null: `x.equals(null)` is `false`

Few tips for implementing equals correctly:
- Optimize by checking reference equality
- Check against null
- Check whether two objects are the same type
- Compare each fields
  - Use `==` for primitive types
  - Use `equals()` for object types
  - Apply these techniques to each elements if the type is array or use `Arrays.equals(a, b)` or `Arrays.deepEquals(a, b)`

We can use LinkedList to implement key, value but we have to search the list almost entirely every time we access it. Thus the worst case running time is O(n) and the average case is O(n/2) for searching.

We then can speed up the lookup by using ordered array then use binary search to search for it. (A binary search is to choose a pivot then split array to two half, one greater than the pivot then look in the appropriate subarray recursively depending on the search value is greater or lesser than the pivot) The problem is when we're going to insert new item we have to shift all greater keys so it would still take O(n) time.

We can use spray tree for this, where insertion and search takes O(log n).

## Hashing

The idea of hash table is to save item in key-indexed table. The key is put through a hash function to get an integer value which is the storage location of that key.

The problem is hash collision when two input to hash function returns same value which comes from space-time tradeoff where function has unlimited number of input but limited output (as the hash table storage space is limited).

A good hash function is fast (such as functions that operate on bits) and distribute its output evenly throughout our space. The best hash function is different for every data set.

## Hashcode

In Java, all classes inherit a method `hashCode()` from `Object` which returns the hash value of this object as 32 bit int. The requirement is if `x.equals(y)` then `x.hashCode() == y.hashCode()`. `!x.equals(y)` then `x.hashCode() != y.hashCode()` is not required, but highly desired (in other words, the hash should not have collisions). The default Java implementation returns the memory address of the object.

One way to write your own hashCode:

```java
public int hashCode(){
	int hash = 17; // nonzero constant
	// 31 is a small prime
	hash = 31*hash + field1.hashCode();
	hash = 31*hash + field2.hashCode();
	return hash;
}
```
