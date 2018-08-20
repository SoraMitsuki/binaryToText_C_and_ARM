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
.global decodeFile
.func decodeFile, decodeFile
.type decodeFile, %function
 
@ void decodeFile(char *input, char *bin, char * output, int index)
decodeFile:
    @ Save caller's registers on the stack
    push {r4-r11, ip, lr}
  .data
  str1: .asciz "rb" @ create string for fopen
  str2: .asciz "wb"
  .text
    MOV r4, r0 @ save all 4 arguments into temp
    MOV r5, r1
    MOV r6, r2
    MOV r7, r3
    LDR r1,=str1 @ load "rb" into r1
    BL fopen @ call fopen on in
    CMP r0, #0 @ null check
    BEQ return
    MOV r8, r0 @ save it into temp r8
    MOV r0, r5 @ call the second fopen in "wb" mode
    LDR r1,=str2
    BL fopen @ call fopen on bin
    CMP r0, #0 @ null check
    BEQ return
    MOV r9, r0 @ save the result in temp r9
    MOV r0, r6 @ fopen the third file  
    LDR r1,=str2 
    BL fopen  @ fopen on out
    CMP r0, #0
    BEQ return @ null check
    MOV r10, r0
    MOV r0, r8 @ put temps into r0, r1 ,r2
    MOV r1, r9
    MOV r2, r7
    BL codeToBinary @ call code to binary
    MOV r0, r8 @ save the result into temp r8
    BL fclose @ fclose the in file
    MOV r0, r9
    BL fclose @ fclose the bin file
    MOV r0, r5
    LDR r1,=str1 @ open the bin file in "rb" mode
    BL fopen
    CMP r0, #0
    BEQ return @ do null check
    MOV r9, r0
    MOV r1, r10 @ call the binary to text 
    BL binaryToText
    MOV r0, r9 @ fclose the bin file
    BL fclose
    MOV r0, r10
    BL fclose @ fclose the out file
return:
    @ restore caller's registers
    pop {r4-r11, ip, lr}

    @ ARM equivalent of return
    BX lr
.endfunc

.end
