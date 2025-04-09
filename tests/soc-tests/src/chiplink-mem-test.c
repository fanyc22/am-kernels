#include <stdint.h>

volatile uint8_t data;

int main()
{
    return 0;
    uint8_t *p = 0xc0000000;       // CHIPLINK_MEM_BASE
    uint8_t *p_sdram = 0xa0000000; // SDM_BASE
    for (int i = 0; i < 0x1000; i++)
    {
        volatile int8_t data = *(p + i);
        data += 1;
        *(p + i) = data;
    }
    for (int i = 0; i < 0x1000; i++)
    {
        volatile int8_t data = *(p_sdram + i);
        data += 1;
        *(p + i) = data;
    }
    return 0;
}