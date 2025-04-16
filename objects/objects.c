#include <stdio.h>
#include <stdlib.h>

typedef enum SnekObjectKind {
    INTEGER,
} snek_object_kind_t;

typedef union SnekObjectData {
    int v_int;
} snek_object_data_t;

typedef struct SnekObject {
    snek_object_kind_t kind;
    snek_object_data_t data;
} snek_object_t;

snek_object_t *new_snek_integer(int value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) {
        return NULL;
    }
  
    obj->kind = INTEGER;
    obj->data.v_int = value;
    return obj;
}
