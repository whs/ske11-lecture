# Computer Organization Lecture 2 - 3 September 2014

- Von Neumann architecture:
  - Von Neumann talked about bottleneck in computing between CPU and memory
  - CPU can process instructions really fast, but the memory can't keep up with it.
- In Von Neumann architecture CPU are breaked down to two parts
  - **Control**
  - **Data path** - consists of ALU (Arithmatic Logic Unit), Register (source of data to compute)
- Control loop:
  1. **Fetch**: Get instruction from memory (eg. RAM) -- thus RAM store both data and code. The instruction is stored in IR (Instruction Register -- a special storage to store instructions in CPU)
  2. **Decode**: Identify the kind of instruction retrieved.
  3. **Exec**: Send signal to related components to perform action based on instruction.
- For example, if fetch got an `ADD` instruction, control will tell ALU to perform addition.
- There are 2 kinds of instructions:
  1. Control action of CPU
  2. Control the source of data to operate on
- Work of the control:
  - Read instructions from memory
  - Issue signals to components
  - Control the program flow with `JUMP` and `BRANCH` statements.
- Datapath contains:
  - Functional components: units that perform actions eg. ALU, Register file (Storage)
  - Interconnects: Connection to data sources

## RISC

RISC stands for Reduced Instruction Set Computer.

- Has fixed instruction length (32 bits)
- Has limited addressing modes (methods to access operands -- data to be used with ALU)

The idea of having these limitations is to make the hardware *small and simple* thus performs *fast*.

## MIPS R3000 Instruction Set Architecture (ISA)

- Instruction categories
  - **Computation** - Involves ALU. eg. `ADD` `SUB` `MUL`.
  - **Load/Store** - Involves memory.
  - **Jump and Branch** - Jump is to go to a specific address. Branch is conditional jump -- go to specified address if the condition is met.
- Instruction formats: 32 bits widths
  - **R format:** `OP rs rt rd sa funct`
  - **I format:** `OP rs rt immediate`
  - **J format:** `OP jumptarget`

## Converting to binary

	1	1	1	1
	2^3	2^2	2^1	2^0
	8 +	4 +	2 +	1 = 15
	or 2^4 - 1

	1	1	1	1		1	1	1	1
	2^7	2^6	2^5	2^4		2^3	2^2	2^1	2^0
	128+64+	32+	16+		8 +	4 +	2 +	1	= 255
	or 2^8 - 1

We can read it in base 16 by grouping in a group of 4.

	1	1	1	1		1	1	1	1
	---sum=15----		----sum=15---
		F					F

We call the largest value (leftmost number) the MSB - Most Significant Bit and the smallest value (rightmost number) the LSB - Least Significant Bit

## MIPS Arithmetic Instructions

```nasm
add $t0, $s1, $s2
sub $t0, $s1, $s2
```

(Add/Subtract $s1 and $s2 and save to $t0)

Each arithmetric instruction performs only one operation. The `$` sign is indicating that the address is in register file.

## Machine language - add instruction

Comparing add operation to R format - arithmetric instruction format:

- **op:** `add`
- **rs:** `$s1`
- **rt:** `$s2`
- **rd:** `$t0`
- **shamt**
- **funct:** `add`

- **op** is 6-bits width specifying *op*eration
- **rs** is 5-bits of *r*egister file address of the first *s*ource operand
- **rt** is 5-bits of *r*egister file address of the second source operand
- **rd** is 5-bits of *r*egister file address of the result's *d*estination
- **shamt** is 5-bits specifying *sh*ift *am*oun*t* (for shift instructions)
- **funct** is 6-bits specifying *funct*ion code augmenting the opcode

## MIPS Register file

- Hold 32 of 32 bits registers
- Located in the ALU
- Has 1 write port and 2 read ports
- Input ports: `src1 addr`, `src2 addr`, `dst addr` (all 5 bits width), `write data` (32 bits width), `write control` (1 bit width)
- Output ports: `src1 data`, `src2 data` (all 32 bits width)
- Has one bit `write control` signal
  - If `write control` is on, data sent in `write data` port will be written to address specified by `dst addr` port.
  - If `write control` is off, data stored in address specified by `src1 addr` and `src2 addr` ports will be outputted to `src1 data` and `src2 data` ports.

- Registers are
  - Faster than memory (Bigger register are slower than smaller one)
  - Easier for compilers to use
  - Shorter to call than a memory location

## MIPS memory access instruction

**Load instruction**

`lw $t0, 4($s3)`

Load a word from memory location (the value of register `$s3` + `4`) to register `$t0`

**Store instruction**

`sw $t0, 8($s3)`

Store value of `$t0` to memory location (the value of register `$s3` + `8`)

- The memory address is 32-bit formed by adding the value of *base address register* to *offset* value. The offset can be positive or negative.
  - A 16-bit field means that access is limited to +-2^13 words (+-2^15 bytes) of address in base register

For example:

- `$s3` stored 1000. This is the *base address register*
- `4($s3)` means 1000 + 4 = 1004
- When writing loop, we could use `1000($s3)` and shift $s3 by 4 each loop to access 1000, 1004, 1008...

These instructions are in **I format**

- **op**: `lw`
- **rs**: `$s2`
- **rt**: `$t0`
- **16-bit offset**: 4

## Conditional branch instruction

- `bne $s0, $s1, Lbl`: Go to `Lbl` if `$s0` != `$s1`
- `beq $s0, $s1, Lbl`: Go to `Lbl` if `$s0` == `$s1`

For example,

```java
if(i == j){
	h = i+j;
}
```

```nasm
		bne $s0, $s1, Lbl1
		add $s3, $s0, $s1 # $s3 = $s0+$s1
Lbl1:	...
```

This use the **I instruction format**

- **op**: `bne`/`beq`
- **rs**: `$s0`
- **rt**: `$s1`
- **16 bit offset**: Relative position of `Lbl` to the **next** instruction

The offset is related to the **next** instruction instead of `bne`/`beq` as after `bne`/`beq` has been read the instruction address register will be already advanced to the next instruction.

As the offset is 16-bit width, the jump can be only +- 2^15-1 instructions away from the source instruction (instruction next to `bne`/`beq`)