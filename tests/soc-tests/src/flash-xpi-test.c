#include <stdint.h>
#include <stdio.h>
#include "trap.h"

#define FLASH_BASE 0x30000000

int main()
{
    // volatile uint32_t p;
    // p = *(uint32_t *)(FLASH_BASE + 0);
    // printf("flash_read: %x\n", p);
    // asm volatile(
    //     "li t0, 0x30000000\n\t"
    //     "jalr t0\n\t");
    return 0;
}