#include "IntroSort.h"

#define Swap(type, a, b) type Swap_buff = (a); (a) = (b); (b) = (Swap_buff);

void ConnectArr(
    uint64_t* ar,
    uint64_t* a1, size_t s1,
    uint64_t* a2, size_t s2,
    uint64_t* a3, size_t s3);

void DHeapify(uint64_t* _array, size_t _size, size_t _index);

void QuickSortM(uint64_t* _array, size_t _array_size, size_t req_num)
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
    
    if(req_num > 0)
    {
        QuickSortM(_low_array, _low_i, req_num - 1);
        QuickSortM(_high_array, _high_i, req_num - 1);
    }
    else
    {
        PiramidSort(_low_array, _low_i);
        PiramidSort(_high_array, _high_i);
    }
    
    ConnectArr(
        _array,
        _low_array, _low_i,
        _equal_array, _equal_i,
        _high_array, _high_i);
    
    free(_low_array);
    free(_equal_array);
    free(_high_array);
    
}

void ConnectArr(uint64_t* ar, uint64_t* a1, size_t s1, uint64_t* a2, size_t s2, uint64_t* a3, size_t s3)
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

void DHeapify(uint64_t* _array, size_t _size, size_t _index)
{
    size_t _max_index = _index; //index of the max element of double heap
    size_t _left_index, _right_index;
    
    while(1)
    {
        _left_index = 2 * _index + 1; //left index of max index
        _right_index = 2 * _index + 2; //left index of max index
        
        if(_size > _left_index && _array[_left_index] > _array[_max_index])
        {
            _max_index = _left_index;//indetificate max index
        }
        if(_size > _right_index && _array[_right_index] > _array[_max_index])
        {
            _max_index = _right_index;//indetificate max index
        }
        if(_index == _max_index)
        {
            break;//go uot of the cycle (and out of the function)
        }
        Swap(uint64_t, _array[_index], _array[_max_index]);
        _index = _max_index;//work with next max index
    }
}

void PiramidSort(uint64_t* _array, size_t _size)
{
    for(size_t _i = _size / 2; _i > 0; _i--)
    {
        DHeapify(_array, _size, _i - 1);//start from second line (from down)
    }
    
    for(size_t _i = _size; _i > 0; _i--)
    {
        Swap(uint64_t, _array[0], _array[_i - 1]);
        DHeapify(_array, _i - 1, 0);
    }
}

void IntroSort(uint64_t* _array, size_t _size)
{
    QuickSortM(_array, _size, (size_t)log2((double)_size));
}
































