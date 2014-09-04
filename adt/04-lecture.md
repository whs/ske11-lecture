# ADT Lecture 4 - 4 September 2014

**Recursion (cont.)**

## Permutation

Suppose we have a string `S = "abc"`. `permute("abc")` should returns a list of `abc` `acb` `bac` `bca` .... which have the size of 3! elements.

If we want to permute a string of length `n`, we should consider how to permute a string of length `n-1`

	a b c d e
	  |_____|
	 permute these

After we have the result of substring permutation, we can compute the permutation of main string by adding a to various positions of the output.

	a _ _ _ _
	_ a _ _ _
	_ _ a _ _
	_ _ _ a _
	_ _ _ _ a

Now let's code it in Java. We have to choose a data structure to use. In this case we can use `ArrayList`

```java
ArrayList<String> permute(String s){
	ArrayList<String> as = new ArrayList<String>();

	// base case
	if(s.length() == 1){
		as.add(s);
		return s;
	}

	ArrayList<String> t = permute(s.substring(1));

	for(String ss : t){
		for(int i=0; i < s.length() + 1; i++){
			String sss = new String();
			sss += ss.substring(0, i) + 
				s.substring(0, 1) +
				ss.substring(i, ss.length());
			as.add(sss);
		}
	}

	return as;
}
```

## Number of combinations

*This section use LaTeX to denote mathematics equations*

We want to calculate (n r) (\dbinom{n}{r}) recursively. The formula to compute this is (n r) = (n-1 r-1)*(n-1 r) (\dbinom{n-1}{r-1}\dbinom{n-1}{r}).

For example, to compute the number of combinations in shuffling abcde we can see that it is number of combinations without a + number of combinations with a.

```java
int combi(int n, int r){
	// (n 0) = (n n) = 1
	if((r == 0) || (r == 1)){
		return 1;
	}
	return combi(n-1, r) + combi(n-1, r-1);
}
```

## Speeding up recursion

1. Only recurse when necessary
2. Use divide and conquer technique
3. Memorization

For example for the divide and conquer techinque, to do a^n we can see that a^n = a^(n/2) a^(n/2) if n is even and a^n = a^(n/2)a^(n/2)a if n is odd.

```java
int fastPower(int a, int n){
	if(n == 0){
		return 1;
	}
	int temp = fastPower(a, n/2) * fastPower(a, n/2);
	if(n % 2 == 0){
		return temp;
	}else{
		return a * temp;
	}
}
```

For the memorization technique, we can use it to compute the fibonacci sequence faster. After we have computed a number, we add it to a cache to avoid computing it again later.
