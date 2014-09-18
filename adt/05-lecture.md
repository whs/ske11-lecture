# Lecture 5 - 18 September 2014

**Exam on 13 Oct 2014, 8-11am.**

(please submit if you have lecture on the math section)

## Computing closest point

Suppose you have a 2D plane with some points on it. To find the closest dots, we have to compute the distance between every pair of dots.

For 5 dots, there are (5 2): 5!/2!3! = 10 computations

So, what is the running time of this program? Or, T(n) = O(...) where `T` is the running time and `n` is the input size (number of points in the plane).

(5 2) = 4+3+2+1 = (5*4)/2 or generalized form (n-1)+(n-2)+(n-3)+...+1 = (n-1)n/2 = (n^2-n)/2

So, as indicated by the first time of out result, the running time of this program is growing polynomially; T(n) = O(n^2)

In pseudocode,

```
for every points in the 2D plane:
	let x be the selected point
	for every points in the 2D plane that is not x:
		let y be the selected point
		calculate the distance between x and y
		record the minimum distance
	if current minimum distance is less than previous minimum distance:
		let the current minimum distance be the minimum one
```

So we also can look at the loops to compute the running time of the program. In this code we run n*(n-1) = n^2-n iterations which is O(n^2) as dominated by the largest term.

Another example,

```java
for(i = 0; i < n; i++){
	for(j = 0; j < n; j++){
		for(k=0; k < n; k++){
			C[i][j] += A[i][k] + B[k][j];
		}
	}
}
```

This matrix multiplication code is O(n^3).

If we turn that addition statement to a simple `x++`, we might think that `x++` is more simpler and should be faster but it doesn't matter as both statements run in constant time and this code would still be O(n^3).

If we turn that statement to something that is larger than O(n^3), then Big O of the code will change.

## Insertion sort

If we have a set of numbers: 8 2 4 9 3 6 and we want to sort it ascendingly.

- Make a list of sorted numbers, {} (empty) and the old set is unsorted set.
- Pick a pivot, 8 and add it to sorted numbers. {8}
- Pick another pivot, 2 and add it by comparing until we found a bigger number and put it before that number, {2, 8}.
- {2, 4, 8} unsorted {9, 3, 6}
- {2, 4, 8, 9} unsorted {3, 6}
- {2, 3, 4, 8, 9} unsorted {6}
- {2, 3, 4, 6, 8, 9} unsorted {}

In coding of this algorithm, the outer loop will grow the list of sorted numbers and the inner loop will compare the pivot to sorted set.

```
for each number x from 1 .. n:
	exchange number at position x with number from 1..x-1 position so that the number of x+1 position is in the right place
```

the time complexity of this sort algorithm is:

- Worst case: O(n^2)
- Best case: O(n) (when no swapping is never required)

when mentioning the Big O normally we means the worst case running time of the algorithm.

## Factorial

```c
int fact(int n){
	if(n == 0){
		return 1;
	}
	return fact(n-1) * n;
}
```

We need to compute T(n) -- the running time of fact(n) and T(n-1) -- the running time of fact(n-1).

- T(n) = T(n-1) + C where C is a constant processing time
- T(n) = T(n-2) + C + C
- T(n) = T(n-n) + nC

Now we can define T(0) = K which is also a constant processing time. So, T(n) = K + nC = O(n)

## Merge sort

Sort 8 3 2 9 7 1 5 4 ascendingly.

1. Divide it to two parts, {8, 3, 2, 9} and {7, 1, 5, 4}
2. Divide it furthermore, {8,3}, {2, 9}, {7, 1} and {5, 4}
3. Divide it furthermore, {8}, {3}, {2}, {9}, {7}, {1}, {5}, {4}.
4. Sort each number in group created in 2. {3, 8}, {2, 9}, {1, 7} and {4, 5}.
5. Continue doing it {2, 3, 8, 9}, {1,4, 5, 7}.
6. Result {1, 2, 3, 4, 5, 7, 8, 9}.

This algorithm turns to be O(n log n)!

## Homework problem 2

For correcting code of size n, the set doesn't have more than 3^(n-1) members.

- If n equals 2, the numbers of member will be less than 3^(2-1) = 3: {00, 11, 22}
- For n=3, there are 3^3 = 27 possible possibilities. {000, 001, 002, 010, 011, 012, 020, 021, 0211, ..., 222}
- The numbers can be organized into groups: {{000, 001, 002}, {010, 011, 012}, {020, 021, 022}, ...}. To build the error correcting set, pick one member from each groups.
