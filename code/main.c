#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

//#include <sortlib1.h>
//#include <sortlib2.h>

void SortFunc1(unsigned* _array){}
void SortFunc2(unsigned* _array){}

#define LOG1_FILE "log1.txt"
#define LOG2_FILE "log2.txt"

#define ERROR -1

bool CharIsNumber(char _char);
double GetSortTime(void SortFunc(unsigned*), unsigned* array);

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("ERROR::MAIN::No input file.\n");
        exit(ERROR);
    }
    
    FILE* data_file = fopen(argv[1], "r");
    FILE* log1_file = fopen(LOG1_FILE, "w");
    FILE* log2_file = fopen(LOG2_FILE, "w");
    
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
    
    unsigned* array;
    unsigned array_length = 0;
    
    unsigned line_number = 0;
    unsigned line_symbol = 0;
    
    char* line;
    
    array = (unsigned*)malloc(sizeof(unsigned));
    line = (char*)malloc(sizeof(char));
    
    while((line[line_symbol] = getc(data_file)) != EOF)
    {
        if(
            line_symbol > 0 &&
            line[line_symbol] == ' ' &&
            CharIsNumber(line[line_symbol - 1]))
        {
            array_length++;
        }
        else if(line[line_symbol] == '\n')
        {
            if(
                line_symbol > 0 &&
                CharIsNumber(line[line_symbol - 1]))
            {
                array_length++;
            }
            
            if(array_length == 0)
            {
                printf("WARNING::MAIN::Line number %u is void.", line_number);
            }
            else
            {
                array = (unsigned*)realloc(array, sizeof(unsigned) * array_length);
                for(unsigned element = 0; element < array_length; element++)
                {
                    fscanf(data_file, "%u", &array[element]);
                }
                
                fprintf(log1_file, "%lf\n", GetSortTime(SortFunc1, array));
                fprintf(log2_file, "%lf\n", GetSortTime(SortFunc2, array));
                
                array_length = 0;
                line_number++;
                line_symbol = -1;//it is UINT_MAX
            }
            
        }
        
        line_symbol++;
        line = (char*)realloc(line, sizeof(char) * (line_symbol + 1));
    }
}


bool CharIsNumber(char _char)
{
    return '0' <= _char && _char <= '9';
}

double GetSortTime(void SortFunc(unsigned*), unsigned* array)
{
    unsigned long start_time = clock();
    
    SortFunc(array);
    
    return (double)(clock() - start_time) / (double)CLOCKS_PER_SEC;
}














