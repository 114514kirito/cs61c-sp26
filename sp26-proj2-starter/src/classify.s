.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
classify:
    addi sp sp -48
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw s6 24(sp)
    sw s7 28(sp)
    sw s8 32(sp)
    sw s9 36(sp)
    sw s10 40(sp)
    sw ra 44(sp)
    mv s0 a0
    mv s1 a1
    mv s7 a2
    li t0 5
    beq s0 t0 read
    li a0 31
    j exit
read:
    li a0 24
    jal ra malloc
    bne a0 x0 next
malloc_error:
    li a0 26
    j exit
next:
    mv s2 a0
    lw a0 4(s1)
    mv a1 s2
    addi a2 s2 4
    jal ra read_matrix
    mv s3 a0 # m0的矩阵
    lw a0 12(s1) 
    addi a1 s2 16
    addi a2 s2 20
    jal ra read_matrix
    mv s5 a0 # input
    lw a0 8(s1)
    addi a1 s2 8
    addi a2 s2 12
    jal ra read_matrix
    mv s4 a0
    lw t0 0(s2)
    lw t1 20(s2)
    mul s8 t0 t1
    slli a0 s8 2
    jal ra malloc
    beq a0 x0 malloc_error
do_h_matmul:
    mv s6 a0
    mv a0 s3
    lw a1 0(s2)
    lw a2 4(s2)
    mv a3 s5
    lw a4 16(s2)
    lw a5 20(s2)
    mv a6 s6
    jal ra matmul
relu_h:
    mv a0 s6
    mv a1 s8
    jal ra relu
do_matmul_o:
    lw t0 8(s2)
    lw t1 20(s2)
    mul t0 t0 t1
    slli a0 t0 2
    jal ra malloc
    beq a0 x0 malloc_error
    mv s9 a0
    mv a0 s4
    lw a1 8(s2)
    lw a2 12(s2)
    mv a3 s6
    lw a4 0(s2)
    lw a5 20(s2)
    mv a6 s9
    jal ra matmul
write:
    lw a0 16(s1)
    mv a1 s9
    lw a2 8(s2)
    lw a3 20(s2)
    jal ra write_matrix
argmax_o:
    mv a0 s9
    lw t0 8(s2)
    lw t1 20(s2)
    mul a1 t0 t1
    jal ra argmax
    mv s10 a0
    bne s7 x0 end
print_o:
    mv a0 s10
    jal ra print_int
    li a0 '\n'
    jal ra print_char
end:
    mv a0 s2
    jal ra free
    mv a0 s3
    jal ra free
    mv a0 s4
    jal ra free
    mv a0 s5
    jal ra free
    mv a0 s6
    jal ra free
    mv a0 s9 
    jal ra free
    mv a0 s10
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw s6 24(sp)
    lw s7 28(sp)
    lw s8 32(sp)
    lw s9 36(sp)
    lw s10 40(sp)
    lw ra 44(sp)
    addi sp sp 48
    jr ra
