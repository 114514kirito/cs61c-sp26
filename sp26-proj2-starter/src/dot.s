.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
   
    # Prologue
    li t0 1
    bge a2 t0 test1
    li a0 36
    j exit
test1:
    bge a3 t0 test2
    li a0 37
    j exit
test2:
    bge a4 t0 loop_start
    li a0 37
    j exit
loop_start:
    li t0 0 # index begin with 0
    li t1 0 # index1 begin with 0
    li t2 0 # index2 begin with 0
    li t3 0 # sum begin with 0
    
loop_continue:
    beq t0 a2 loop_end
    slli t4 t1 2 #index1*4
    slli t5 t2 2 #index2*4
    add t4 a0 t4 #a0+4*index1
    add t5 a1 t5 #a1+4*index2
    lw t4 0(t4) # a0[index1]
    lw t5 0(t5) # a1[index2]
    mul t4 t4 t5 # a0[index1]*a1[index2]
    add t3 t3 t4 #sum+=
    addi t0 t0 1 
    add t1 t1 a3
    add t2 t2 a4
    j loop_continue
    
loop_end:
    mv a0 t3

    # Epilogue


    jr ra
