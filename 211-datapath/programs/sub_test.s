# This is a simple program that tests the implementation of your li and add instructions.
add_sub_test:
        li   $s0, 3          # Load a 3 into $s0
        add  $s1, $s0, $s0  # Store $s0 + $s0 into $s1 == 6
        addi $s2, $s1, 8    # Store $s1 + 8 to $s2 (14/e)
        subi $s3, $s2, 10   # store $s2 - 10 to $s3 (4)
        sub  $t0, $s3, $s0  # Store $s3 - $s0 in $t0 (1)
        #nop
        nop
        nop
        #and,andi
        li   $s1, 3
        li   $s0, 5
        and  $s2, $s1, $s0  #and s0 and s1, s2 == 1
        andi $s3, $s0, 12   #and s0 and 12, s3 == 4
        #or,ori
        or   $s2, $s1, $s0 #or s0 and s1, s2 == 7
        ori  $s3, $s0, 12  #or s0 and 12, s3 == 13/d
        #nand,nandi
        nand  $s2, $s1, $s0 #nand s0 and s1, s2 == 0xFFFe 
        nandi $s3, $s0, 12  #nand s0 and 12, s3 == 0xFFFb 
        #nor,nori
        nor  $s2, $s1, $s0 #nor s0 and s1, s2 == 0xFFF8 
        nori $s3, $s0, 12  #nor s0 and 12, s3 == 0xFFF2  
        #xor,xori  
        xor  $s2, $s1, $s0 #xor s0 and s1, s2 == 6
        xori $s3, $s0, 12  #xor s0 and 12, s3 == 9 
        #slt,slti
        slt  $s2, $s1, $s0 #slt s0 and s1, s2 == 1
        slti $s3, $s0, 12  #slt s0 and 12, s3 == 1
        slt  $s2, $s0, $s3 #slt s3 and s1, s2 == 0
        slti $s3, $s0, -6  #slt s0 and 12, s3 == 0
        #sltu,sltiu
        sltu  $s2, $s1, $s0 #sltu s0 and s1, s2 == 1
        sltiu $s3, $s0, 12  #sltu s0 and 12, s3 == 1
        sltu  $s2, $s0, $s3 #sltu s3 and s1, s2 == 0
        sltiu $s3, $s0, -3  #sltu s0 and 12, s3 == 0, Yikes
