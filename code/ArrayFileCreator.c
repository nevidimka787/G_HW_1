/*
The prgram generate bin file.
The file has LINES_IN_GROUP_COUNT * GROUPS_COUNT lines.
The GROUPS_COUNT is log[EXP_STEP](ELEMENTS_FINISH_COUNT / ELEMENTS_START_COUNT) + 1
The first value in the line store a data about count of elements in current line.
*/

#define SHAKE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define NEW_LINE    0xFFFFFFFF

#ifdef INTRO
#define BLOCKS_COUNT    1000000
#define BLOCK_DELTA     1000
#endif //INTRO


#ifdef SHAKE
#define BLOCKS_COUNT    10000
#define BLOCK_DELTA     10
#endif //SHAKE


#define LINES_IN_BLOCK  4
#define DELTA           0.01f

#define ARRAY_FILE_NAME argv[1]
#define ARRAY_TYPE      argv[2]

#define ERROR -1

uint32_t Rand32U();
uint64_t Rand64U();
float RandF1();
bool StrsIsEqual(const char* _str1, const char* _str2);

int main(unsigned argc, char** argv)
{
    if(argc < 3)
    {
        printf("ERROR::Low argumants.\nArrCreator.elf <generated_file_name> [{GOOD, NORMAL, BAD}]\n");
        exit(ERROR);
    }
    
    FILE *arrays_file;
    arrays_file = fopen(ARRAY_FILE_NAME, "wb+");
    
    if(StrsIsEqual(ARRAY_TYPE, "GOOD"))
    {
        for(size_t block = BLOCK_DELTA; block < BLOCKS_COUNT; block += BLOCK_DELTA)
        {
            for(size_t line = 0; line < LINES_IN_BLOCK; line++)
            {
                uint64_t* array = malloc(sizeof(uint64_t) * block + 1);
                array[0] = block;
                for(size_t element = 1; element <= array[0]; element++)
                {
                    array[element] = element + (uint64_t)((float)element * RandF1() * DELTA);
                }
                fwrite(array, sizeof(uint64_t) , array[0] + 1, arrays_file);
                free(array);
            }
            printf("Block %lu / %lu create.\r", block / BLOCK_DELTA + 1, (uint64_t)(BLOCKS_COUNT / BLOCK_DELTA));
        }
    }
    
    if(StrsIsEqual(ARRAY_TYPE, "NORMAL"))
    {
        for(size_t block = BLOCK_DELTA; block < BLOCKS_COUNT; block += BLOCK_DELTA)
        {
            for(size_t line = 0; line < LINES_IN_BLOCK; line++)
            {
                uint64_t* array = malloc(sizeof(uint64_t) * block + 1);
                array[0] = block;
                for(size_t element = 1; element <= array[0]; element++)
                {
                    array[element] = Rand64U();
                }
                fwrite(array, sizeof(uint64_t) , array[0] + 1, arrays_file);
                free(array);
            }
            printf("Block %lu / %lu create.\r", block / BLOCK_DELTA + 1, (uint64_t)(BLOCKS_COUNT / BLOCK_DELTA));
        }
    }
    
    if(StrsIsEqual(ARRAY_TYPE, "BAD"))
    {
        for(size_t block = BLOCK_DELTA; block < BLOCKS_COUNT; block += BLOCK_DELTA)
        {
            for(size_t line = 0; line < LINES_IN_BLOCK; line++)
            {
                uint64_t* array = malloc(sizeof(uint64_t) * block + 1);
                array[0] = block;
                for(size_t element = 0; element < array[0]; element++)
                {
                    array[array[0] - element] = element + (uint64_t)((float)element * RandF1() * DELTA);
                }
                fwrite(array, sizeof(uint64_t) , array[0] + 1, arrays_file);
                free(array);
            }
            printf("Block %lu / %lu create.\r", block / BLOCK_DELTA + 1, (uint64_t)(BLOCKS_COUNT / BLOCK_DELTA));
        }
    }
    
    
    fclose(arrays_file);
    printf("File generation was completed.\nProgram was finished\n");
}

float RandF1()
{
    return (float)rand() / (float)RAND_MAX;
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

bool StrsIsEqual(const char* _str1, const char* _str2)
{
    if(_str1 == NULL || _str2 == NULL)
    {
        return false;
    }
    
    size_t _c = 0;
    
    while(_str1[_c] != '\0' && _str2[_c] != '\0')
    {
        if(_str1[_c] != _str2[_c])
        {
            return false;
        }
        _c++;
    }
    return _str1[_c] == _str2[_c];
}














