#include "library.h"


uint64_t shake(uint64_t *input, size_t size) {
    size_t left = 0;
    size_t right = size - 1;
    bool flag = true;
    while ((left < right) && flag == true) {
        flag = false;
        for (size_t i = left; i < right; ++i) {
            if (input[i] > input[i + 1]) {
                SWAP(input[i], input[i + 1]);
                flag = true;
            }
        }
        --right;
        for (size_t i = right; i > left; --i) {
            if (input[i - 1] > input[i]) {
                SWAP(input[i - 1], input[i]);
                flag = true;
            }
        }
        ++left;
    }
    return input;
}