.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:
    
    # Error checks
    li t0 1
    bge a1 t0  test1
    li a0 38
    j exit
test1:
    bge a2 t0 test2
    li a0 38
    j exit
test2:
    bge a4 t0 test3
    li a0 38
    j exit
test3:
    bge a5 t0 test4
    li a0 38
    j exit
test4:
    beq a2 a4 Prologue
    li a0 38
    j exit
   # Prologue
Prologue: 
    addi sp sp -40
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw s6 24(sp)
    sw s7 28(sp)
    sw s8 32(sp)
    sw ra 36(sp)
    mv s0 a0
    mv s1 a3
    mv s2 a1
    mv s3 a2
    mv s4 a5
    li s5 0
    mv s7 s3
    slli s7 s7 2
    mv s8 a6
    
    
    

outer_loop_start:
    li s6 0 
    

inner_loop_start:
   mv a0 s0
   mv t0 s1
   slli t1 s6 2
   add t0 t1 t0 # s1 +j *4
   mv a1 t0 
   mv a2 s3
   li a3 1
   mv a4 s4
   jal ra dot
   sw a0 0(s8)
   addi s8 s8 4
   addi s6 s6 1
   beq s6 s4 inner_loop_end
   j inner_loop_start

inner_loop_end:
    addi s5 s5 1
    add s0 s0 s7 #(i+M*4)
    beq s5 s2 Epilogue
    j outer_loop_start
ourer_loop_end:
    
    # Epilogue
Epilogue:
    
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw s6 24(sp)
    lw s7 28(sp)
    lw s8 32(sp)
    lw ra 36(sp)
    addi sp sp 40
    jr ra
