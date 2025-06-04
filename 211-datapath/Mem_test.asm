test_start:
        li   $sp, 0xf800          #init stack
        li   $s0, 5
        li   $s1, 7
        addi $sp, $sp, -4
        sw   $s0, 0($sp)          #put 5 on the stack
        lw   $s2, 0($sp)          #pop 5 from the stack
        addi $sp, $sp, 4          # $s2 == 5
        
        
