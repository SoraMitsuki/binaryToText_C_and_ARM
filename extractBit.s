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
.global extractBit
.func extractBit, extractBit
.type extractBit, %function

@ int extractBit(char c, int index)
extractBit:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}
    MOV r11, #1 @ this is mask
    LSL r11, r11, r1 @ mask << index
    AND r10, r11, r0 @ mask & c
    LSR r0, r10, r1 @ unsigned shift right by index
  return:
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
