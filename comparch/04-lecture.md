# Computer Architecture Lecture 4 - 24 September 2014

- Multiplication use 4 cycles to operate instead of 1 as in addition
- We can optimize like doing bit shift for 2 multiplication.

## Booth's Algorithm

- There is an algorithm called booth's algorithm to compute multiplication of signed (positive/negative) number faster
  - Assume we have a partial sum, A = 0
  - We have a counter, c = n
  - We have one bit counter, `Q[-1]` = 0
  - Let M be the multiplicant and Q be the multiplier
  - When doing multiplication, look at the rightmost bit of the multiplier and `Q[-1]`
  	- If they are 1 and 0, `A = A-M`
  	- If they are 0 and 1, `A = A+M`
  - Right shift so that `Q[-1]` = `Q[0]`, Q is right shifted and the first bit is taken from A
  - c--
  - Repeat until c=0

Example:

	  A		 Q		Q[-1]	M
	0000	0011	0		0111	Initial value

	1001	0011*	0*		0111	A = A-M
	1100	1001	1		0111	Shift (note that the sign bit of A is duplicated)

	1110	0100	1		0111	Shift

	0101	0100*	1*		0111	A = A+M
	0010	1010	0		0111	Shift

	0001	0101	0		0111	Shift


Binary subtraction:

	0000 -
	0111
	----
	1001

## Array Multiplier

There is another type of multiplier that is more commonly used but more expensive called array multiplier

----|----|----|----|----|
    |    |  Y2|  Y1|  Y0|
----|----|----|----|----|
    |    |  X2|  X1|  X0|
    |    |Y2X0|Y1X0|Y0X0|
    |Y2X1|Y1X1|Y0X0|    |
Y2X2|Y1X2|Y0X2|    |    |
----|----|----|----|----|
Y2X2|Y1X2|Y0X2|Y0X1|Y0X0|
    |Y2X1|Y1X1|Y1X0|    |
    |    |Y2X0|    |    |

## Division

			   <-n->
			   .... 	quotient
		<-n->______
		...|....000		dividend
	divisor|....
		   -----
		     ...0 -
		     ....
		     ----		partial remainder array
		      ...0 -
		      ....
		      ----
		       ...0 -
		       ....
		       ----
		       ....		remainder
		       <-n->

To do division we need to guess the numbers to be filled in the quotient. In binary this is easier as we only need to guess only 0 or 1. After we have chosen, multiplied and subtracted we look at the sign bit of the subtraction. If it is 1 it is negative and it is incorrect.

Example

V=101, D=100110, R0 = D

	100110 -		R1 = R0-q0 2^0V, q0=0
	000
	------
	100110			R2 = R1-q1 2^-1V, q1=1
	 101
	------
	 10010			R3 = R2-q2 2^-2V, q2=1
	  101
	------
	  1000			R4 = R3-q3 2^-3V, q3=1
	   101
	------
	   011			Remainder

The result is 0111, the remainder is 011.

We also can do it by shifting the remainder to the left instead of shifting the divisor to the right

	R[i+1] = 2R[i] - q[i]V

	  100110
	  000
	--------
	  100110		R[1] = 2R[0] - q[i]V
	 100110
	  101
	--------
	  100100
	 100100			2R[2]
	  101
	--------
	  100000
	 100000
	  101
	--------
	  01100
	  101			<- Remainder

## MIPS Division

In MIPS the division instruction, `div`, generates the remainder in `hi` and the quotient in `lo`.

In other words, `div $s0, $s1` we get `lo` = `$s0`/`$s1`, `hi` = `$s0` mod `$s1`.

## Floating point representation

- (-1)^`sign` x F x 2^`E`
- Encoded in 32 bits (called single precision) as
  - Sign (1 bit)
  - E: Exponent (8 bits)
  - F: Fraction/Mantissa (23 bits)
- The range is +- 2^256 ~= 1.5E77
- 23 bit mantissa has accuracy of 1.2E-7 or around 6 decimal places
- There are some numbers which cannot be expressed by the floating point representation
  - Negative/positive underflow: too close to zero
  - Negative/positive overflow: too far to zero
- Computer nowadays use IEEE754 floating point standard: (-1)^`sign` x (1+F) x 2^`E`
  - F is normalized or that the first bit which has the value of 1 is not included (hidden bit)
  - For example, 0.01010 is stored in F as 010, the first 1 is not stored by implied implicitly.
  - E is stored before F and is written in excess (biased notation) to ease out sorting.
- If it is stored using 64 bits it is called double precision

## Floating point addition

(+- `F1` x 2^`E1`) + (+-F2 x 2^`E2`) = +-`F3` x 2^`E3`

1. Restore the hidden bit in F1 and F2
2. Right shift F2 by E1-E2 positions (E1>=E2) and the three bits shifted out are called round bit, guard bit and sticky bit
3. Add the result of the shift to F1 and call it F3.
4. Normalize F3
   - If F1, F2 have the same sign and F3 is between 1 and 4, bit right shift F3 once and increase E3
   - If F1, F2 have different signs, left shift F3 many times and decrease F3 every time doing so.
5. Round and normalize F3
6. Hide the most significant bit (MSB) of F3 before storing the result

## MIPS Floating point instruction

MIPS have seperate floating point register file from `$f0` to `$f31` (use 2 registers to store double precision)

Special instructions are required to access and store them:

```asm
lwcl $f1, 54($s2)
swcl 4f1, 58($s4)
```
