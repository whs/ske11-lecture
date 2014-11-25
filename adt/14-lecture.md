# ADT Lecture 14 - 24 November 2014
## Hashtable

Hashtable cut out the search time to O(1) by applying a *hash function* to input, then store the item at location indicated by the function output. So, to search just apply hash function and see that whether there is an item at the location.

### Designing a hash function

We need the keys to be different. So for phone numbers, last few digits are more suitable for hashing than the first few numbers.

The attributes of good hash function are discussed in last issue.

Hashing are also used in other fields such as cryptography and text comparing. To compare two strings the hash of them can also be used to compare and good hash function to do this are *cryptographically secure hash functions* which change drastically even when only a single input bit change.

### Hash collision

Sometimes (which we want it to be very rarely) hashing function may return duplicate output for different inputs as we want the output range of hash function to be small. This is called hash collision and it should be avoided.

This can be analyzed by the birthday problem. If we have `M` bins and randomly throwing balls into them we will starting to get two balls in the same bin after around `sqrt(piM/2)` tosses. Also, the coupon collector problem states that every bins will has a ball or more after around `M ln M` tosses.

To fix the problem of hash collision, we use hash table chaining.

### Hash table chaining

In each of the hash table cell instead of storing the value directly, we store a linkedlist of values that stored in this slot. When searching after hash function was applied we still have to search this linkedlist which should be of small size.

```java
class SeparateChainingHashST<Key, Value>{
	private int M = 97;
	private Node[] st = new Node[M];
	private static class Node{
		private Object key;
		private Object val;
		private Node next;
	}

	public int hash(Key key){
		// return the value of hashcode without the sign bit
		return (key.hashCode() && 0x7ffffffff) % M;
	}

	public void put(Key, key, Value val){
		int i = hash(key);
		for(Node x = st[i]; x != null; x = x.next()){
			if(key.equals(x.key)){
				x.val = val;
				return;
			}
		}
		st[i] = new Node(key, val, st[i]);
	}
}
```

The performance of seperate chaining is log(N) in worst case of insert, search, delete and 3-5 iterations for average case if the hashing is uniform enough.

### Pros - Cons

#### Hashtable
- Simple
- No effective alternative for unordered tree
- Faster for simple key
- Better support in Java

#### BST
- Performance more guaranteed
- Support ordered ST operation
- `compareTo` is easier to implement correctly than `hashCode`

In Java both algorithms are provided in the standard library as `java.util.TreeMap`, `java.util.TreeSet`, `java.util.HashMap`, `java.util.IdentityHashMap`.

## Graph

Graph consists of nodes and lines that connect nodes together called edges. Tree is also a special type of graph.

### Undirected graph

G = (V, E) is an ordered pair of

- V = nodes
- E = edges between pair of nodes
- Graph size n = |V|, m = |E|
- Two nodes connected by an edge are said to be neighbour.
- The number of |E| is proportional to V^2
- If the graph is connected (every nodes have path to it from every other nodes), |E| >= |V| - 1
- Degree of V is the number of edges connected to V
  - Handshaking lemma: Sum of degree of every nodes in the graph = 2 |E| as it would could the same edges twice.

### Directed graph

- Same as undirected graph, but the connection (edges) has direction of connection.
- For example, website A links to website B but B may not link back to A.

### Representation of undirected graph
#### Adjacency matrix

We use **adjacency matrix** to represent graph. The space used is proportional to n^2, checking whether two nodes are connected takes O(1) and to list all edges takes O(n^2).

   | 1 | 2 | 3 | 4 | 5
---|---|---|---|---|---
 1 | ✕ | ✓ | ✕ | ✕ | ✕
 2 | ✓ | ✕ | ✓ | ✕ | ✕
 3 | ✕ | ✓ | ✕ | ✓ | ✓
 4 | ✕ | ✕ | ✓ | ✕ | ✓
 5 | ✕ | ✕ | ✓ | ✓ | ✕

From this matrix table we can see that node 1 is connected to only node 2, and node 3 is connected to node 2, 4 and 5.

This representation is suitable for dense graph. If the graph does not have many edges it would be a waste of space and use more time to list all edges.

#### Adjacency list

- Store edges of each node as a linked list
- Space proportional to m+n
- Checking for edge takes O(deg(u)) time.
- List all edges takes O(m+n) time.
- Use for sparse graph (graph that doesn't have much edges)

### Path and connectivity

**Path** in an undirected graph is a sequence of nodes that node v[i] is connected by an edge to v[i+1].

A graph could be said that it is **connected** if for every pair of nodes there is a path between them.

**Cycle** is a path that v[1] = v[k] where k > 2 and all other nodes than v[k] are distinct.

**Tree** is an undirected graph that is connected and does not contain a cycle. We can choose a node a tree to be a root. This tree is then called rooted tree.

### Graph traversal

#### Depth first search (DFS)

```java
public void dfs(Node c){
	c.visited = true;
	for(Node n : c.neighbours){
		if(!n.visited){
			dfs(n);
		}
	}
}
```

We can use DFS to find path between two nodes in the graph.

#### Breadth first search (BFS)

In this we use a queue to perform searching.

1. Put the starting node on the queue
2. Mark the starting node as visited
3. Pop the queue
4. Check whether the node is the one we want
5. If not put its unvisited neighbours on the queue and mark them as visited.
6. Repeat from 3