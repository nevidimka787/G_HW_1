#include "quick_sort.h"

uint64_t* arr_sum (uint64_t* less_arr, size_t less_size, uint64_t* gr_arr, size_t gr_size) {
    uint64_t* res_arr = malloc((less_size + gr_size) * sizeof(uint64_t));
    for (size_t i = 0; i < less_size; ++i) {
        res_arr[i] = less_arr[i];
    }
    for (size_t i = 0; i < gr_size; ++i) {
        res_arr[i + less_size] = gr_arr[i];
    }
    return res_arr;
}

uint64_t* quicksort (uint64_t* array, size_t array_length) {
    if (array_length < 2) {
        return array;
    }
    else {

        srand(time(NULL));
        size_t pivot = (rand() % array_length);

        uint64_t* less_arr = (uint64_t*) malloc(array_length * sizeof(uint64_t));
        uint64_t* greater_arr = (uint64_t*) malloc(array_length * sizeof(uint64_t));
        uint64_t* mid_arr = (uint64_t*) malloc(array_length * sizeof(uint64_t));

        size_t i, less_index, gr_index, mid_index;

        for (i = 0, less_index = 0, gr_index = 0, mid_index = 0; i < array_length; ++i) {
            if (array[i] < array[pivot])
            {
                less_arr[less_index] = array[i];
                ++less_index;
            }
            else if (array[i] == array[pivot]) {
                mid_arr[mid_index] = array[pivot];
                ++mid_index;
            }
            else
            {
                greater_arr[gr_index] = array[i];
                ++gr_index;
            }
        }
        less_arr = realloc(less_arr, less_index * sizeof(uint64_t));
        greater_arr = realloc(greater_arr, gr_index * sizeof(uint64_t));
        mid_arr = realloc(mid_arr, mid_index * sizeof(uint64_t));
        uint64_t* sum_first = arr_sum(quicksort(less_arr, less_index), less_index, mid_arr, mid_index);
        uint64_t* res_arr = arr_sum(sum_first, (less_index + mid_index), quicksort(greater_arr, gr_index), gr_index);

        free(less_arr);
        free(sum_first);
        free(greater_arr);
        free(mid_arr);

        return res_arr;
    }
}

void q_sort (uint64_t* array, size_t array_length) {
    uint64_t* sorted_array = quicksort(array, array_length);
    free(array);
    array = sorted_array;
}
