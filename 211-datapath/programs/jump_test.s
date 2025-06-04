jump_test:
        nop
        li  $s0,  1             #s0=1
        li  $s1,  5             #s1=5
        li  $s2,  1             #s2 = 1
        jal func                #Go to func
        j   next                #Start again

func:
        add $t0, $t0, $s0       #Add 1 to t0
        jr  $ra                 #Return
next:
        beq $s0, $s2, success   # expect to branch to success
        li  $t0, -1             # if the command fails, set $t0 to -1
success:
        li  $t2, 3              # if beq succeeds, set $t2 to 3
        bne $s0, $s1, success2  # expect to branch to success2
        li  $t0, -1              # if the command fails, set $t0 to -1
success2:
        addi $t2,$t2, 1         # if bne succeeds, set $t2 to 4
        beq $s0, $s1, fail      # here $t0 should be not -1
        addi $t2,$t2, 2         # if beq fails successfully, set $t2 to 6
        bne $s0, $s2, fail      # expect no  branch
        li  $t1, 16             # if bne fails successfully, set $t1 to 16
                                
fail:
       li  $t0, -1              # here $t1 should be 16, $t2 = 6, $t0 = FFFFFF
