#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <deque>
extern char _binary_input_txt_start;
typedef unsigned int uint;

int main()
{
    char *ptr = strtok(&_binary_input_txt_start, "\n");
    char *const env_part = getenv("part");
    uint const part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);
    std::deque<uint> stack[9];
    while (ptr != NULL)
    {
        if (ptr[0] == ' ' || ptr[0] == '[') {
            uint const len = strlen(ptr);
            for (uint i = 1; i < len; i += 4) {
                if (isupper(ptr[i])) {
                    stack[i / 4].emplace_back(ptr[i]);
                }
            }
        } else {
            uint amount = 0, from = 0, to = 0;
            sscanf(ptr, "move %u from %u to %u", &amount, &from, &to);
            char to_move[amount];
            uint const from_idx = from - 1;
            uint const to_idx = to - 1;
            for (uint i = 0; i < amount; i++) {
                if (part_two) {
                    to_move[amount - i - 1] = stack[from_idx].front();
                    stack[from_idx].pop_front();
                } else {
                    stack[to_idx].emplace_front(stack[from_idx].front());
                    stack[from_idx].pop_front();
                }
            }
            if (part_two) {
                for (uint i = 0; i < amount; i++) {
                    stack[to_idx].emplace_front(to_move[i]);
                }
            }
        }

        ptr = strtok(NULL, "\n");
    }

    for (uint i = 0; i < 9; i++) {
        fputc(stack[i].front(), stdout);
    }
}
