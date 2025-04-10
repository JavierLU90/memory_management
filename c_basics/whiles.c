#include <stdio.h>

void print_numbers_reverse(int start, int end) {
    while (start >= end) {
        printf("%d\n", start);
        start--;
    }
}

/* With do-while
void print_numbers_reverse(int start, int end) {
    do {
        printf("%d\n", start);
        start--;
    } while (start >= end);
}
*/

void test(int start, int end){
    printf("Printing from %d to %d:\n", start, end);
    print_numbers_reverse(start, end);
    printf("======================\n");
}

int main() {
    test(20, 4);
}
