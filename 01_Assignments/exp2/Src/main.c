#include <stdio.h>
#include "common.h"

int main() {
    print_message();
    
    int x = 5, y = 10;
    printf("Sum of %d and %d: %d\n", x, y, add(x, y));

    return 0;
}
