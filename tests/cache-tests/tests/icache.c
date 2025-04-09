int main()
{
    for (register int i = 0; i < 100; i++)
        asm volatile("nop\nnop\nnop\nnop\nnop");
    return 0;
}
