#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int part1(char* input) {
    int result = 0;

    int* num1s = malloc(0);
    int* num2s = malloc(0);
    int rows = 0;

    char* line = strtok(input, "\n");
    while (line != NULL) {
        int row = rows;
        rows++;
        num1s = realloc(num1s, rows * sizeof(int));
        num2s = realloc(num2s, rows * sizeof(int));

        num1s[row] = atoi(line);
        char* next_num_i = strstr(line, "   ") + (3 * sizeof(char));
        num2s[row] = atoi(next_num_i);
        
        line = strtok(NULL, "\n");
    }

    // sort each array
    for (int i = 0; i < rows; i++) {
        for (int j = i + 1; j < rows; j++) {
            if (num1s[i] > num1s[j]) {
                int temp = num1s[i];
                num1s[i] = num1s[j];
                num1s[j] = temp;
            }
            if (num2s[i] > num2s[j]) {
                int temp = num2s[i];
                num2s[i] = num2s[j];
                num2s[j] = temp;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        int num1 = num1s[i];
        int num2 = num2s[i];
        result += abs(num1 - num2);
    }

    free(num1s);
    free(num2s);

    return result;
}

int part2(char* input) {
    return 0;
}
