#include <stdio.h>

// How to declare an Enum
typedef enum Color {
    RED = 55,
    GREEN = 176,
    BLUE = 38,
} color_t;



// Use enums in switch stetements
typedef enum {
    HTTP_BAD_REQUEST = 400,
    HTTP_UNAUTHORIZED = 401,
    HTTP_NOT_FOUND = 404,
    HTTP_TEAPOT = 418,
    HTTP_INTERNAL_SERVER_ERROR = 500
} HttpErrorCode;

char *http_to_str(HttpErrorCode code) {
    switch (code) {
        case HTTP_BAD_REQUEST:
            return "400 Bad Request";
        case HTTP_UNAUTHORIZED:
            return "401 Unauthorized";
        case HTTP_NOT_FOUND:
            return "404 Not Found";
        case HTTP_TEAPOT:
            return "418 I AM A TEAPOT!";
        case HTTP_INTERNAL_SERVER_ERROR:
            return "500 Internal Server Error";
        default:
            return "Unknown HTTP status code";
    }
}

// Sizeof Enum
int main() {
    printf("The size of Color is %zu bytes\n", sizeof(color_t));
    printf("The size of HttpErrorCode is %zu bytes\n", sizeof(HttpErrorCode));
    return 0;
}
