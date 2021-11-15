#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void QuickSort(uint64_t* _array, size_t _array_size);

void PiramidSort(uint64_t* _array, size_t _array_size);

#define INTRO_SORT_MAX_REQURSIONS_COUNT     15
void IntroSort(uint64_t* _array, size_t _array_size);

