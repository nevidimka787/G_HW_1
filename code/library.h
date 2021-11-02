#ifndef G_HW_1_LIBRARY_H
#define G_HW_1_LIBRARY_H

#include <stdio.h>
#include <stdbool.h>

#define SWAP(x, y) uint64_t z = x; x = y; y = z;

uint64_t shake(uint64_t *input, size_t size);

#endif //G_HW_1_LIBRARY_H
