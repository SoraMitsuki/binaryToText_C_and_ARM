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
.global binaryToText
.func binaryToText, binaryToText
.type binaryToText, %function

@ void binaryToText(FILE *in, FILE *out)
binaryToText:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}
    MOV r4, r0 @ store in into temp r4
    MOV r5, r1 @ store out into temp r5
    MOV r0, #6 @ need malloc a pointer with size 6
    BL malloc @ call malloc
    CMP r0, #0 @ check for pointer 
    BEQ return
    MOV r6, r0 @ save pointer into temp r6
while:
    MOV r1, #1 @ fread second argument
    MOV r2, #6 @ fread third argument
    MOV r3, r4 @ this is in file
    BL fread @ call fread
    MOV r0, r4 @ move r4 into r0 to do feof check
    BL feof
    CMP r0, #1 
    BEQ break
    MOV r0, #1 @ malloc a char pointer with size 1
    BL malloc
    CMP r0, #0 
    BEQ break
    MOV r7, r0 @ move the pointer into r7
    MOV r0, r6 @ put back the value of t6 into r0
    BL decodeChar @ call decodeChar
    STRB r0, [r7] @ store the value returned by decodeChar into pointer
    MOV r0, r7 @ move items into arugment r0,1,2,3
    MOV r1, #1
    MOV r2, #1
    MOV r3, r5
    BL fwrite @ call fwrite
    MOV r0, r7
    BL free @ free r0 everytime
    MOV r0, r6 @ move pointer back to r0
    B while @ keep loop
break:
    MOV r0, r6 @ free the size 6 pointer 
    BL free    
return:
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
