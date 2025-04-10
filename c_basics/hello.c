#include <stdio.h>

int main() {
    int sneklang_default_max_threads = 8;
  char sneklang_default_perms = 'r';
  float sneklang_default_pi = 3.141592;
  char *sneklang_title = "Sneklang";
  // don't touch above this line

  printf("Default max threads: %d\n", sneklang_default_max_threads);
  printf("Custom perms: %c\n", sneklang_default_perms);
  printf("Constant pi value: %f\n", sneklang_default_pi);
  printf("Sneklang title: %s\n", sneklang_title);

  return 0;
}

// This is a single-line comment

/*
    int - An integer
    float - A floating point number
    char - A character
    char * - An array of characters

Common format specifiers are:
    %d - digit (integer)
    %c - character
    %f - floating point number
    %s - string (char *)

printf("Hello, %s. You're %d years old.\n", name, age);
*/
