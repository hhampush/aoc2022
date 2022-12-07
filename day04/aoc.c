#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char _binary_input_txt_start;
typedef unsigned int uint;

char* save_ptr_one;
char* save_ptr_two;

void get_sections(char* segment, char* output) {
    char* sections = __strtok_r(segment, "-", &save_ptr_two);
    uint left = atoi(sections);
    sections = __strtok_r(NULL, "-", &save_ptr_two);
    uint right = atoi(sections);

    if (left > right) {
        uint tmp = left;
        left = right;
        right = tmp;
    }

    for (uint i = left; i <= right; i++) {
        char num[5] = {};
        sprintf(num, "[%2u]", i);
        strcat(output, num);
    }
}

uint find_all_overlap(char* left, char* right) {
    for (int i = 0; i < strlen(left); i += 4) {
        char tmp[5];
        strncpy(tmp, left + i, 4);
        if (strstr(right, tmp) != NULL) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char* const env_part = getenv("part");
    uint const part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);
    char* ptr = __strtok_r(&_binary_input_txt_start, "\n", &save_ptr_one);

    uint count = 0;
    while (ptr != NULL) {
        char output_left[512] = {};
        char output_right[512] = {};

        char* segment = strtok(ptr, ",");
        get_sections(segment, output_left);
        segment = strtok(NULL, ",");
        get_sections(segment, output_right);

        if (part_two) {
            uint i = find_all_overlap(output_left, output_right);
            if (!i)
                i = find_all_overlap(output_right, output_left);
            count += i;
        } else if (strstr(output_left, output_right) != NULL || strstr(output_right, output_left) != NULL) {
            count++;
        }

        ptr = __strtok_r(NULL, "\n", &save_ptr_one);
    }
    printf("%u\n", count);
}