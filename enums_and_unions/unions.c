#include <stdio.h>
#include <stdint.h>

// Unions are a combination of both structs and enums. Kind of like dynamic variables in python.
typedef enum SnekObjectKind {
    INTEGER = 0,
    STRING = 1,
} snek_object_kind_t;
  
typedef union SnekObjectData {
    int v_int;
    char *v_string;
} snek_object_data_t;
  
typedef struct SnekObject {
    snek_object_kind_t kind;
    snek_object_data_t data;
} snek_object_t;

void format_object(snek_object_t obj, char *buffer) {
    switch (obj.kind) {
        case INTEGER:
            sprintf(buffer, "int:%d", obj.data.v_int);
            break;
        case STRING:
            sprintf(buffer, "string:%s", obj.data.v_string);
            break;
        default:
            sprintf(buffer, "unknown");
            break;
    }
}

snek_object_t new_integer(int i) {
    return (snek_object_t){
        .kind = INTEGER,
        .data = {.v_int = i}
    };
}
  
snek_object_t new_string(char *str) {
    return (snek_object_t){
        .kind = STRING,
        .data = {.v_string = str}
    };
}



/* PacketHeader union. It has two potential fields:
    tcp_header: A struct:
        The first 2 bytes are the src_port.
        The next 2 bytes are the dest_port.
        The last 4 bytes are the seq_num.
    raw: An array of 8 bytes.
Use uint8_t, uint16_t, and uint32_t for the types of the fields, based on the number of bytes needed. 
Remember, 8 bits = 1 byte.
*/
typedef union PacketHeader{
    struct {
        uint16_t src_port;
        uint16_t dest_port;
        uint32_t seq_num;
    } tcp_header;
    uint8_t raw[8];
} packet_header_t;
