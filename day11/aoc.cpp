#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>  // some c++ again :(

extern char _binary_input_txt_start;
#define NR_MONKEYS 8

typedef struct monkey {
    std::vector<uint64_t> items;
    char op_a[4];
    char op_b[4];
    char operand;
    uint test_divisible;
    uint true_throw_to;
    uint false_throw_to;
    uint inspect_count;
} monkey_t;
monkey_t monkeys[NR_MONKEYS];

void parse_monkey(uint const monkey, char* ptr) {
    monkey_t m = {};
    uint lines = 0;
    while (ptr != NULL) {
        uint test = 0;
        uint throw_to = 0;
        if (strstr(ptr, "Starting items: ") != NULL) {
            char* items_str = ptr + 18;
            uint item = 0;
            while (sscanf(items_str, "%u", &item) == 1) {
                m.items.push_back(item);
                char* next = strstr(items_str, ", ");
                if (next == NULL)
                    break;
                items_str = next + 2;
            }
        } else if (sscanf(ptr, "  Operation: new = %s %c %s", m.op_a, &m.operand, m.op_b) == 3) {
            ;
        } else if (sscanf(ptr, "  Test: divisible by %u", &test) == 1) {
            m.test_divisible = test;
        } else if (sscanf(ptr, "    If true: throw to monkey %u", &throw_to) == 1) {
            m.true_throw_to = throw_to;
        } else if (sscanf(ptr, "    If false: throw to monkey %u", &throw_to) == 1) {
            m.false_throw_to = throw_to;
        }
        if (++lines == 6)
            break;
        ptr = strtok(NULL, "\n");
    }
    monkeys[monkey] = m;
}

void parse_operand(uint64_t const old, char const* string, uint64_t* out_op) {
    if (isdigit(string[0])) {
        *out_op = atoi(string);
    } else if (strcmp(string, "old") == 0) {
        *out_op = old;
    }
}

int compare(void const* a, void const* b) {
    return (*(int*)b - *(int*)a);
}

uint64_t lcm(uint64_t const a, uint64_t const b) {
    uint64_t max = (a > b) ? a : b;
    for (;; max++) {
        if ((max % a == 0) && (max % b == 0)) {
            return max;
        }
    }
}

int main() {
    char* const env_part = getenv("part");
    uint const part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);
    char* ptr = strtok(&_binary_input_txt_start, "\n");

    while (ptr != NULL) {
        uint monkey = 0;
        if (sscanf(ptr, "Monkey %u", &monkey) == 1) {
            parse_monkey(monkey, ptr);
        }
        ptr = strtok(NULL, "\n");
    }

    uint64_t const lowest_common = lcm(
        monkeys[0].test_divisible,
        lcm(monkeys[1].test_divisible,
            lcm(monkeys[2].test_divisible,
                lcm(monkeys[3].test_divisible,
                    lcm(monkeys[4].test_divisible,
                        lcm(monkeys[5].test_divisible, lcm(monkeys[6].test_divisible, monkeys[7].test_divisible)))))));

    uint const rounds = (part_two ? 10000 : 20);
    for (uint round = 0; round < rounds; round++) {
        for (uint m = 0; m < NR_MONKEYS; m++) {
            auto it = monkeys[m].items.begin();
            while (it != monkeys[m].items.end()) {
                monkeys[m].inspect_count++;
                uint64_t op_a = 0;
                uint64_t op_b = 0;
                parse_operand(*it, monkeys[m].op_a, &op_a);
                parse_operand(*it, monkeys[m].op_b, &op_b);

                uint64_t value =
                    (monkeys[m].operand == '+')
                        ? (op_a + op_b)
                        : ((monkeys[m].operand == '-') ? (op_a - op_b)
                                                       : ((monkeys[m].operand == '*') ? (op_a * op_b) : 0));
                if (!part_two)
                    value /= 3;
                else
                    value %= lowest_common;

                if (value % monkeys[m].test_divisible == 0) {
                    monkeys[monkeys[m].true_throw_to].items.push_back(value);
                } else {
                    monkeys[monkeys[m].false_throw_to].items.push_back(value);
                }

                it = monkeys[m].items.erase(it);
            }
        }
    }

    uint inspection_list[NR_MONKEYS] = {};
    for (uint m = 0; m < NR_MONKEYS; m++) {
        inspection_list[m] = monkeys[m].inspect_count;
    }
    qsort(inspection_list, NR_MONKEYS, sizeof(uint), compare);
    printf("%lu\n", (uint64_t)inspection_list[0] * (uint64_t)inspection_list[1]);
}
