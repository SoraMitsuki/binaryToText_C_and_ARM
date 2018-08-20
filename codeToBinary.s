@ Name: Jiaqi Fan
@ PID: A12584051
@ UserID: SoraMitsuki
@
@ Name : Xuanru Zhu
@ PID: A91064234
@ UserID: Aaron12138
.syntax unified

.text

.align 3
.global codeToBinary
.func codeToBinary, codeToBinary
.type codeToBinary, %function

@void codeToBinary(FILE *in, FILE *out, int index);

codeToBinary:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}
    MOV r11, r0 @ r11 is in
    MOV r10, r1 @ r10 is out
    MOV r9, r2 @ r9 is index
    MOV r4, 0x30 @ this is c
    MOV r5, 0x31 @ this is j
    MOV r0, #1 @ need malloc a pointer
    BL malloc
    MOV r8, r0 @ save r0 into r8
  while:
    MOV r0, r8 @ move the pointer back after loop
    MOV r1, #1 @ move 1 back to r1
    MOV r2, #1 @ move 1 back to r2
    MOV r3, r11 @ move in into r3
    BL fread @ call fread
    CMP r0, #1 @ check for feof
    BNE return
    LDRB r0, [r8] @ load pointer back to r0
    MOV r1, r9 @ move the index to r1
    BL extractBit @ call extractBit
  if:
    CMP r0, #0 @ compare the result from extractBit
    BNE elseif @ if it is 0 write '0' into out
    STRB r4, [r8] @ store '0' into pointer
    MOV r0, r8 @ move 0 into r0
    MOV r1, #1 @ move 1 into r1 for fwrite
    MOV r2, #1
    MOV r3, r10 @ move out into r3
    BL fwrite @ call fwrite
    B while

  elseif: @ if it is 1 write '1' into out
    CMP r0, #1 
    BNE while
    STRB r5, [r8] @ store '1' into pointer
    MOV r0, r8 @ move 1 into r0
    MOV r1, #1
    MOV r2, #1
    MOV r3, r10
    BL fwrite
    B while

return:
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
