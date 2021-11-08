#include "QuickSortM.h"


void SumArr(
    uint64_t* ar,
    uint64_t* a1, size_t s1,
    uint64_t* a2, size_t s2,
    uint64_t* a3, size_t s3);

void QuickSort(uint64_t* _array, size_t _array_size)
{
    if(_array_size <= 1)
    {
        return;
    }
    
    uint64_t* _low_array = (uint64_t*)malloc(sizeof(uint64_t*) * _array_size);
    uint64_t* _equal_array = (uint64_t*)malloc(sizeof(uint64_t*) * _array_size);
    uint64_t* _high_array = (uint64_t*)malloc(sizeof(uint64_t*) * _array_size);
    
    uint64_t _check_e = _array[_array_size / 2lu];
    size_t 
        _low_i = 0,
        _equal_i = 0,
        _high_i = 0;
    
    for(size_t _i = 0; _i < _array_size; _i++)
    {
        if(_array[_i] < _check_e)
        {
            _low_array[_low_i] = _array[_i];
            _low_i++;
        }
        else if(_array[_i] == _check_e)
        {
            _equal_array[_equal_i] = _check_e;
            _equal_i++;
        }
        else
        {
            _high_array[_high_i] = _array[_i];
            _high_i++;
        }
    }
    
    QuickSort(_low_array, _low_i);
    QuickSort(_high_array, _high_i);
    
    SumArr(
        _array,
        _low_array, _low_i,
        _equal_array, _equal_i,
        _high_array, _high_i);
    
    free(_low_array);
    free(_equal_array);
    free(_high_array);
    
}

void SumArr(uint64_t* ar, uint64_t* a1, size_t s1, uint64_t* a2, size_t s2, uint64_t* a3, size_t s3)
{        
    size_t pos = 0;
    
    for(size_t i = 0; i < s1; i++, pos++)
    {
        ar[pos] = a1[i];
    }
    for(size_t i = 0; i < s2; i++, pos++)
    {
        ar[pos] = a2[i];
    }
    for(size_t i = 0; i < s3; i++, pos++)
    {
        ar[pos] = a3[i];
    }
}


