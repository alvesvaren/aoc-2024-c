#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* part1(char* input) {
    char* result = malloc(100); // Allocate memory for the result
    snprintf(result, 100, "Result for Part 1 with input length: %zu", strlen(input));
    return result;
}

char* part2(char* input) {
    return NULL;
}
