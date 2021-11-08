#pragma once

#ifndef G_HW_1_QUICK_SORT_H
#define G_HW_1_QUICK_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <stdint.h>

uint64_t* arr_sum (uint64_t* less_arr, size_t less_size, uint64_t* gr_arr, size_t gr_size);
uint64_t* quicksort (uint64_t* array, size_t array_length);
void q_sort (uint64_t* array, size_t array_length);

#endif // G_HW_1_QUICK_SORT_H
