#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
extern char _binary_input_txt_start;
extern char _binary_input_txt_end;
typedef unsigned int uint;

int compare (void const * a, void const * b) {
   return (*(int*)b - *(int*)a);
}

int main() {
    char* ptr = &_binary_input_txt_start;
    char* const env_part = getenv("part");
    uint const part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);
    uint values[1000] = {0};
    uint elf = 0;

    while (ptr != NULL) {
        uint val = strtoul(ptr++, &ptr, 10);

        values[elf] += val;

        if (*ptr == '\n' && *(ptr+1) == '\n') elf++;
        else if (*ptr == '\0') break;
    }

    qsort(values, elf + 1, sizeof(uint), compare);

    if (part_two) {
        uint sum = 0;      
        for (size_t i = 0; i < 3; i++) {
            sum += values[i];
        }
        printf("%u\n", sum);
    } else {
        printf("%u\n", values[0]);
    }
}
