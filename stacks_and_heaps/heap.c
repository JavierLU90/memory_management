#include <stdio.h>
#include <stdlib.h>

char *get_full_greeting(char *greeting, char *name, int size) {
    char *full_greeting = (char*)malloc((size + 1) * sizeof(char));
    if (full_greeting == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
    }
    snprintf(full_greeting, size + 1, "%s %s", greeting, name);
    if (size > 0 && full_greeting[size - 1] == ' ') {
            full_greeting[size - 1] = '\0';
    }
    return full_greeting;
}

/*
This is the code used to test the former code:


#include "munit.h"
#include <string.h>
#include <stdbool.h>
#include "exercise.h"

// Helper function to check if a pointer is on the stack
bool is_on_stack(void *ptr) {
  void *stack_top = __builtin_frame_address(0);
  uintptr_t stack_top_addr = (uintptr_t)stack_top;
  uintptr_t ptr_addr = (uintptr_t)ptr;

  // Check within a threshold in both directions (e.g., 1MB)
  uintptr_t threshold = 1024;

  return ptr_addr >= (stack_top_addr - threshold) && ptr_addr <= (stack_top_addr + threshold);
}

munit_case(RUN, test_basic_greeting, {
  char *result = get_full_greeting("Hello", "Alice", 20);
  munit_assert_string_equal(result, "Hello Alice", "Basic greeting should be correct");
  munit_assert_false(is_on_stack(result));
  free(result);
});

munit_case(SUBMIT, test_short_buffer, {
  char *result = get_full_greeting("Hey", "Bob", 4);
  munit_assert_string_equal(result, "Hey", "Should truncate to fit buffer");
  munit_assert_false(is_on_stack(result));
  free(result);
});


int main() {
  MunitTest tests[] = {
    munit_test("/test_basic_greeting", test_basic_greeting),
    munit_test("/test_short_buffer", test_short_buffer),
    munit_null_test,
  };

  MunitSuite suite = munit_suite("get_full_greeting", tests);

  return munit_suite_main(&suite, NULL, 0, NULL);
}
*/


// Another exzample:
int *allocate_scalar_array(int size, int multiplier) {
    int *new_arr = (int*)malloc(size * sizeof(int));
    if (new_arr == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        new_arr[i] = i * multiplier;
    }
    return new_arr;
}


// Freeing the memory allocated after each loop:
int main(){
    const int num_lists = 500;
    for (int i = 0; i < num_lists; i++) {
        int *lst = allocate_scalar_list(50000, 2);
        if (lst == NULL) {
            printf("Failed to allocate list\n");
            return 1;
        } else {
            printf("Allocated list %d\n", i);
        }
        free(lst);
    }
    return 0;
}
