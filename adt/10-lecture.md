# ADT lecture 10 - 9 October 2014

## Infix form

Scan from left to right one character at a time

- If it is operand, print it
- If it is (, push onto stack
- If it is operator, pop the stack until we have lower precedence item on ..., push that operator
- If it is ), pop until ( including (
- At the end, pop everything

The operator precedence are:
- */
- +-

For example, 1+2*3+(4*5+6)

	Note: should be incorrect, please fix

	Postfix: 1 2
	Stack: +

	Postfix: 1 2 3
	Stack: + * (pop)
	Stack: +
	Stack: 

	Postfix: 1 2 3 * +
	Stack: +

	Postfix: 1 2 3 * + 4 5 *
	Stack: + ( *
	Stack: + (

	Postfix: 1 2 3 * + 4 5 * 6 +
	Stack: + ( +
	Stack: + (
	Stack: +
	Stack:

TODO: Computation by stack

Instead of doing the actual calculation, once an operator is discovered we form a subtree of that operator as a root and push it onto the stack

TODO: how?

```java
public static int eval(TreeCell root){
	int left_result, right_result;
	if(root.datum is a number){
		return 0;
	}
	left_result = eval(root.left);
	right_result = eval(root.right);
	switch(root.datum){
		case '+':
			return left_result + right-result;
		case '-':
			return left_result - right_result;
		case '*':
			return left_result * right_result;
		case '/':
			return left_result / right_result;
		case '%':
			return left_result % right_result;
	}
}
```

## Stack

Stack is a data structure which is area in memory used for saving data from function calls.

For example, in a recursive factorial function the hardware will push a "stack frame" which register the function call onto a stack. During the evaluation as this is recursive function more stack frames will be reserved until the base case is reached then the stack is starting to get popped.

If the recursion has no limit, the stack will be full and a stack overflow exception is generated.