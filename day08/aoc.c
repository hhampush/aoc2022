#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char _binary_input_txt_start;
typedef unsigned int uint;

uint part_two = 0;
enum dir { left = -1, right = 1, up = -1, down = 1, none = 0 };

struct tree {
    uint height;
    uint counted;
    uint scenic_score;
};

uint check(uint const width, struct tree map[width][width], uint const start_x, uint const start_y,
           enum dir const x_dir, enum dir const y_dir) {
    if ((!part_two && map[start_x][start_y].counted) || (start_x == 0 && start_y == 0))
        return 0;

    uint visible = 1;
    uint const tree_height = map[start_x][start_y].height;

    uint trees_in_view = 0;
    int var = (x_dir != none) ? start_x + x_dir : start_y + y_dir;
    for (;;) {
        if ((x_dir == left || y_dir == up) && var < 0)
            break;
        else if ((x_dir == right || y_dir == down) && var == width)
            break;
        else if (x_dir != none && map[var][start_y].height >= tree_height) {
            trees_in_view++;
            visible = 0;
            break;
        } else if (y_dir != none && map[start_x][var].height >= tree_height) {
            trees_in_view++;
            visible = 0;
            break;
        } else {
            trees_in_view++;
            var += x_dir;
            var += y_dir;
        }
    }

    if (part_two)
        map[start_x][start_y].scenic_score *= trees_in_view;

    if (visible) {
        map[start_x][start_y].counted = 1;
        return 1;
    }
    return 0;
}

int main() {
    char* const env_part = getenv("part");
    part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);
    char* ptr = strtok(&_binary_input_txt_start, "\n");

    uint const width = strlen(ptr);
    struct tree map[width][width];
    memset(map, 0, sizeof(map));
    uint y = 0;
    while (ptr != NULL) {
        uint x = 0;
        for (uint i = 0; i < strlen(ptr); i++) {
            struct tree t;
            t.height = ptr[i] - '0';
            t.scenic_score = 1;
            t.counted = 0;
            map[x++][y] = t;
        }
        y++;
        ptr = strtok(NULL, "\n");
    }

    uint highest_scenic_score = 0;
    uint num_visible = 0;
    for (uint y = 0; y < width; y++) {
        for (uint x = 0; x < width; x++) {
            if (((y == 0 || y == width - 1) && x > 0) || ((x == 0 || x == width - 1) && y > 0)) {
                num_visible++;  // always count edge trees
            } else {
                num_visible += check(width, map, x, y, left, none);
                num_visible += check(width, map, x, y, right, none);
                num_visible += check(width, map, x, y, none, up);
                num_visible += check(width, map, x, y, none, down);

                if (part_two && map[x][y].scenic_score > highest_scenic_score) {
                    highest_scenic_score = map[x][y].scenic_score;
                }
            }
        }
    }

    if (part_two)
        printf("%u\n", highest_scenic_score);
    else
        printf("%u\n", num_visible + 1);
}
