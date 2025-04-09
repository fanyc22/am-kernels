#include <stdio.h>
#include <stdint.h>
#include "trap.h"

#define SDRAM_BASE 0xa0000000

int main(int argc, char const *argv[])
{
    volatile uint64_t data;
    volatile uint8_t *sdram_u8 = (uint8_t *)(SDRAM_BASE);
    volatile uint8_t *mem = (uint8_t *)(SDRAM_BASE);
    if (&main >= 0xa0000000)
    {
        printf("main in sdram, goto read_test\n");
        goto read_test;
    }
write_test:
    for (int i = 0; i < 0x1000 / sizeof(uint8_t); i++)
    {
        sdram_u8[i] = 0x12345678;
        data = sdram_u8[i];
    }
    volatile uint16_t *sdram_u16 = (uint16_t *)(SDRAM_BASE);
    for (int i = 0; i < 0x1000 / sizeof(uint16_t); i++)
    {
        sdram_u16[i] = 0x12345678;
        data = sdram_u16[i];
    }
    volatile uint32_t *sdram = (uint32_t *)(SDRAM_BASE);
    for (int i = 0; i < 0x1000 / sizeof(uint32_t); i++)
    {
        sdram[i] = 0x12345678;
        data = sdram[i];
    }
    volatile uint64_t *sdram_u64 = (uint64_t *)(SDRAM_BASE);
    for (int i = 0; i < 0x1000 / sizeof(uint64_t); i++)
    {
        sdram_u64[i] = 0x12345678;
        data = sdram_u64[i];
    }
    printf("4KB SDRAM test passed\n");
    for (int i = 0; i < 0x1000; i++)
    {
        uint8_t volatile u8 = ((uint8_t)(mem + i)) & 0xff;
        mem[i] = u8;
        volatile uint8_t b;
        b = (mem[i] == u8);
        if (!b)
        {
            printf("mem[%x]: %x, u8: %x\n", i, mem[i], u8);
        }

        uint16_t volatile u16 = (uint16_t)(mem + i) & 0xffff;
        ((uint16_t *)(mem + i))[0] = u16;
        b = (((uint16_t *)(mem + i))[0] == u16);
        if (!b)
        {
            printf("((uint16_t *)(mem + %x))[0]: %x, u16: %x\n", i, ((uint16_t *)(mem + i))[0], u16);
        }

        uint32_t volatile u32 = (uint32_t)(mem + i) & 0xffffffff;
        ((uint32_t *)(mem + i))[0] = u32;
        b = (((uint32_t *)(mem + i))[0] == u32);
        if (!b)
        {
            printf("((uint32_t *)(mem + %x))[0]: %x, u32: %x\n", i, ((uint32_t *)(mem + i))[0], u32);
        }

        uint64_t volatile u64 = (uint64_t)(mem + i) & 0xffffffffffffffff;
        ((uint64_t *)(mem + i))[0] = u64;
        b = (((uint64_t *)(mem + i))[0] == u64);
        if (!b)
        {
            printf("((uint64_t *)(mem + %x))[0]: %lx, u64: %lx\n", i, ((uint64_t *)(mem + i))[0], u64);
        }
    }
    printf("SDRAM mem test passed\n");

    for (int i = 0; i < 0x4000000 / sizeof(uint8_t); i += 0x10000)
    {
        uint8_t volatile u8 = 0x12345678;
        sdram_u8[i] = u8;
        data = sdram_u8[i];
        if (sdram_u8[i] != u8)
        {
            printf("sdram_u8[%x]: %x, u8: %x\n", i, sdram_u8[i], u8);
            break;
        }
    }
    printf("SDRAM fast all passed!\n");

    for (int i = 0; i < 0x4000000 / sizeof(uint8_t); i++)
    {
        uint8_t volatile u8 = 0x12345678;
        sdram_u8[i] = u8;
        data = sdram_u8[i];
        if (sdram_u8[i] != u8)
        {
            printf("sdram_u8[%x]: %x, u8: %x\n", i, sdram_u8[i], u8);
            break;
        }
        if (i % 0x100000 == 0)
        {
            printf("SDRAM test: %d bytes written\n", i);
        }
    }
read_test:
    for (int i = 0; i < 0x400000 / sizeof(uint8_t); i += 0x1000)
    {
        data = sdram_u8[i];
    }
    printf("SDRAM read fast all passed!\n");
    for (int i = 0; i < 0x400000 / sizeof(uint8_t); i++)
    {
        data = sdram_u8[i];
    }
    printf("SDRAM read all passed!\n");

    return 0;
}