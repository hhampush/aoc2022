#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char _binary_input_txt_start;
typedef unsigned int uint;
uint part_two = 0;

uint const A_INDEX = 'A' % 3;
uint const B_INDEX = 'B' % 3;
uint const C_INDEX = 'C' % 3;
uint const X_INDEX = 'X' % 3;
uint const Y_INDEX = 'Y' % 3;
uint const Z_INDEX = 'Z' % 3;

int main() {
    char* const env_part = getenv("part");
    part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);

    uint bonus_score[3];
    bonus_score[A_INDEX] = 1;
    bonus_score[B_INDEX] = 2;
    bonus_score[C_INDEX] = 3;

    uint score_table[3][3];
    score_table[A_INDEX][A_INDEX] = 3;
    score_table[B_INDEX][A_INDEX] = 0;
    score_table[C_INDEX][A_INDEX] = 6;
    score_table[A_INDEX][B_INDEX] = 6;
    score_table[B_INDEX][B_INDEX] = 3;
    score_table[C_INDEX][B_INDEX] = 0;
    score_table[A_INDEX][C_INDEX] = 0;
    score_table[B_INDEX][C_INDEX] = 6;
    score_table[C_INDEX][C_INDEX] = 3;

    char translation_table_part_two[3][3];
    translation_table_part_two[A_INDEX][X_INDEX] = 'C';
    translation_table_part_two[B_INDEX][X_INDEX] = 'A';
    translation_table_part_two[C_INDEX][X_INDEX] = 'B';
    translation_table_part_two[A_INDEX][Y_INDEX] = 'A';
    translation_table_part_two[B_INDEX][Y_INDEX] = 'B';
    translation_table_part_two[C_INDEX][Y_INDEX] = 'C';
    translation_table_part_two[A_INDEX][Z_INDEX] = 'B';
    translation_table_part_two[B_INDEX][Z_INDEX] = 'C';
    translation_table_part_two[C_INDEX][Z_INDEX] = 'A';

    char translation_table_part_one[3];
    translation_table_part_one[X_INDEX] = 'A';
    translation_table_part_one[Y_INDEX] = 'B';
    translation_table_part_one[Z_INDEX] = 'C';

    char* ptr = strtok(&_binary_input_txt_start, "\n");
    uint score = 0;
    while (ptr != NULL) {
        char const opponent_move = ptr[0];
        char const input = (strstr(ptr, " ") + 1)[0];
        char my_move;

        if (part_two)
            my_move = translation_table_part_two[opponent_move % 3][input % 3];
        else
            my_move = translation_table_part_one[input % 3];

        score += score_table[opponent_move % 3][my_move % 3] + bonus_score[my_move % 3];

        ptr = strtok(NULL, "\n");
    }
    printf("%u\n", score);
}
