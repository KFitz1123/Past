.constant HALT      0xff00
.constant TERM      0xff10
.constant KBD       0xff20
.constant STACK_TOP 0xf800

nop
main:
  li   $s0, TERM       # Address of the terminal output for memory-mapped I/O
  li   $s1, KBD        # Address of the keyboard input for memory-mapped I/O
        li   $sp, STACK_TOP  # Predefined initial stack address
        jal reverse
        j HALT                  #stop after done

reverse:
        lb  $t0, 0($s1)           # Load a character from the keyboard
        li  $t1, '\n'             # Load a newline constant
        beq $t0, $t1, end         # Exit if char is newline
        push $t0                  #push char
        push $ra                  # push ra
        jal reverse                     #recurse
end:
        pop $ra                         #pop ra
        pop $t0                         # pop char
        sb  $t0, 0($s0)           # Write the character to the terminal
        jr  $ra                         #return
