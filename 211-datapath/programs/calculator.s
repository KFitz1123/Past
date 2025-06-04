.constant HALT      0xff00
.constant TERM      0xff10
.constant KBD       0xff20
.constant STACK_TOP 0xf800

nop
main:
  li   $s0, TERM       # Address of the terminal output for memory-mapped I/O
  li   $s1, KBD        # Address of the keyboard input for memory-mapped I/O
  li   $sp, STACK_TOP  # Predefined initial stack address


loop_top:
        lb  $t0, 0($s1)           # Load a character from the keyboard
        beq $t0, $zero, loop_top  # If it is the null terminator, start over
        li  $t1, '\n'             # Load a newline constant
        beq $t0, $t1, end         # If the character was the newline, stop looping
        push $t0
pause1: 
        lb  $t0, 0($s1)           # Load a character from the keyboard
        beq $t0, $zero, pause1    # If it is the null terminator, start over
        li  $t1, '\n'             # Load a newline constant
        beq $t0, $t1, end         # If the character was the newline, stop looping
        push $t0
pause2: 
        lb  $t0, 0($s1)           # Load a character from the keyboard
        beq $t0, $zero, pause2    # If it is the null terminator, start over
        li  $t1, '\n'             # Load a newline constant
        beq $t0, $t1, end         # If the character was the newline, stop looping
        pop $t1
        pop $t1
        sb  $t1, 0($s0)           # Write the character to the terminal
        li  $t2, 43               # Write '+' to the terminal
        sb  $t2, 0($s0)           # Write the character to the terminal
        sb  $t0, 0($s0)           # Write the character to the terminal
        li  $t2, '\n'             # Load a newline constant
        sb  $t2, 0($s0)           # Write the character to the terminal
        add $a0, $t1, $t0
        addi $a0, $a0, -96
        jal print_num
        li  $t2, '\n'             # Load a newline constant
        sb  $t2, 0($s0)           # Write the character to the terminal
        j   loop_top              # Start over

end:
  j   HALT                  # Enable halt pin and stop the PC incrementing

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
