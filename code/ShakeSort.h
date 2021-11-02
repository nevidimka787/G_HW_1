#pragma once

#ifndef G_HW_1_LIBRARY_H
#define G_HW_1_LIBRARY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define SWAP(x, y) uint64_t z = x; x = y; y = z;

void ShakeSort(uint64_t *input, size_t size);

#endif //G_HW_1_LIBRARY_H
