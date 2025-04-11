#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long size_of_addr(long long i) {
    // accepts a long long (a potentially very large integer) as input and returns the size of its address.
    unsigned long sizeof_snek_version = sizeof(&i);
    return sizeof_snek_version;
}



typedef struct CodeFile {
    int lines;
    int filetype;
} codefile_t;

codefile_t change_filetype(codefile_t *f, int new_filetype) {
    /* Accept a pointer to a code file
    Dereference the pointer into a codefile_t struct
    Change the filetype field to the provided new_filetype value
    Return the updated codefile_t struct */
    codefile_t new_f = *f;
    new_f.filetype = new_filetype;
    return new_f;
}



typedef struct Graphics {
    int fps;
    int height;
    int width;
} graphics_t;

void dump_graphics(graphics_t gsettings[10]) {
    // Iterates over the known number of integers in the array of structs (gsettings)
    int *ptr = (int *)gsettings;
    for (int i = 0; i < 30; i++) {
        printf("settings[%d] = %d\n", i, ptr[i]);
    }
}


/* Run it and take a look at the output. 
You'll notice that due to the array decaying to a pointer, the reported size is the size of a pointer, 
not the size of the actual array. */ 
void core_utils_func(int core_utilization[]) {
    printf("sizeof core_utilization in core_utils_func: %zu\n", sizeof(core_utilization));
}

int main() {
    int core_utilization[] = {43, 67, 89, 92, 71, 43, 56, 12};
    int len = sizeof(core_utilization) / sizeof(core_utilization[0]);
    printf("sizeof core_utilization in main: %zu\n", sizeof(core_utilization));
    printf("len of core_utilization: %d\n", len);
    core_utils_func(core_utilization);
    return 0;
}


//  Appends str2 to the end of str1 in place.
void concat_strings(char *str1, const char *str2) {
    char *end = str1;
    while (*end != '\0') {
        end++;
    }
    while (*str2 != '\0') {
        *end = *str2;
        end++;
        str2++;
    }
    *end = '\0';
}


/* It appends a src string to a dest TextBuffer struct.
It's called a "smart" append because the destination buffer is a fixed 64 bytes, and it:
    Checks for available space before appending.
    Appends as much as possible if there's not enough space.
    Always ensures the buffer remains null-terminated.
    Returns a status indicating whether the full append was possible.
*/
typedef struct {
    size_t length;
    char buffer[64];
} TextBuffer;

int smart_append(TextBuffer* dest, const char* src) {
    if (!dest || !src) return 1;
    const int max_buffer_size = 64;
    size_t src_len = strlen(src);
    size_t available_space = max_buffer_size - dest->length - 1;
    if (src_len > available_space) {
        strncat(dest->buffer, src, available_space);
        dest->length = max_buffer_size - 1;
        return 1;
    }
    strcat(dest->buffer, src);
    dest->length += src_len;
    return 0;
}



// Forward Declaration: when you have a struct that may need to reference itself, or be used recursively.
typedef struct SnekObject snekobject_t;

typedef struct SnekObject {
    char *name;
    snekobject_t *child;
} snekobject_t;

snekobject_t new_node(char *name) {
    snekobject_t node = {
        .name = name,
        .child = NULL
    };
    return node;
}



// Mutual Structs:
// Forward declarations can also be used when two structs reference each other (a circular reference).
typedef struct Employee employee_t;
typedef struct Department department_t;

typedef struct Employee {
    // Employee references Department
    int id;
    char *name;
    department_t *department;
} employee_t;

typedef struct Department {
    // Department references Employee
    char *name;
    employee_t *manager;
} department_t;

employee_t create_employee(int id, char *name) {
    employee_t emp = {
        .id = id,
        .name = name,
        .department = NULL
    };
    return emp;
}
  
department_t create_department(char *name) {
    department_t dept = {
        .name = name,
        .manager = NULL
    };
    return dept;
}
  
void assign_employee(employee_t *emp, department_t *department) {
    emp->department = department;
}
  
void assign_manager(department_t *dept, employee_t *manager) {
    dept->manager = manager;
}
