#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "ShakeSort.h"
#include "IntroSort.h"


#define ERROR   -1
#define ALWAYS  1

#define DATA_FILE_NAME  argv[1]
#define LOG_FILE_NAME   argv[2]


void CheckFilesErr(
    const FILE* _data_f, const char* _data_f_name,
    const FILE* _log_f, const char* _log_f_name);

uint64_t* CloneArray(const uint64_t* _array, size_t _array_size);

double GetSortTime(void SortFunc(uint64_t*, size_t), uint64_t* _array, size_t _size);

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("ERROR::MAIN::Few arguments.\n./Timing.elf <data_file_name> <log_file_name>\n");
        exit(ERROR);
    }
    
    printf("Timing program was began.\n");
    
    FILE* data_file = fopen(DATA_FILE_NAME, "r");    
    FILE* log_file = fopen(LOG_FILE_NAME, "w+");
    
    size_t line_number = 0lu;
    
    CheckFilesErr(data_file, DATA_FILE_NAME, log_file, LOG_FILE_NAME);
    
    size_t array_length;
    
    while(ALWAYS)
    {
        if(fread(&array_length, sizeof(uint64_t), 1u, data_file) == 0)
        {//end of file detected
            break;
        }
        uint64_t* array = (uint64_t*)malloc(sizeof(uint64_t) * array_length);
        fread(array, sizeof(uint64_t), array_length, data_file);
        
        fprintf(log_file, "%lu\t%lf\n", array_length, GetSortTime(IntroSort, array, array_length));
        
        free(array);
        
        printf("array: %lu\r", line_number);
        line_number++;
        
    }
    
    fclose(log_file);
    fclose(data_file);
    
    printf(
        "\n\nProgram finished succsessfully.\n%lu lines was sorted.\nResults was wrote in %s.\n",
        line_number, LOG_FILE_NAME);
}

void CheckFilesErr(const FILE* _data_f, const char* _data_f_name, const FILE* _log_f, const char* _log_f_name)
{    
    if(_data_f == NULL)
    {
        printf("ERROR::MAIN::Can not open data file.\nFile name: %s\n", _data_f_name);
    }
    if(_log_f == NULL)
    {
        printf("ERROR::MAIN::Can not open log file.\nFile name: %s\n", _log_f_name);
    }
    if(_data_f == NULL || _log_f == NULL)
    {
        exit(ERROR);
    }
}

uint64_t* CloneArray(const uint64_t* _array, size_t _array_size)
{
    uint64_t* _new_arr = (uint64_t*)malloc(sizeof(uint64_t) * _array_size);
    for(size_t i = 0; i < _array_size; i++)
    {
        _new_arr[i] = _array[i];
    }
    return _new_arr;
}

double GetSortTime(void SortFunc(uint64_t*, size_t), uint64_t* _array, size_t _size)
{
    time_t start_time = clock();
    
    SortFunc(_array, _size);
    
    return (double)(clock() - start_time) / (double)CLOCKS_PER_SEC;
}













