#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char _binary_input_txt_start;
typedef unsigned int uint;

int main() {
    char* const env_part = getenv("part");
    uint const part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);
    char* ptr = strtok(&_binary_input_txt_start, "\n");

    uint sum = 0;
    uint cycle = 1;
    int x_register = 1;
    int val_to_add = 0;
    int work_cycles = 0;
    uint counted_cycle = 0;
    uint position = 0;
    while (ptr != NULL || work_cycles > 0) {
        if (work_cycles > 0) {
            if (--work_cycles == 0) {
                x_register += val_to_add;
                ptr = strtok(NULL, "\n");
            }
            counted_cycle = 0;
            cycle++;
        } else if (strcmp(ptr, "noop") == 0) {
            counted_cycle = 0;
            cycle++;
            ptr = strtok(NULL, "\n");
        } else if (sscanf(ptr, "addx %d", &val_to_add) == 1) {
            work_cycles = 2;
        }

        if (!counted_cycle++) {  // act on cycle only once, cycle might not step every loop
            if (part_two) {
                if ((x_register == position - 1) || (x_register == position) || (x_register == position + 1)) {
                    putc('#', stdout);
                } else {
                    putc('.', stdout);
                }

                if (position++ == 39) {
                    position = 0;
                    putc('\n', stdout);
                }
            } else {
                if (cycle == 20 || (cycle >= 60 && (cycle % 40 == 20))) {
                    sum += cycle * x_register;
                }
            }
        }
    }

    if (!part_two)
        printf("%u\n", sum);
}
