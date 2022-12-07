#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char _binary_input_txt_start;
typedef unsigned long int ulint;
typedef unsigned int uint;

#define TABLE_SIZE 100000
#define SPECIAL_ROOT_INDEX 99999
#define DIR_NAME_BUFFER_SIZE 255
#define PATH_BUFFER_SIZE 8192

// good ol' djb2 http://www.cse.yorku.ca/~oz/hash.html
uint hash(char *str) {
    ulint hash = 5381;
    uint c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

ulint file_size_per_dir[TABLE_SIZE];

void parse_dirtree() {
    char current_path[PATH_BUFFER_SIZE] = "";
    char *ptr = strtok(&_binary_input_txt_start, "\n");
    while (ptr != NULL) {
        if (ptr[0] == '$') {
            char dir[DIR_NAME_BUFFER_SIZE] = "";
            if (sscanf(ptr + 2, "cd %s", dir) == 1) {
                if (strcmp(dir, "/") == 0) {
                    current_path[0] = '/';
                    current_path[1] = '\0';
                } else if (strcmp(dir, "..") == 0) {
                    char *pos = strrchr(current_path, '/');
                    *pos = '\0';
                } else {
                    strncat(current_path, "/", 1);
                    strcat(current_path, dir);
                }
            }
        } else {
            uint const dir_hash = hash(current_path);
            uint file_size = 0;
            if (sscanf(ptr, "%u", &file_size) == 1) {
                file_size_per_dir[SPECIAL_ROOT_INDEX] += file_size;
                if (strcmp(current_path, "/") != 0) {
                    char path_cpy[PATH_BUFFER_SIZE] = "";
                    strcpy(path_cpy, current_path);
                    char *parents = strrchr(path_cpy, '/');
                    while (parents != NULL) {
                        *parents = '\0';
                        if (strcmp(path_cpy, "/") != 0 && strlen(path_cpy) > 0) {
                            file_size_per_dir[hash(path_cpy)] += file_size;
                        }
                        parents = strrchr(path_cpy, '/');
                    }
                    file_size_per_dir[dir_hash] += file_size;
                }
            }
        }
        ptr = strtok(NULL, "\n");
    }
}

int main() {
    char *const env_part = getenv("part");
    uint const part_two = (env_part != NULL) && (strcmp(env_part, "part2") == 0);

    parse_dirtree();
    ulint sum = 0;
    uint smallest_deletion = UINT_MAX;
    for (uint i = 0; i < TABLE_SIZE; i++) {
        ulint const size = file_size_per_dir[i];
        if (!part_two && size <= 100000) {
            sum += size;
        }
        if (part_two) {
            uint const unused = 70000000 - file_size_per_dir[SPECIAL_ROOT_INDEX];
            if (unused + size >= 30000000) {
                if (size < smallest_deletion) {
                    smallest_deletion = size;
                }
            }
        }
    }

    if (part_two)
        printf("%u\n", smallest_deletion);
    else
        printf("%lu\n", sum);
}
