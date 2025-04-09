#include <stdio.h>
#include <stdint.h>

#include <am.h>
#include <klib-macros.h>

static uint64_t uptime() { return io_read(AM_TIMER_UPTIME).us; }

int main(int argc, char const *argv[])
{
    printf("AM_TIMER_UPTIME: %x\n", AM_TIMER_UPTIME);
    uint64_t t0 = uptime();
    printf("uptime h32: %ld\n", (uint32_t)(t0 >> 32));
    printf("uptime l32: %ld\n", (uint32_t)t0);
    return 0;
}
