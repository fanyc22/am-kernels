#include <stdio.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    volatile uint32_t data;
    if (1)
    {
        volatile uint32_t *sdram = (uint32_t *)0xa1fffffc;
        putch('\n');
        *sdram = 0x12345678;
        data = *sdram;

        volatile uint8_t *sdram_u8 = (uint8_t *)0xa1fffff1;
        *sdram_u8 = 0x12;
        data = *sdram_u8;

        sdram_u8 = (uint8_t *)(0xa0000000);
        data = *sdram_u8;
        sdram_u8 = (uint8_t *)(0xa0001800);
        *sdram_u8 = 0x12;
        sdram_u8 = (uint8_t *)(0xa0000000);
        data = *sdram_u8;

        sdram_u8 = (uint8_t *)(0xa1ffffff + 0x1);
        *sdram_u8 = 0x42;
        data = *sdram_u8;

        for (size_t i = 0; i < 10; i++)
        {
            *(sdram_u8 + i) = 0x12;
        }
        for (size_t i = 0; i < 10; i++)
        {
            data = *(sdram_u8 + i);
            if (data != 0x12)
            {
                putch('F');
                asm volatile(
                    "li a0, 0x1\n"
                    "ebreak");
                break;
            }
        }

        // // turn sdram_u8 to function pointer
        // void (*func)(void) = (void (*)(void))sdram_u8;
        // func();
    }
    return 0;
}