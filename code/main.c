#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "ShakeSort.h"

//#include <sortlib1.h>
//#include <sortlib2.h>

void SortFunc2(uint64_t* _array, size_t _size){}

#define LOG1_FILE "logs/log1.txt"
#define LOG2_FILE "logs/log2.txt"

#define ERROR -1

bool CharIsNumber(char _char);
double GetSortTime(void SortFunc(uint64_t*, size_t), uint64_t* _array, size_t _size);

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("ERROR::MAIN::No input file.\n");
        exit(ERROR);
    }
    
    FILE* data_file = fopen(argv[1], "r");
    FILE* log1_file = fopen(LOG1_FILE, "w+");
    FILE* log2_file = fopen(LOG2_FILE, "w+");
    
    if(data_file == NULL)
    {
        printf("ERROR::MAIN::Can not open data file.\nFile name: %s\n", argv[1]);
    }
    if(log1_file == NULL)
    {
        printf("ERROR::MAIN::Can not open log file.\nFile name: %s\n", LOG1_FILE);
    }
    if(log2_file == NULL)
    {
        printf("ERROR::MAIN::Can not open log file.\nFile name: %s\n", LOG2_FILE);
    }
    if(data_file == NULL || log1_file == NULL || log2_file == NULL)
    {
        exit(ERROR);
    }
    
    uint64_t* array;
    size_t array_length = 0;
    
    size_t line_number = 0;
    size_t line_symbol = 0;
    
    char* line;
    
    array = (uint64_t*)malloc(sizeof(uint64_t));
    line = (char*)malloc(sizeof(char));
    
    printf("\n\n");
    
    while((line[line_symbol] = getc(data_file)) != EOF)
    {
        if(
            line_symbol > 0 &&
            line[line_symbol] == ' ' &&
            CharIsNumber(line[line_symbol - 1]))
        {
            array_length++;
            array = (uint64_t*)realloc(array, sizeof(uint64_t) * array_length);
            line = (char*)realloc(line, sizeof(char) * (line_symbol + 2));
            line[line_symbol + 1] = '\0';
            sscanf(line, "%lu", &array[array_length - 1]);
            line_symbol = -1;//it is UINT_MAX
            
        }
        else if(line[line_symbol] == '\n')
        {
            if(
                line_symbol > 0 &&
                CharIsNumber(line[line_symbol - 1]))
            {
                array_length++;
                array = (uint64_t*)realloc(array, sizeof(uint64_t) * array_length);
                line = (char*)realloc(line, sizeof(char) * (line_symbol + 2));
                line[line_symbol + 1] = '\0';
                sscanf(line, "%lu", &array[array_length - 1]);
                line_symbol = -1;//it is UINT_MAX
            }
            
            if(array_length == 0)
            {
                printf("WARNING::MAIN::Line number %lu is void.\n", line_number);
                line_number++;
                line_symbol = -1;//it is UINT_MAX
            }
            else
            {      
                fprintf(log1_file, "%lf\n", GetSortTime(ShakeSort, array, array_length));
                fprintf(log2_file, "%lf\n", GetSortTime(SortFunc2, array, array_length));
                array = (uint64_t*)realloc(array, sizeof(uint64_t));
                array_length = 0;
                line_number++;
                printf("Line %lu was sorted.\n", line_number);
            }
            
        }
        
        line_symbol++;
        line = (char*)realloc(line, sizeof(char) * (line_symbol + 1));
    }
    
    printf(
        "\n\nProgram finished succsessfully.\n%lu lines was sorted.\nResults was wrote in\n%s\n%s\n",
        line_number, LOG1_FILE, LOG2_FILE);
}


bool CharIsNumber(char _char)
{
    return '0' <= _char && _char <= '9';
}

double GetSortTime(void SortFunc(uint64_t*, size_t), uint64_t* _array, size_t _size)
{
    time_t start_time = clock();
    
    SortFunc(_array, _size);
    
    return (double)(clock() - start_time) / (double)CLOCKS_PER_SEC;
}














