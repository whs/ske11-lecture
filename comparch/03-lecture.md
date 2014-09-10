# Computer Organization Lecture 3 - 10 September 2014

## More conditional instructions

**Set on less than instruction**

```nasm
slt $t0, $s0, $s1
```

If `$s0` < `$s1`, set `$t0` to 1 else `$t0` is set to 0.

Use R instruction format (`op rs rt rd funct`)

**Branch instructions**

- `blt $s1, $s2, Label`
- `ble $s1, $s2, Label`
- `bgt $s1, $s2, Label`
- `bge $s1, $s2, Label`

The set instruction and branch instructions can be used to create other type of jump conditions. For example,

```nasm
slt $at, $s1, $s2 ; set $at to 1 if $s1 < $s2
bne $at, $zero, Label ; If $at is not 0, jump to label
```

## Other control flow instructions

```nasm
j label ; Jump to label unconditionally
```

Use J instruction format (`op address`, where address is 26 bit width)

The jump address is wider than branching instruction so it can be used for larger jump. It is also absolute address instead of relative address.

The assembler use the jump command to jump to an address that is can't be addressed by 16 bit:

```nasm
beq 4s0, $s1, L1
```

becomes

```nasm
		bne $s0, $s1, L2
		j L1
L2:		...
```

## Accessing procedures

```nasm
jal ProcedureAddress ; Jump and link
```

Save PC+4 to register `$ra` to have a link to the next for the procedure return.

Use J instruction format.

After we have jump and linked, we can return by

```nasm
jr $ra ; return
```

Use R instruction format (`op rs`)

If the callee needs more register or the procedure is recursive, a *stack* is used.

Stack is an in-memory last in first out queue for passing additional values or saving return addresses. Register `$sp` is used to address the stack which grow from high memory address to low memory address.

## Immediate instructions

Immediate instructions are instructions that have a constant value in it

```nasm
addi $sp, $sp, 4 ; $sp = $sp + 4
slti $t0, $s2, 15 ; $t0 = 1 if $s2 < 15
```

These instructions use I format (`op rs rt immediate` where immediate is 16-bit width) so the constant used must be in range -2^15 to 2^15-1.

To use 32-bit constant we can use 2 instructions for it:

```nasm
lui $t0, 1010101010101010 ; Load upper immediate
ori $t0, $t0, 1010101010101010 ; Set lower immediate
```

So `$t0` will be set to 10101010101010101010101010101010. The first 16 bits are set by lui and the rest by ori

	[---- lui -----][----- ori ----]
	10101010101010101010101010101010

## Review

**Instructions**

- **Arithmetic/Logic** - Add, Add immediate, Subtract, And, Or, Xor...
- **Data Transfer** - Load word, Store word, Load byte, Store byte, Load upper immediate
- **Branch** - Branch on equal, Branch on not equal
- **Jump** - Jump, Return jump, Jump and link

**Instruction formats**

1. R: `opcode rs rt rd shamt funct`
2. I: `opcode rs rt immediate`
3. J: `opcode address`

**Addressing modes**

1. Register addressing - operand is in a register
2. Base addressing - operand is in a memory location which address is the sum of a register value and a 16-bit constant in the instruction
3. Immediate addressing - operand is a 16-bit constant in the instruction
4. PC-relative addressing - address is sum of the PC and 16-bit constant in the instruction
5. Pseudo-direct addressing - address is 26-bit constant contained in the instruction concatenated with upper 4 bits of PC

**MIPS Design principles**

- Fixed size instruction: 32 bits
- Small number of instruction formats
- These compromises make common cases fast

## MIPS Number Representation

MIPS use the first bit to indicate negative number. If it is 0, it is positive. If it is 1, it is negative.

If the number is negative, the numbers will be written inverted plus one. This system is called 2's complement

Base 10 | Base 2
------- | -------
5		| `0101`
-5		| `1010` + 1 = `1011`
6		| `0110`
-6		| `1001` + 1 = `1010`

When we doing subtraction operation, we use 2's complement and add the numbers up together. eg. 6 - 3 = 6 + (-3)

When converting to 32 bit values, the MSB (the sign bit) will be copied to empty bits

	0010 -> 0000 0010
	1100 -> 1111 1100