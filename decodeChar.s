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
.global decodeChar
.func decodeChar, decodeChar
.type decodeChar, %function

@ char decodeChar(char *b)
decodeChar:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}
    LDR r11, =MAPPING @ get mapping array
    MOV r4, #5 @ this is i
    MOV r5, #0 @ this is c
    MOV r9, #1 @ used for LSL
    MOV r7, #0 @ this is index
  for:
    CMP r4, #0 @ loop from 5 to 0
    BLT return
  if:
    LDRB r10, [r0, r4] @ get the value from array
    CMP r10, 0x31 @ compare it is '1' or not
    BNE update
    LSL r6, r9, r5 @ compute = 1 << c
    ADD r7, r7, r6 @ index = index + compute
  update:
    ADD r5, r5, #1 @ c++
    SUB r4, r4, #1 @ i --
    B for
return:
    LDRB r0, [r11, r7] @ return mapping[index]
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
