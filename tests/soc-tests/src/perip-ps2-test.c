#include <stdio.h>
#include <stdint.h>
#include <am.h>
#include <klib.h>
#include <klib-macros.h>

int main(int argc, char const *argv[])
{
    uint8_t *ps2_base = (uint8_t *)0x10011000;
    for (int i = 0; i < 0xfffff; i++)
    {
        volatile uint8_t data = io_read(AM_INPUT_KEYBRD).keycode;
        if (data != 0)
        {
            printf("Data: %x\n", data);
        }
    }
    return 0;
}
