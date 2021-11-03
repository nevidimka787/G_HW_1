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

#define LINES_IN_GROUP_COUNT    1000lu
#define GROUPS_COUNT            4u

#define ERROR   -1
#define ALWAYS  1

void CheckFilesErr(
    const FILE* _data_f,
    char* _data_f_name,
    const FILE* _log1_f,
    const FILE* _log2_f);

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
    char* log1_file_name = "log1_group";
    char* log2_file_name = "log2_group";
    char* log1_file_full_name = (char*)malloc(sizeof(char));
    char* log2_file_full_name = (char*)malloc(sizeof(char));
    log1_file_full_name[0] = '\0';
    log2_file_full_name[0] = '\0';
    
    
    unsigned group_number = 1u;
    
    sprintf(log1_file_full_name, "%s/%s_%u.log",
        log_files_way, log1_file_name, group_number);
    sprintf(log2_file_full_name, "%s/%s_%u.log",
        log_files_way, log2_file_name, group_number);
    
    FILE* data_file = fopen(argv[1], "r");    
    FILE* log1_file = fopen(log1_file_full_name, "w+");
    FILE* log2_file = fopen(log2_file_full_name, "w+");
    
    size_t line_number = 0lu;
    
    CheckFilesErr(data_file, argv[1], log1_file, log2_file);
    
    while(ALWAYS)
    {
        size_t array_length;
        if(fread(&array_length, sizeof(uint64_t), 1u, data_file) == 0)
        {//end of file detected
            break;
        }
        uint64_t* array = (uint64_t*)malloc(sizeof(uint64_t) * array_length);
        fread(array, sizeof(uint64_t), array_length, data_file);
        
        uint64_t* clone_arr = CloneArray(array, array_length);
        fprintf(log1_file, "%lf\n", GetSortTime(ShakeSort, array, array_length));
        fprintf(log2_file, "%lf\n", GetSortTime(SortFunc2, clone_arr, array_length));
        
        free(array);
        free(clone_arr);
        
        line_number++;
        
        if(!(line_number % LINES_IN_GROUP_COUNT))
        {
            printf("Group: %u was completed\n", group_number);
            group_number++;
            
            fclose(log1_file);
            fclose(log2_file);
            log1_file_full_name = (char*)realloc(log1_file_full_name, sizeof(char));
            log2_file_full_name = (char*)realloc(log2_file_full_name, sizeof(char));
            
            log1_file_full_name[0] = '\0';
            log1_file_full_name[0] = '\0';
            sprintf(log1_file_full_name, "%s/%s_%u.log",
                log_files_way, log1_file_name, group_number);
            sprintf(log2_file_full_name, "%s/%s_%u.log",
                log_files_way, log2_file_name, group_number);
            
            log1_file = fopen(log1_file_full_name, "w+");
            log2_file = fopen(log2_file_full_name, "w+");
        }
        else if(!(line_number % (LINES_IN_GROUP_COUNT / 10u)))
        {
            printf("%lu%%\n", (line_number % LINES_IN_GROUP_COUNT) / (LINES_IN_GROUP_COUNT / 10u) * 10u);
        }
        //printf("Line: %lu was completed.\n", line_number);
    }
    
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

double GetSortTime(void SortFunc(uint64_t*, size_t), uint64_t* _array, size_t _size)
{
    time_t start_time = clock();
    
    SortFunc(_array, _size);
    
    return (double)(clock() - start_time) / (double)CLOCKS_PER_SEC;
}














