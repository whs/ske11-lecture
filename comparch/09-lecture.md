# Computer Organization Lecture 9 - 12 November 2014
## Overcoming data hazard

Data hazard is when data is required before it is ready. There are several ways to avoid data hazards

### Stall

Stall is just to wait until everything clears up and it is safe to use the data.

### Reorder code
```asm
# $t1 = address of v[k]
lw $t0, 0($t1) # $t0 = v[k]
lw $t2, 4($t1) # $t2 = v[k+1]
sw $t2, 0($t1) # v[k] = $t2
sw $t0, 4($t1) # v[k+1]= $t0
```

In the above code data hazard would occur on $t2 as it is read and used immediately. We can reorder code to avoid this.

```asm
lw $t0, 0($t1) # $t0 = v[k]
lw $t2, 4($t1) # $t2 = v[k+1]
sw $t0, 4($t1) # v[k+1] = $t0
sw $t2, 0($t1) # v[k] = $t2
```

This is called instruction scheduling.

### Forwarding

We can use forwarding or bypassing to overcome data hazard. This is covered in last lecture note.

To forwarding is to send the output to the instructions that needs that output as soonest as it is available. This requires extra wiring. When we add these wiring to the ALU we need to add multiplexors to the input of ALU.

### Writeback and mem conflict

There could be a potential conflict when forwarding both WB and MEM stage at the same time so we need to check for that too.

### Load-use hazard detection

We need to have a hazard detection unit in the ID to insert stall operation between load and its use.

## Implementing stall

Stall is implemented by preventing instruction in IF and ID stage to flow into the pipeline.

## Jump

Jump is not decoded until ID so we need a stop that clear out the pipeline. To optimize jump, we move the branch decision hardware back to earlier stage (EX stage).