#include "stdio.h"
#include "stdlib.h"

int main()
{
    system("./Timing.elf arrays/intro_arr_good.bin logs/intro_arr_good_q15.log");
    system("./Timing.elf arrays/intro_arr_normal.bin logs/intro_arr_normal_q15.log");
    system("./Timing.elf arrays/intro_arr_bad.bin logs/intro_arr_bad_q15.log");
}
