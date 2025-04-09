#include <stdio.h>
#include <stdint.h>

#define GPIO_BASE 0x10002000
#define GPIO_SWITCH GPIO_BASE + 0x4
#define GPIO_SEG GPIO_BASE + 0x8

int main(int argc, char const *argv[])
{
    uint16_t *gpio = (uint16_t *)GPIO_BASE;
    uint16_t *sw = (uint16_t *)GPIO_SWITCH;
    uint8_t *seg = (uint8_t *)GPIO_SEG;
    uint16_t light = 1;
    volatile uint16_t data;
    uint32_t mvendorid, marchid;
    asm volatile(
        "csrr %0, mvendorid\n\t"
        "csrr %1, marchid\n\t"
        : "=r"(mvendorid), "=r"(marchid) :);
    for (int i = 0; i < 4; i++)
    {
        seg[i] = (marchid >> (8 * i)) & 0xff;
    }
    for (;;)
    {
        data = *sw;
        if (data == 0x8888)
        {
            break;
        }
    }
    for (int i = 0; i < 0x1fff; i++)
    {
        *gpio = light;
        if (i % 100 == 0)
        {
            light = light << 1;
        }
        if (light == 0)
        {
            light = 1;
        }
        asm volatile("nop");
    }
    return 0;
}
