#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define true 1
#define false 0

typedef struct SnekObject snek_object_t;

typedef struct {
    size_t size;
    snek_object_t **elements;
} snek_array_t;

typedef struct {
    snek_object_t *x;
    snek_object_t *y;
    snek_object_t *z;
} snek_vector_t;

typedef enum SnekObjectKind {
    INTEGER,
    FLOAT,
    STRING,
    VECTOR3,
    ARRAY,
} snek_object_kind_t;

typedef union SnekObjectData {
    int v_int;
    float v_float;
    char *v_string;
    snek_vector_t v_vector3;
    snek_array_t v_array;
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

snek_object_t *new_snek_float(float value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) {
        return NULL;
    }
  
    obj->kind = FLOAT;
    obj->data.v_float = value;
    return obj;
}

snek_object_t *new_snek_string(char *value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) {
        return NULL;
    }
  
    int len = strlen(value);
    char *dst = malloc(len + 1);
    if (dst == NULL) {
        free(obj);
        return NULL;
    }
  
    strcpy(dst, value);
  
    obj->kind = STRING;
    obj->data.v_string = dst;
    return obj;
}

snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
) {
    if (x == NULL || y == NULL || z == NULL) {
        return NULL;
    }

    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) {
        return NULL;
    }

    obj->kind = VECTOR3;
    obj->data.v_vector3 = (snek_vector_t){.x = x, .y = y, .z = z};
    return obj;
}

snek_object_t *new_snek_array(size_t size) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) {
        return NULL;
    }
  
    snek_object_t **elements = calloc(size, sizeof(snek_object_t *));
    if (elements == NULL) {
        free(obj);
        return NULL;
    }
  
    obj->kind = ARRAY;
    obj->data.v_array = (snek_array_t){.size = size, .elements = elements};
    return obj;
}

bool snek_array_set(snek_object_t *snek_obj, size_t index, snek_object_t *value) {
    if (snek_obj == NULL || value == NULL) return false;
    if (snek_obj->kind != ARRAY) return false;
    if (snek_obj->data.v_array.size <= index) return false;
    snek_obj->data.v_array.elements[index] = value;
    return true;
}
  
  snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index) {
    if (snek_obj == NULL) return NULL;
    if (snek_obj->kind != ARRAY) return NULL;
    if (snek_obj->data.v_array.size <= index) return NULL;
    return snek_obj->data.v_array.elements[index];
}

int snek_length(snek_object_t *obj) {
    if (obj == NULL) {
        return -1;
    }
  
    switch (obj->kind) {
        case INTEGER:
        case FLOAT:
            return 1;
        case STRING:
            return strlen(obj->data.v_string);
        case VECTOR3:
            return 3;
        case ARRAY:
            return obj->data.v_array.size;
        default:
            return -1;
    }
}

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
    if (a == NULL || b == NULL) {
        return NULL;
    }
  
    switch (a->kind) {
        case INTEGER:
            switch (b->kind) {
                case INTEGER:
                    return new_snek_integer(a->data.v_int + b->data.v_int);
                case FLOAT:
                    return new_snek_float((float)a->data.v_int + b->data.v_float);
                default:
                    return NULL;
        }
        case FLOAT:
            switch (b->kind) {
                case FLOAT:
                    return new_snek_float(a->data.v_float + b->data.v_float);
                default:
                    return snek_add(b, a);
        }
        case STRING:
            switch (b->kind) {
                case STRING: {
                    int a_len = strlen(a->data.v_string);
                    int b_len = strlen(b->data.v_string);
                    int len = a_len + b_len + 1;
                    char *dst = calloc(len, sizeof(char));
            
                    strcat(dst, a->data.v_string);
                    strcat(dst, b->data.v_string);
            
                    snek_object_t *obj = new_snek_string(dst);
                    free(dst);
            
                    return obj;
                }
                default:
                    return NULL;
            }
        case VECTOR3:
            switch (b->kind) {
                case VECTOR3:
                    return new_snek_vector3(
                        snek_add(a->data.v_vector3.x, b->data.v_vector3.x),
                        snek_add(a->data.v_vector3.y, b->data.v_vector3.y),
                        snek_add(a->data.v_vector3.z, b->data.v_vector3.z)
                    );
                default:
                    return NULL;
        }
        case ARRAY:
            switch (b->kind) {
                case ARRAY: {
                    size_t a_len = (size_t)snek_length(a);
                    size_t b_len = (size_t)snek_length(b);
                    size_t length = a_len + b_len;
            
                    snek_object_t *array = new_snek_array(length);
            
                    for (int i = 0; i < a_len; i++) {
                        snek_array_set(array, i, snek_array_get(a, i));
                    }
            
                    for (int i = 0; i < b_len; i++) {
                        snek_array_set(array, i + a_len, snek_array_get(b, i));
                    }
            
                    return array;
            }
            default:
                return NULL;
        }
    default:
        return NULL;
    }
}  
