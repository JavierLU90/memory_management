#include "stdlib.h"
#include <stdio.h>
#include <string.h>

/* It accepts a pointer to a pointer to an integer called pointer_pointer, and a raw value. 
Changes the value of pointer_pointer's pointer's address to point to new memory that has the value of the int.
*/
void allocate_int(int **pointer_pointer, int value) {
    int *new_pointer = (int*)malloc(sizeof(int));
    if (new_pointer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
    }
    *new_pointer = value;
    *pointer_pointer = new_pointer;
}


// Example that uses and array of pointers
// "Tokens" - strings of text that represent syntax, things like if, else and def.
typedef struct Token {
    char* literal;
    int line;
    int column;
} token_t;

token_t** create_token_pointer_array(token_t* tokens, size_t count) {
    token_t** token_pointers = malloc(count * sizeof(token_t*));
    if (token_pointers == NULL) {
        exit(1);
    }
    for (size_t i = 0; i < count; ++i) {
        // Allocate memory for a new token
        token_t *new_token = malloc(sizeof(token_t));
        if (new_token == NULL) {
            exit(1);
        }
        // Copy token data
        new_token->literal = tokens[i].literal;
        new_token->line = tokens[i].line;
        new_token->column = tokens[i].column;
    
        // Store the address in the array
        token_pointers[i] = new_token;
    }
    return token_pointers;
}
  

/* VOID POINTERS:

A void * "void pointer" tells the compiler that this pointer could point to anything. 
This is why void pointers are also known as a "generic pointer". 
Since void pointers do not have a specific data type, they cannot be directly dereferenced or used in pointer arithmetic without casting them to another pointer type first.
*/
typedef enum SnekObjectKind {
    INTEGER,
    FLOAT,
    BOOL,
} snek_object_kind_t;
  
typedef struct SnekInt {
    char *name;
    int value;
} snek_int_t;
  
typedef struct SnekFloat {
    char *name;
    float value;
} snek_float_t;
  
typedef struct SnekBool {
    char *name;
    unsigned int value;
} snek_bool_t;

// It should "zero out" the .value field of the struct by setting it to the zero value of its type. 
// Uses the kind parameter to figure out which type of struct it is working with.
void snek_zero_out(void *ptr, snek_object_kind_t kind){
    switch(kind){
        case INTEGER:
            ((snek_int_t*)ptr)->value = 0;
            break;
        case FLOAT:
            ((snek_float_t*)ptr)->value = 0.0;
            break;
        case BOOL:
            ((snek_bool_t*)ptr)->value = 0;
            break;
    }
}


// Swapping Ints:
// It accepts two pointers to integers, and should swap the values of the integers they point to.
void swap_ints(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


// Swapping Strings:
void swap_strings(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}
/* This function swaps two string pointers. Let's break it down:
    1. void swap_strings(char **a, char **b) - The function takes two parameters:
        each a pointer to a char pointer (or a double pointer). 
        This means we can modify where those pointers point to.
    2. char *temp = *a
        We create a temporary char pointer variable and store what a is pointing to 
        (which is itself a pointer to a string).
    3. *a = *b
        We set what a points to, to be what b points to. 
        So now a points to the string that b was pointing to.
    4. *b = temp
        We set what b points to, to be what we saved in temp (the original string a was pointing to).
This is the standard pattern for swapping values: save one in a temporary variable, 
replace it with the other, then put the saved value in place of the other.
*/


// Generic Swap:
/* 
1. Allocates memory for a temporary buffer to store the data using malloc.
2. If the allocation fails (returns NULL) return immediately.
3. Uses memcpy to shuffle the data around.
4. Frees the temporary buffer.
*/
void swap(void *vp1, void *vp2, size_t size) {
    void *buffer = malloc(size * sizeof(void *));
    if (buffer == NULL) {
        exit(1);
    }
    memcpy(buffer, vp1, size);
    memcpy(vp1, vp2, size);
    memcpy(vp2, buffer, size);
    free(buffer);
}
