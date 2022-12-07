#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char _binary_input_txt_start;
typedef unsigned int uint;

void part1() {
    uint sum = 0;
    char* ptr = strtok(&_binary_input_txt_start, "\n");
    while (ptr != NULL) {
        uint const len = strlen(ptr) / 2;

        char part1[len + 1];
        char part2[len + 1];
        strncpy(part1, ptr, len);
        strncpy(part2, ptr + len, len);
        part1[len] = '\0';
        part2[len] = '\0';

        uint counted[127] = {0};
        for (size_t i = 0; i < len; i++) {
            char item = part1[i];
            uint prio = 0;
            if (!counted[(uint)item] && strchr(part2, item) != NULL) {
                prio = (islower(item) ? item - 'a' + 1 : item - 'A' + 27);
                sum += prio;
                counted[(uint)item] = 1;
            }
        }
        ptr = strtok(NULL, "\n");
    }
    printf("%u\n", sum);
}

void part2() {
    uint sum = 0;
    char* ptr = strtok(&_binary_input_txt_start, "\n");
    while (ptr != NULL) {
        char first[100] = {};
        char second[100] = {};
        char third[100] = {};
        strcat(first, ptr);
        ptr = strtok(NULL, "\n");
        strcat(second, ptr);
        ptr = strtok(NULL, "\n");
        strcat(third, ptr);
        ptr = strtok(NULL, "\n");

        for (size_t i = 0; i < strlen(first); i++) {
            char item = first[i];
            if (strchr(second, item) != NULL && strchr(third, item) != NULL) {
                sum += (islower(item) ? item - 'a' + 1 : item - 'A' + 27);
                break;
            }
        }
    }

    printf("%u\n", sum);
}

int main() {
    char* const env_part = getenv("part");
    uint part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);
    if (part_two) {
        part2();
    } else {
        part1();
    }
}
