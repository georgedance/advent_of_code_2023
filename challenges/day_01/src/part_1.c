#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int my_atoi(char c) {
    switch(c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        default:  return -1;
    }
}

int main(int argc, char *argv[]) {

    if(argc < 2) {
        //print_usage();
        printf("Usage: %s [FILE...]\n", argv[0]);
        puts("Made for Part 1 of Day 1 of Advent of Code 2023!");
        puts("It scans thru the input files, finding the first and last digit on each line.");
        puts("It uses the first digit as the 10's place and the last digit as the 1's place.");
        puts("It then adds the numbers gathered on each line to get the total for each file.");
        puts("If you are having troubles, ensure the file ends with a newline character.");
        return EXIT_FAILURE;
    }

    for(int z = 1; z < argc; z++) {

        FILE *file_data = fopen(argv[z], "r");
        fseek(file_data, 0, SEEK_END);
        unsigned long file_size = ftell(file_data);
        rewind(file_data);

        char input[file_size];

        fread(input, 1, file_size, file_data);
        fclose(file_data);

        int line_count = 0;

        for(uint i = 0; i < file_size; i++) {
            if(input[i] == '\n') {
                line_count++;
            }
        }

        char cursor;

        int first_num;
        int last_num;
        int line_num_total[line_count];

        line_count = 0;

        int nums_on_line = 0;

        for(uint i = 0; i < file_size; i++) {
            cursor = input[i];

            if(cursor == '\n') {
                // found newline
                line_num_total[line_count] = ((first_num * 10) + last_num);
                assert(line_num_total[line_count] < (99 + 99));

                // reset
                line_count++;
                nums_on_line = 0;
            }

            if(isdigit(cursor)) {
                // found num
                if(nums_on_line == 0) {
                    first_num = my_atoi(cursor);
                    assert(first_num < 10 && first_num > -1);
                }

                last_num = my_atoi(cursor);
                assert(last_num < 10 && last_num > -1);

                nums_on_line++;
            }

        }

        int full_total = 0;

        for(int i = 0; i < line_count; i++) {
            full_total += line_num_total[i];
        }

        printf("total for %s: %d\n", argv[z], full_total);

    }

    return EXIT_SUCCESS;
}
