#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char _binary_input_txt_start;
typedef unsigned int uint;
uint part_two = 0;

char get_move(char opponent_move, char input) {
    if (part_two) {
        char translation_table[3][3];
        translation_table['A' % 3]['X' % 3] = 'C';
        translation_table['B' % 3]['X' % 3] = 'A';
        translation_table['C' % 3]['X' % 3] = 'B';
        translation_table['A' % 3]['Y' % 3] = 'A';
        translation_table['B' % 3]['Y' % 3] = 'B';
        translation_table['C' % 3]['Y' % 3] = 'C';
        translation_table['A' % 3]['Z' % 3] = 'B';
        translation_table['B' % 3]['Z' % 3] = 'C';
        translation_table['C' % 3]['Z' % 3] = 'A';
        return translation_table[opponent_move % 3][input % 3];
    } else {
        char translation_table[3];
        translation_table['X' % 3] = 'A';
        translation_table['Y' % 3] = 'B';
        translation_table['Z' % 3] = 'C';
        return translation_table[input % 3];
    }
}

int main() {
    char* const env_part = getenv("part");
    part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);

    uint bonus_score[3];
    bonus_score['A' % 3] = 1;
    bonus_score['B' % 3] = 2;
    bonus_score['C' % 3] = 3;

    uint score_table[3][3];
    score_table['A' % 3]['A' % 3] = 3;
    score_table['B' % 3]['A' % 3] = 0;
    score_table['C' % 3]['A' % 3] = 6;
    score_table['A' % 3]['B' % 3] = 6;
    score_table['B' % 3]['B' % 3] = 3;
    score_table['C' % 3]['B' % 3] = 0;
    score_table['A' % 3]['C' % 3] = 0;
    score_table['B' % 3]['C' % 3] = 6;
    score_table['C' % 3]['C' % 3] = 3;

    char* ptr = strtok (&_binary_input_txt_start, "\n");
    uint score = 0;
    while (ptr != NULL) {
        char opponent_move = ptr[0];
        char my_move = get_move(opponent_move, (strstr(ptr, " ") + 1)[0]);
        score +=  score_table[opponent_move % 3][my_move % 3] + bonus_score[my_move % 3];

        ptr = strtok (NULL, "\n");
    }
    printf("%u\n", score);
}