#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char _binary_input_txt_start;
typedef unsigned int uint;

uint all_unique(char block[], uint unique_needed) {
    uint count[127] = {};
    uint u = 0;
    for (u = 0; u < unique_needed; u++) {
        if (++count[(int)(block[u])] == 2) return 0;
    }
    return u;
}

int main()
{
    char *ptr = &_binary_input_txt_start;
    char *const env_part = getenv("part");
    uint const part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);
    uint const unique_needed = (part_two ? 14 : 4);

    uint const len = strlen(ptr) - 4;
    for (uint i = 0; i < len; i++)
    {
        char block[unique_needed + 1];
        memset(block, 0, sizeof(block));
        strncpy(block, ptr + i, unique_needed);
        block[unique_needed] = '\0';
        uint c = all_unique(block, unique_needed);
        if (c) {
            printf("%u\n", i + c);
            break;
        }
    }
}
