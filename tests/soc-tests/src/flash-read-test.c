#include <stdint.h>
#include <stdio.h>
#include "trap.h"

#define FLASH_BASE 0x30000000
// #define FLASH_TEST
#define SRAM_TARGET 0x0f001000

#define SPI_BASE 0x10001000
#define SPI_CTRL SPI_BASE + 0x10
#define SPI_DIVIDER SPI_BASE + 0x14
#define SPI_SS SPI_BASE + 0x18

volatile uint32_t *spi_base = SPI_BASE;

volatile uint32_t *divider = SPI_DIVIDER;
volatile uint32_t *ss = SPI_SS;
volatile uint32_t *ctrl = SPI_CTRL;

uint32_t flash_read(uint32_t addr)
{
    uint32_t flash_cmd = (0x03 << 24) | (addr & 0xffffff);
    *(uint32_t *)(SPI_BASE + 4) = flash_cmd; // TODO: know why it is 4
    *(ss) = 0x01;
    *(ctrl) = 0x540;
    while (1)
    {
        uint32_t c = *(ctrl);
        if ((c & 0x100) == 0)
        {
            *(ss) = 0x00;
            break;
        }
    }
    uint32_t r0 = *(uint32_t *)(SPI_BASE + 0);
    r0 = ((r0 & 0xff000000) >> 24) |
         ((r0 & 0x00ff0000) >> 8) |
         ((r0 & 0x0000ff00) << 8) |
         ((r0 & 0x000000ff) << 24);
    return r0;
}

int main()
{
#ifdef FLASH_TEST
    for (int i = 0; i < 0x1f; i += 4)
    {
        uint32_t p = flash_read(FLASH_BASE + i);
        // printf("flash_read: %x\n", p);
        *(uint32_t *)(SRAM_TARGET + i) = p;
    }
    asm volatile(
        "li t0, 0x0f001000\n\t"
        "jalr t0\n\t");
#endif
    return 0;
}