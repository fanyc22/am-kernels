#include <stdio.h>
#include <stdint.h>
#include <am.h>
#include <klib.h>
#include <klib-macros.h>

int main(int argc, char const *argv[])
{
    uint32_t mvendorid, marchid;
    asm volatile(
        "csrr %0, mvendorid\n\t"
        "csrr %1, marchid\n\t"
        : "=r"(mvendorid), "=r"(marchid) :);
    printf("mvendorid: 0x%lx, marchid: %ld\n",
           mvendorid, marchid);
    for (int i = 0; i < 0xffff; i++)
    {
        volatile uint8_t data = io_read(AM_UART_RX).data;
        if (data != 0xff)
        {
            printf("data: %d, %c\n", data, data);
        }
    }
    return 0;
}
