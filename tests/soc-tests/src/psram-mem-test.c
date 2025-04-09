#include <stdio.h>
#include <stdint.h>
#include "trap.h"

#define PSRAM_BASE 0x80000000
#define PSRAM_SIZE 0x00400000

int main(int argc, char const *argv[])
{
    volatile uint32_t data;
    for (size_t i = 0; i < 0x1000; i++)
    {
        data = *((uint32_t *)(PSRAM_BASE + i * 4));
    }
    size_t offset = 0x2000;
    for (size_t i = 0; i < 0x1000 * 4; i++)
    {
        uint32_t *p = (uint32_t *)(PSRAM_BASE + offset + i * 4);
        data = 0xffff0000 | i;
        *p = data;
        check(*p == data);
        if (i % 0x1000 == 0)
        {
            printf("psram[%x]: \t%lx\n", i, *p);
        }
    }
    for (size_t i = 0; i < 4 * 1024 * 1024; i += 1024)
    {
        uint32_t *p = (uint32_t *)(PSRAM_BASE + i);
        data = 0xffff0000 | i;
        *p = data;
        check(*p == data);
        if (i % (0x1000 * 100) == 0)
        {
            printf("psram[%x]: \t%lx\n", i, *p);
        }
    }
    return 0;
}