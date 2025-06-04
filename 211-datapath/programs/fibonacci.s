.constant TERMINAL 0xff10
.constant HALT     0xff00
.constant STACK_TOP 0xf800
.constant END      987

main:
        nop
        li   $sp, STACK_TOP
        li   $s0, TERMINAL              # Load the terminal
        li   $a0, 1
        li   $a1, 0                     # Load a1 and a0
        jal  fibonacci                  # Run the fibonacci sequence
        j    HALT                       # Stop execution

print_num:
        push $ra                        # Store ra and a0
        push $a0
        li   $t0, 10                    # t0= 10
        slt  $t2, $t0, $a0              # t2=10<n !t2=10>=n
        pop  $t0                        # pop a0
        beq  $t2, $zero, base           # t2==1 recurse
        push $t0                        # push a0
        addi $a1, $zero, 10             # $a1 = 10
        jal  remainder                  # get remainder
        pop  $a0                        # Retrieve a0
        push $v0                        # Store remainder
        li   $a1, 10                    # set a1 to 10
        jal  quotient
        addi $a0, $v0, 0                # a0 = n / 10
        jal  print_num                  #recurse
        pop  $t0                        # Get remainder
base:
        addi $t0, $t0, 0x30             # Load ASCII value to $t0
        sb   $t0, 0($s0)                # Print
        pop  $ra                        # Get return
        jr   $ra

        
quotient:
        addi $v0, $zero, 0              # Set v0 to 0
quoloop:        
        slt  $t1, $a0, $a1		# branch out if b>=a
        bne $t1, $zero, out2 			
        sub  $a0, $a0, $a1		# a0 = a0 - a1
        addi $v0,$v0,1                  # Increment v0
        j    quoloop			# loop
remainder:

        slt  $t1, $a0, $a1		# branch out if b>=a
        bne  $t1, $zero, out			
        sub  $a0, $a0, $a1		# a0 = a0 - a1
        j    remainder			# loopout:
out:    
        addi $v0, $a0, 0                # Move a0 to v0
        jr   $ra                        # Return to caller
out2:
        jr $ra                          # Return
        
fibonacci:
        push $s2                        # Store s2,s1, and ra
        push $s1
        push $ra
        add  $s2, $a0, $zero            # s2=a0
        add  $s1, $a1, $zero            # s1=a1
        jal  print_num                  # Print a1
        li   $t0, 0x0a                  # Load ASCII value for newline
        sb   $t0, 0($s0)                # Print newline
        add  $a1, $s2, $zero            # a1=first input this recursion
        add  $a0, $s2, $s1              # a0=sum of the inputs
        addi $t0, $zero, END            # Set up the check if we're done
        beq  $t0, $a0, done             # Check if we're done
        jal  fibonacci                  # Recurse if not done
done:
        pop  $ra                        # Retrieve s2,s1 and ra
        pop  $s1
        pop  $s2
        jr   $ra                        # Return

        
