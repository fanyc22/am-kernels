#include <stdio.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    printf("test-psram\n");
    volatile uint32_t *psram = (uint32_t *)0x8000221f;
    volatile uint32_t data;
    data = *psram;
    psram = (uint32_t *)0x80000000;
    data = *psram;
    psram = (uint32_t *)0x80082210;
    *((uint32_t *)psram) = 0x12345678;
    asm volatile(
        "li t0, 0x80082210\n"
        "li t1, 0x12345678\n"
        "sw t1, 0(t0)\n");
    data = *psram;
    printf("data: %lx\n", data);

    asm volatile(
        "li t0, 0x80082210\n"
        "li t1, 0x12345678\n"
        "sw t1, 0(t0)\n"
        "lw t2, 0(t0)\n");
    return 0;
}