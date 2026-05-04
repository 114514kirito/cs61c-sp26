.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    li t0 1
    bge a1 t0 loop_start
    li a0 36
    j exit
loop_start:
    li t0 0#index begin with 0
    lw t1 0(a0)# max begin with arr[0]
    li t4 0#记录最大值的index
loop_continue:
    beq t0 a1 loop_end#结束
    slli t2 t0 2 # index *4
    add t2 a0  t2# a0+index*4
    lw t3 0(t2) # arr[index]
    blt t1 t3 max
    addi t0 t0 1
    j loop_continue
max:
    mv t1 t3
    mv t4 t0
    addi t0 t0 1
    j loop_continue
loop_end:
    # Epilogue
    mv a0 t4 
    jr ra

