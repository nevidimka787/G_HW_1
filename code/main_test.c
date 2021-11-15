#include <stdbool.h>
#include "IntroSort.h"

#define SIZE    10

bool CheckArr(uint64_t* _array, size_t _size);
void PrintArr(uint64_t* _array, size_t _size); 

int main(void)
{
    uint64_t* arr = malloc(sizeof(uint64_t) * SIZE);
    
    arr[0] = 33;
    arr[1] = 23;
    arr[2] = 26;
    arr[3] = 64;
    arr[4] = 45;
    arr[5] = 22;
    arr[6] = 98;
    arr[7] = 12;
    arr[8] = 12;
    arr[9] = 54;
    
    PrintArr(arr, SIZE);
    printf("\n\nSorting...\n");

    IntroSort(arr, SIZE);

    PrintArr(arr, SIZE);
    printf("\n");
}

bool CheckArr(uint64_t* _array, size_t _size)
{
    for(size_t _i = 1; _i < _size; _i++)
    {
        if(_array[_i - 1] > _array[_i])
        {
            return false;
        }
    }
    
    return true;
}

void PrintArr(uint64_t* _array, size_t _size)
{
    for(size_t _i = 0; _i < _size; _i++)
    {
        printf("%lu ", _array[_i]);
    }
}
















