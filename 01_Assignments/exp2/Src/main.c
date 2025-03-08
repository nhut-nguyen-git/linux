#include <stdio.h>
#include "common.h"

int main() {
    print_message();
    
    int iValue1 = 5;
    int iValue2 = 10;
    printf("Sum of %d and %d: %d\n", iValue1, iValue2, add(iValue1, iValue2));

    return 0;
}
