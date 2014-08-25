# ADT Lecture 3 - 25/08/2014

## Iteration

- Iterations are used to perform repetitive jobs
- Programming languages used loop construct (while, do..while, for, for each, etc.) to implement iterative algorithms

## Recursion

- A concept is defined in term of itself
  - eg. a list is empty or there is an element followed by another list
- Can be used to repeat jobs like iteration
- Related to induction

- Recursion can be written as iteration and vice-versa
- Sometimes recursion or iteration is simpler than the another

## Inductive Proof

To prove that statement `S(n)` is true:

- Assume that `S(n)` is true
- Check the following
  - Base case: Is `S(1)` true?
  - Inductive case: Is `S(n)` leads to `S(n+1)`?
- If both are true, the statement is true

**Ex:** `S(n)`: 1 + 2 + 3 + ... + n = n(n+1)/2

1. Assume that `S(n)` is true
2. Is `S(1)` true? `S(1)`: 1 = 1(1+1)/2 = 1
3. `S(n)` : 1 + 2 + 3 + ... + n = n(n+1)/2
   - Adding (n+1) to both sides: 1 + 2 + 3 + ... + n + (n+1) = n(n+1)/2 + (n+1)
   - Multiplying with 2/2: 1 + 2 + 3 + ... + n + (n+1) = n(n+1)/2 + 2(n+1)/2
   - Factor (n+1): 1 + 2 + 3 + ... + n + (n+1) = (n+1)(n+2)/2
   - `S(n+1)` : 1 + 2 + 3 + ... + (n+1) = (n+1)(n+2)/2
   - Both are equal, thus `S(n)` leads to `S(n+1)`

This is related to recursion as recursion assume that the subproblems can be solved in the same way as the main problem and solving will reach base case.

## Exercise

### 1. Calculating `n!`

We wanted to compute `n!` recursively in Java. We don't know how to compute `n!` just now, but we know how to compute `(n-1)!`. Can we use that?

Yes! `n!` = `(n-1)! * n`

What about the base case? Well, the base case is defined as `1!` = 1

```java
public static int factorial(int n){
	// Start with base case
	if(n == 1){
		return 1;
	}
	return factorial(n-1) * n;
}
```

### 2. Sum of all digits in a number `n`

**Ex.** `n` is 9,867. Sum of digits is 9+8+6+7 = 30

If we don't know how to compute sum of 9,867, but we know how to compute sum of 986 we can find sum of 9,867 by adding 7 to the answer of sum of 986.

The base case is when `n` is single digit, the answer is `n`.

```java
public static int sumDigits(int n){
	if(n < 10){
		return n;
	}
	// n%10 get the last digit
	// n/10 get rid of the last digit
	return n % 10 + sumDigits(n/10);
}
```

### 3. Is a string a palindrome?

**Ex.** `a man a plan a canal panama` can be read normally or backward resulting in the same text.

To check that a string is palindrome, we check whether the 1st character is the same as the last, and the 2nd is the same as the one 2nd from the end, and so on.

If we know that the substring between the first and the last character is a palindrome, then if the first and the last character are the same the entire string is palindrome.

Base case: when the string consist of 1 characters, the string is a palindrome.

```java
public static boolean isPalindrome(String s){
	if(s.length() == 1)	{
		return true;
	}
	if(!isPalindrome(s.substring(s, s.length() - 1))){
		return false;
	}
	return s.charAt(0) == s.charAt(s.length() - 1);
}
```