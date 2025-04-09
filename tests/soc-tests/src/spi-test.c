#include <stdint.h>
#include <stdio.h>
#include "trap.h"

// #define SPI_TEST

#define SPI_BASE 0x10001000
#define SPI_CTRL SPI_BASE + 0x10
#define SPI_DIVIDER SPI_BASE + 0x14
#define SPI_SS SPI_BASE + 0x18

volatile uint32_t *spi_base = SPI_BASE;

volatile uint32_t *divider = SPI_DIVIDER;
volatile uint32_t *ss = SPI_SS;
volatile uint32_t *ctrl = SPI_CTRL;

uint32_t test_spi(uint32_t input)
{
    *(spi_base + 0) = input;

    *(ss) = 0x80;

    *(ctrl) = 0x910;

    while (1)
    {
        uint32_t c = *(ctrl);
        if ((c & 0x100) == 0)
        {
            *(ss) = 0x00;
            break;
        }
    }
    uint32_t r0 = *(spi_base + 0);
    return r0;
}

uint16_t bitrev(uint16_t x)
{
    return (
        (x & 0x01) << 7 |
        (x & 0x02) << 5 |
        (x & 0x04) << 3 |
        (x & 0x08) << 1 |
        (x & 0x10) >> 1 |
        (x & 0x20) >> 3 |
        (x & 0x40) >> 5 |
        (x & 0x80) >> 7);
}

int main()
{
#ifdef SPI_TEST
    uint32_t randoms[] = {
        0x01, 0x02, 0x03, 0x04,
        0x09, 0x0a, 0x0b, 0x0c,
        0x11, 0x12, 0x13, 0x14,
        0x19, 0x1a, 0x1b, 0x1c,
        0xff, 0x00, 0x0f, 0xf0};
    for (int i = 0; i < sizeof(randoms) / sizeof(randoms[0]); i++)
    {
        check(test_spi(randoms[i]) == bitrev(randoms[i]) << 8);
    }
    test_spi(0x2d);
#endif
    return 0;
}