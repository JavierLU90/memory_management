#include <stdio.h>

void print_numbers(int start, int end) {
    for (start; start <= end; start++) {
        printf("%d\n", start);
    }
}

void test(int start, int end){
    printf("Printing from %d to %d:\n", start, end);
    print_numbers(start, end);
    printf("======================\n");
}
  
int main() {
    test(42, 69);
}
