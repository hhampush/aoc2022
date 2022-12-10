#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char _binary_input_txt_start;
typedef unsigned int uint;

#define GRID_SIZE 512
#define START_X GRID_SIZE / 2
#define START_Y GRID_SIZE / 2

uint visited_grid[GRID_SIZE][GRID_SIZE] = {0};

void adjust_tail(uint* x, uint* y, uint const leader_x, uint const leader_y, uint is_tail) {
    uint const x_distance = abs(leader_x - *x);
    uint const y_distance = abs(leader_y - *y);
    uint should_adjust = 0;

    if (x_distance > 1 || y_distance > 1)
        should_adjust = 1;
    if (should_adjust && x_distance >= 1) {
        if (leader_x > *x)
            *x += 1;
        else
            *x -= 1;
    }
    if (should_adjust && y_distance >= 1) {
        if (leader_y > *y)
            *y += 1;
        else
            *y -= 1;
    }

    if (is_tail)
        visited_grid[*x][*y]++;
}

int main() {
    char* const env_part = getenv("part");
    uint const part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);
    char* ptr = strtok(&_binary_input_txt_start, "\n");

    uint const knots = (part_two ? 10 : 2);
    uint knots_x[knots];
    uint knots_y[knots];
    for (uint i = 0; i < knots; i++) {
        knots_x[i] = START_X;
        knots_y[i] = START_Y;
    }

    visited_grid[knots_x[knots - 1]][knots_y[knots - 1]] = 1;
    char dir = '\0';
    uint target_x = knots_x[0], target_y = knots_y[0];
    while (ptr != NULL) {
        uint distance = 0;
        if (sscanf(ptr, "%c %u", &dir, &distance) == 2) {
            if (dir == 'U')
                target_y = knots_y[0] - distance;
            else if (dir == 'D')
                target_y = knots_y[0] + distance;
            else if (dir == 'L')
                target_x = knots_x[0] - distance;
            else if (dir == 'R')
                target_x = knots_x[0] + distance;
        }
        while (knots_x[0] != target_x) {
            knots_x[0] += (target_x > knots_x[0] ? 1 : -1);
            for (uint i = 1; i < knots; i++) {
                adjust_tail(&knots_x[i], &knots_y[i], knots_x[i - 1], knots_y[i - 1], (i == knots - 1));
            }
        }
        while (knots_y[0] != target_y) {
            knots_y[0] += (target_y > knots_y[0] ? 1 : -1);
            for (uint i = 1; i < knots; i++) {
                adjust_tail(&knots_x[i], &knots_y[i], knots_x[i - 1], knots_y[i - 1], (i == knots - 1));
            }
        }
        ptr = strtok(NULL, "\n");
    }
    uint count = 0;
    for (uint y = 0; y < GRID_SIZE; y++) {
        for (uint x = 0; x < GRID_SIZE; x++) {
            if (visited_grid[x][y]) {
                count++;
            }
        }
    }

    printf("%u\n", count);
}
