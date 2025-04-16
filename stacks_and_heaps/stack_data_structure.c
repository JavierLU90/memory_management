#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* We're going to implement a stack again, 
but this time we're going to do it while manually managing the memory of generic pointers!

We'll get to have our first deeper exploration of "generics" in C (remember, that just means void *) 
as well as creating a data structure we will later use in our mark-and-sweep garbage collector.
*/
typedef struct Stack {
    size_t count;
    size_t capacity;
    void **data;
} stack_t;

// Handles the memory allocation for the Stack struct
stack_t *stack_new(size_t capacity) {
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack == NULL) {
        return NULL;
    }
  
    stack->count = 0;
    stack->capacity = capacity;
    stack->data = malloc(stack->capacity * sizeof(void *));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }
  
    return stack;
}

/* Stack Push
It safe(ish)ly adds a new object to the top of the stack. 
Remember: the size of the data array is the capacity of the stack, 
and the number of elements that are actually in the stack is the count 
(which is less than or equal to the capacity).

Whenever it runs out of capacity, it'll double it's capacity.
*/
void stack_push(stack_t *stack, void *obj) {
    if (stack->count == stack->capacity) {
        stack->capacity *= 2;
        void **temp = realloc(stack->data, stack->capacity * sizeof(void *));
        if (temp == NULL) {
            stack->capacity /= 2;
            return;
        }
        stack->data = temp;
    }
    stack->data[stack->count] = obj;
    stack->count++;
    return;
}

/* Stack Pop
If the stack is empty, return NULL.
Decrement the stack's count.
Return the top element of the stack (the count-th element in the array).
*/
void *stack_pop(stack_t *stack) {
    if (stack->count == 0) {
        return NULL;
    }
    stack->count--;
    return stack->data[stack->count];
}

/* Stack Free
Function that will clean up all the memory that has been allocated for the stack.
*/
void stack_free(stack_t *stack) {
    if (stack == NULL) {
        return;
    }
    if (stack->data != NULL) {
        free(stack->data);
    }
    free(stack);
}

// Dangerous Push
// Example of pushing an int * and a regular old int directly onto the stack (a bad idea).
void scary_double_push(stack_t *s) {
    stack_push(s, (void *)1337);
  
    int *i = malloc(sizeof(int));
    *i = 1024;
    stack_push(s, i);
}
// Example of pushing an float * and a string (char *) directly onto the stack (a bad idea).
void stack_push_multiple_types(stack_t *s) {
    float *f = malloc(sizeof(float));
    if (f != NULL) {
        *f = 3.14f;
    }
    stack_push(s, f);
  
    const char *string = "Sneklang is blazingly slow!";
    size_t len = strlen(string) + 1;
  
    char *c = malloc(sizeof(char) * len);
    if (c != NULL) {
        strcpy(c, string);
    }
    stack_push(s, c);
}
