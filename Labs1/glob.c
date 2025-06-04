#include <stdio.h>

int glob = 10;

void
g (void) {
    // Point (B)---first call to g()
    for (int i = 0; i < glob; i++) {
        printf("%d ", i);
    }
    printf("\n");
    glob += 1;
    // Point (C)---final call to g()
} // g

int
f (void) {
    for (int i = 0; i < glob; i += 2) {
        // Point (A)---first iteration of the for-loop
        g();
        printf("===\n");
    }
    return glob;
} // f

int
main (void) {
    int ret = f();
    // Point (D)
} // main
