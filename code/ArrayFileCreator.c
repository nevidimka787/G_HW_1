/*
The prgram generate bin file.
The file has LINES_IN_GROUP_COUNT * GROUPS_COUNT lines.
The GROUPS_COUNT is log[EXP_STEP](ELEMENTS_FINISH_COUNT / ELEMENTS_START_COUNT) + 1
The first value in the line store a data about count of elements in current line.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define NEW_LINE    0xFFFFFFFF

#define LINES_IN_GROUP_COUNT    1000lu
#define EXP_STEP                10lu
#define ELEMENTS_START_COUNT    100lu
#define ELEMENTS_FINISH_COUNT   100000lu
#define GROUPS_COUNT            4u

#define ARRAY_FILE_NAME argv[1]

#define ERROR -1

uint32_t Rand32U();
uint64_t Rand64U();

int main(unsigned argc, char** argv)
{
    if(argc < 2)
    {
        printf("ERROR::Low argumants.\nArrCreator.elf <generated_file_name>\n");
        exit(ERROR);
    }
    FILE *arrays_file;
    arrays_file = fopen(ARRAY_FILE_NAME, "wb");
    long k = 1000;
    size_t elements_in_line = Rand32U();
    
    for(size_t group = ELEMENTS_START_COUNT; group <= ELEMENTS_FINISH_COUNT; group *= EXP_STEP)
    {
        //printf("Group: %lu\n", group);
        for(size_t line = 0; line < LINES_IN_GROUP_COUNT; line++)
        {
            uint64_t* array = (uint64_t*)malloc(sizeof(uint64_t) * (group + 1u));
            array[0u] = (uint64_t)group;
            for(size_t elemnt = 1u; elemnt <= group; elemnt++)
            {
                array[elemnt] = Rand64U();
            }
            if(fwrite(array, sizeof(uint64_t), group + 1u, arrays_file) != group + 1u)
            {
                printf("Write data error: Some data not wrote.\nFile: %s\nGroup: %lu\nLine: %lu",
                    ARRAY_FILE_NAME, group, line);
            }
            free(array);
        }
        printf("Group: %lu was completed.\n", group);
    }
    fclose(arrays_file);
    printf("All groups were completed.\nProgram was finished");
}

uint32_t Rand32U()
{
    return 
        ((uint64_t)rand() << 16lu) +
        (uint64_t)rand();
}


uint64_t Rand64U()
{
    return
        ((uint64_t)rand() << 48lu) +
        ((uint64_t)rand() << 32lu) +
        ((uint64_t)rand() << 16lu) +
        (uint64_t)rand();
}














