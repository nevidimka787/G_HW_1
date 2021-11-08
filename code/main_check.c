#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "ShakeSort.h"
#include "QuickSortM.h"

//#include <sortlib1.h>
//#include <sortlib2.h>

void SortFunc2(uint64_t* _array, size_t _size){}

#define LOG1_FILE "logs/log1.txt"
#define LOG2_FILE "logs/log2.txt"

#define LINES_IN_GROUP_COUNT    1000lu
#define START_GROUP             1u
#define GROUPS_COUNT            4u

#define ERROR   -1
#define ALWAYS  1

void CheckFilesErr(
    const FILE* _data_f,
    char* _data_f_name,
    const FILE* _log1_f,
    const FILE* _log2_f);

void CheckArray(uint64_t* _input_array, uint64_t* _sort_array, size_t _array_size, FILE* _log_f);
uint64_t* CloneArray(const uint64_t* _array, size_t _array_size);

double GetSortTime(void SortFunc(uint64_t*, size_t), uint64_t* _array, size_t _size);

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("ERROR::MAIN::No input file.\n");
        exit(ERROR);
    }
    
    char* log_files_way = "logs";
    char* error_log1_file_name = "error_log1";
    char* error_log2_file_name = "error_log2";
    
    char* error_log1_file_full_name = (char*)malloc(sizeof(char));
    char* error_log2_file_full_name = (char*)malloc(sizeof(char));
    
    error_log1_file_full_name[0] = '\0';
    error_log2_file_full_name[0] = '\0';
    
    
    unsigned group_number = START_GROUP;
    
    sprintf(error_log1_file_full_name, "%s/%s.log",
        log_files_way, error_log1_file_name);
    sprintf(error_log2_file_full_name, "%s/%s.log",
        log_files_way, error_log2_file_name);
    
    FILE* data_file = fopen(argv[1], "r");
    FILE* error_log1_file = fopen(error_log1_file_full_name, "w+");
    FILE* error_log2_file = fopen(error_log2_file_full_name, "w+");
    
    size_t line_number = 0lu;
    
    CheckFilesErr(data_file, argv[1], error_log1_file, error_log2_file);
    
    while(ALWAYS)
    {
        size_t array_length;
        if(fread(&array_length, sizeof(uint64_t), 1u, data_file) == 0)
        {//end of file detected
            break;
        }
        uint64_t* array = (uint64_t*)malloc(sizeof(uint64_t) * array_length);
        fread(array, sizeof(uint64_t), array_length, data_file);
        
        uint64_t* clone1_arr;// = CloneArray(array, array_length);
        uint64_t* clone2_arr = CloneArray(array, array_length);
        
        //ShakeSort(clone1_arr, array_length);
        QuickSort(clone2_arr, array_length);
        
        //CheckArray(array, clone1_arr, array_length, error_log1_file);
        CheckArray(array, clone1_arr, array_length, error_log2_file);
        
        free(array);
        free(clone1_arr);
        free(clone2_arr);
        
        line_number++;
        
        if(!(line_number % LINES_IN_GROUP_COUNT))
        {
            printf("Group: %u was completed\n", group_number);
            group_number++;
        }
        else if(!(line_number % (LINES_IN_GROUP_COUNT / 10u)))
        {
            printf("%lu%%\n", (line_number % LINES_IN_GROUP_COUNT) / (LINES_IN_GROUP_COUNT / 10u) * 10u);
        }
        //printf("Line: %lu was completed.\n", line_number);
    }
    
    fclose(error_log1_file);
    fclose(error_log2_file);
    fclose(data_file);
    
    printf(
        "\n\nProgram finished succsessfully.\n%lu lines was sorted.\nResults was wrote in %s folder.\n",
        line_number, log_files_way);
}

void CheckFilesErr(const FILE* _data_f, char* _data_f_name, const FILE* _log1_f, const FILE* _log2_f)
{    
    if(_data_f == NULL)
    {
        printf("ERROR::MAIN::Can not open data file.\nFile name: %s\n", _data_f_name);
    }
    if(_log1_f == NULL)
    {
        printf("ERROR::MAIN::Can not open log file.\nFile name: %s\n", LOG1_FILE);
    }
    if(_log2_f == NULL)
    {
        printf("ERROR::MAIN::Can not open log file.\nFile name: %s\n", LOG2_FILE);
    }
    if(_data_f == NULL || _log1_f == NULL || _log2_f == NULL)
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

void CheckArray(uint64_t* _input_array, uint64_t* _sort_array, size_t _array_size, FILE* _log_f)
{
    if(_array_size < 2)
    {
        return;
    }
    for(size_t _element = 1lu; _element < _array_size; _element++)
    {
        if(_sort_array[_element - 1lu] > _sort_array[_element])
        {
            fprintf(
                _log_f, "Incorrect sorting in elements %lu and %lu:\nInput array:\n",
                _element - 1lu, _element);
            for(size_t i = 0; i < _array_size; i++)
            {
                fprintf(_log_f, "%lu ", _input_array[i]);
            }
            fprintf(_log_f, "\nSorted array:\n");
            for(size_t i = 0; i < _array_size; i++)
            {
                fprintf(_log_f, "%lu ", _sort_array[i]);
            }
            fprintf(_log_f, "\n\n");
            return;
        }
    }
}













