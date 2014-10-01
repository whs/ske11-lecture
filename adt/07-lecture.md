# ADT Lecture 7 - 25 September 2014

There is no universal implementation of data structures that would fit every use case and fast.

## Lists

List is the simplest data structure of all.

In some programming languages like Python, list can be a collection of mixed objects. In Java, list must contain elements of the same type.

Operations done on list:

- Create list
- Accessing and searching
- Insert item into list
- Remove item out of list

Ways to implement list:

- Arrays
  - Fast random access (can access any position in O(1) time)
  - Array have constant size, so inserting, deleting is difficult as it need compacting and expanding operation
- Linked list
  - Must go to each element one by one until you reach the target element (worst case access time is O(n))
  - Can be grow and shrink dynamically

List interface:

```java
public interface List<T> {
	public void insert(T element);
	public void delete(T element);
	public boolean contains(T element);
	public int size();
}
```

Java provides some list implementations in the standard library.

### Linked list

Linked list have cells that has a value and a link to the next cell.

```java
class ListCell<T> {
	// datum is singular form of data
	private T datum;
	// note that it is referencing current class
	// if it is null, this cell is the last element of the list
	private ListCell<T> next;

	public ListCell(T datum, ListCell<T> next) {
		this.datum = datum;
		this.next = next;
	}

	public T getDatum() {
		return datum;
	}
	public ListCell<T> getNext() {
		return next;
	}
	public void setDatum(T obj) {
		datum = obj;
	}
	public void setNext(ListCell<T> c){
		next = c;
	}
}
```

To create a list of one element,

```java
// note: Integer class, not primitive
ListCell<Integer> c = new ListCell<Integer>(new Integer(24), null);
```

To create a linked list of 3 elements,

```java
Integer t = new Integer(24);
Integer s = new Integer(-7);
Integer e = new Integer(87);

ListCell<Integer> p = new ListCell<Integer>(t,
	new ListCell<Integer>(s,
		new ListCell<Integer>(e, null)
	)
);
```

To search in the list

```java
public static boolean search(T x, ListCell c){
	// keep looking until the next element is null
	for(ListCell lc = c; lc != null; lc = lc.getNext()){
		if(lc.getDatum().equals(x)){
			return true;
		}
	}
}
```

or recursive version:

```java
public static boolean search(T x, ListCell c){
	return c != null && (c.getDatum().equals(x) || search(x, c.getNext()));
}
// or
public static boolean search(T x, ListCell c){
	if(c == null){
		return false;
	}
	if(c.getDatum().equals(x)){
		return true;
	}
	return search(x, c.getNext());
}
```

To reverse:

```java
public static ListCell reverse(ListCell c){
	return reverse(c, null);
}

// overloading
private static ListCell reverse(ListCell c, ListCell r){
	if(c == null){
		return r;
	}else{
		return reverse(c.getNext(), new ListCell(c.getDatum(), r));
	}
}
```

To delete one `x` out of the list:

- If list is empty, return null
- If head datum is `x`, return the next element
- Otherwise, return a list of
  - Head element and
  - List that contains result of deleting `x` from the tail elements

#### Doubly-linked list

If the `ListCell` has a link to its predecessor and successor, it is called doubly-linked list.

### ArrayList

- Java provide an ArrayList implementation that can be dynamically resized similar to the LinkedList implementation.
