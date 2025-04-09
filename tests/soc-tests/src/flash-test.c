#include <stdint.h>
#include <stdio.h>
#include "trap.h"

#define FLASH_BASE 0x30000000
// #define FLASH_TEST

int main()
{
#ifdef FLASH_TEST
    for (int i = 0; i < 0x1000; i++)
    {
        uint8_t *p = FLASH_BASE + i;
        check(p[0] == (i & 0xff));
    }
#endif
    return 0;
}