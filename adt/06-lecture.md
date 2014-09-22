# ADT Lecture 6 - 22 September 2014

## Analysis of program running time

### Merge sort

To sort 8, 3, 2, 9, 7, 1, 5, 4:

- Split to half {8, 3, 2, 9}, {7, 1, 5, 4}
- Split it further {8,3}, {2,9}, {7, 1}, {5, 4}
- Split it further {8}, {3}, {2}, {9}, {7}, {1}, {5}, {4}
- Combine and sort each pair of elements: {3, 8}, {2, 9}, {7, 1}, {4, 5}
- {2, 3, 8, 9}, {1, 4, 5, 7}
- {1, 2, 3, 4, 5, 7, 8, 9}

To merge two *sorted* arrays to one,

- Have two pointers to start of each array {**2**, 3, 8, 9}, {**1**, 4, 5, 7}
- Combine elements pointed by the pointers and put it into the result array then advance the pointer of that array.
  - {**2**, 3, 8, 9}, {**4**, 5, 7} --> {1}
  - {**3**, 8, 9}, {**4**, 5, 7} --> {1, 2}
  - {**8**, 9}, {**4**, 5, 7} --> {1, 2, 3}
  - {**8**, 9}, {**5**, 7} --> {1, 2, 3, 4}
  - {**8**, 9}, {**7**} --> {1, 2, 3, 4, 5}
  - {**8**, 9}, {} --> {1, 2, 3, 4, 5, 7}
- When an array is exhaused, copy rest of the other array.
  - {1, 2, 3, 4, 5, 7, 8, 9}

Again, this method works only if the arrays are sorted.

The running time of this merge step is O(n) because in each step you advance either pointer one by one. The number of time we pull the elements is depending on the number of elements.

Psuedocode:

```py
def mergesort(A):
	if a.size == 1:
		return A
	s1 = mergesort(A[0:a.size/2 - 1])
	s2 = mergesort(A[a.size/2:])
	return merge(s1, s2)
```

We can see that in this function:

- T(n) = T(n/2) + T(n/2) + Kn + C (T(n/2) for recursive call, Kn for merge, C for minor processing)
- 2T(n/2) + Kn + C
- 2(2T(n/4)) + Kn + C
- 2^2 T(n/4) + Kn + 2C + Kn + C
- 2^2 T(n/4) + 2Kn + 3C
- 2^2 (2T(n/8) + Kn/4 + C) + 2Kn + 3C
- 2^3 T(n/8) + 3Kn + 4C
- and so on. This technique is called repeated substitution
- We can see that 2^x = n thus x = log n (base 2)
- 2^(log n) T(n/2 log n) + log nKn + (log n + 1)C
- nT(1) + Kn (log n) + (log n + 1)C
- T(1) = C
- nC + Kn(log n)+(log n+1)C
- log n dominates n
- This algorithm is O(n log n)

### Fibonacci

```c
int fib(int n){
	if(n == 0){
		return 0;
	}
	if(n == 1){
		return 1;
	}
	return fib(n-1) + fib(n-2);
}
```

- T(n) = T(n-1) + T(n-2)
- = (T(n-2)+T(n-3) + C) + (T(n-3)+T(n-4)+C) + C
- = (T(n-3)+T(n-4)+C + T(n-4)+T(n-5)+C) + (T(n-4)+T(n-5)+C)
- and so on
- ~= 2^n ~= (1.6)^n

### Memorized fibonacci

```c
int fibm(int n){
	if(n <= 1){
		return n;
	}
	if(in_cache(n)){
		return get_cache(n);
	}
	int out = fibm(n-1) + fibm(n-2);
	put_cache(n, out);
	return out;
}
```

When recursion, we only need to do one half of the recursion tree thus this is O(n)

## List data structure