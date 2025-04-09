#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>
#include <limits.h>

__attribute__((noinline)) void check(bool cond)
{
    if (!cond)
        halt(1);
}

#define N 32
uint8_t data[N];

// 检查[l,r)区间中的值是否依次为val, val + 1, val + 2...
void check_seq(int l, int r, int val)
{
    int i;
    for (i = l; i < r; i++)
    {
        check(data[i] == val + i - l);
    }
}

// 检查[l,r)区间中的值是否均为val
void check_eq(int l, int r, int val)
{
    int i;
    for (i = l; i < r; i++)
    {
        check(data[i] == val);
    }
}

void reset()
{
    int i;
    for (i = 0; i < N; i++)
    {
        data[i] = i + 1;
    }
}

void test_strcpy()
{
    char buf[] = "0123456789";
    for (int i = 0; i < 10; i++)
    {
        check(strcpy((char *)data + i, buf) == (char *)data + i);
        check_seq(i, i + 1, buf[0]);
        check_seq(i, i + sizeof(buf) / sizeof(char) - 1, buf[0]);
    }
}

void test_strncpy()
{
    char buf[] = "0123456789";
    int buf_len = sizeof(buf) / sizeof(char) - 1;
    int n = 5;
    for (int i = 0; i < 10; i++)
    {
        check(strncpy((char *)data + i, buf, n) == (char *)data + i + n);
        check_seq(i, i + n, buf[0]);
    }
    n = buf_len + 4;
    for (int i = 0; i < 10; i++)
    {
        check(strncpy((char *)data + i, buf, n) == (char *)data + i + n);
        check_seq(i, i + buf_len, buf[0]);
        for (size_t j = 0; j < n; j++)
        {
            if (j < buf_len)
            {
                check(data[i + j] == buf[j]);
            }
            else
            {
                check(data[i + j] == '\0');
            }
        }
    }
}

void test_strcat()
{
    char buf[] = "0123456789";
    int buf_len = sizeof(buf) / sizeof(char) - 1;
    data[0] = '\0';
    check(strcat((char *)data, buf) == (char *)data);
    check_seq(0, buf_len, buf[0]);
    check_seq(buf_len, buf_len + 1, '\0');
    check(strcat((char *)data, buf) == (char *)data);
    check_seq(buf_len, buf_len * 2, buf[0]);
}

void test_memset()
{
    int l, r;
    for (l = 0; l < N; l++)
    {
        for (r = l + 1; r <= N; r++)
        {
            reset();
            uint8_t val = (l + r) / 2;
            memset(data + l, val, r - l);
            check_seq(0, l, 1);
            check_eq(l, r, val);
            check_seq(r, N, r + 1);
        }
    }
}

void test_memmove()
{
    char buf[] = "0123456789";
    int buf_len = sizeof(buf) / sizeof(char) - 1;
    for (size_t i = 0; i < 10; i++)
    {
        check(memmove(data + i, buf, buf_len) == data + i);
        check_seq(i, i + buf_len, buf[0]);
    }
    memmove(data, buf, buf_len);
    for (size_t i = 1; i < 10; i++)
    {
        check(memmove(data + i, data + i - 1, buf_len) == data + i);
        check_seq(i, i + buf_len, buf[0]);
    }
}

void test_memcpy()
{
    char buf[] = "0123456789";
    int buf_len = sizeof(buf) / sizeof(char) - 1;
    for (size_t i = 0; i < 10; i++)
    {
        check(memmove(data + i, buf, buf_len) == data + i);
        check_seq(i, i + buf_len, buf[0]);
    }
}

void test_strlen()
{
    char buf[] = "0123456789";
    int buf_len = sizeof(buf) / sizeof(char) - 1;
    for (size_t i = 0; i < 4; i++)
    {
        check(strlen(buf + i) == buf_len - i);
    }
}

void test_strcmp()
{
    char buf[128] = "0123456789";
    data[0] = '\0';
    check(strcmp(buf, buf) == 0);
    check(strcmp(buf, (char *)data) > 0);
    data[0] = '1';
    check(strcmp(buf, (char *)data) < 0);

    sprintf(buf, "%s", "Hello world!\n");
    check(strcmp(buf, "Hello world!\n") == 0);

    sprintf(buf, "%d + %d = %d\n", 1, 1, 2);
    check(strcmp(buf, "1 + 1 = 2\n") == 0);

    sprintf(buf, "%d + %d = %d\n", 2, 10, 12);
    check(strcmp(buf, "2 + 10 = 12\n") == 0);
}

void test_strncmp()
{
    char buf[] = "0123456789";
    int buf_len = sizeof(buf) / sizeof(char) - 1;
    data[0] = '\0';
    check(strncmp(buf, buf, buf_len) == 0);
    check(strncmp(buf, (char *)data, buf_len) > 0);
    data[0] = '1';
    check(strncmp(buf, (char *)data, buf_len) < 0);
}

void test_memcmp()
{
    char buf[] = "0123456789";
    int buf_len = sizeof(buf) / sizeof(char) - 1;
    data[0] = '\0';
    check(memcmp(buf, buf, buf_len) == 0);
    check(memcmp(buf, (char *)data, buf_len) > 0);
    data[0] = '1';
    check(memcmp(buf, (char *)data, buf_len) < 0);
}

void test_sprintf()
{
    char buf[128];
    long long data_test[] = {
        0, INT_MAX / 17, INT_MAX, INT_MIN, INT_MIN + 1,
        UINT_MAX / 17, INT_MAX / 17, UINT_MAX};
    char data_test_str[][32] = {
        "0", "126322567", "2147483647", "-2147483648", "-2147483647",
        "252645135", "126322567", "-1"};
    sprintf(buf, "Hello world!");
    check(strcmp(buf, "Hello world!") == 0);
    sprintf(buf, "Hello %s!", "world");
    check(strcmp(buf, "Hello world!") == 0);
    sprintf(buf, "Hello %s! %d + %d = %d", "world", 1, 2, 3);
    check(strcmp(buf, "Hello world! 1 + 2 = 3") == 0);
    for (size_t i = 0; i < sizeof(data_test) / sizeof(long long); i++)
    {
        sprintf(buf, "%d", data_test[i]);
        check(strcmp(buf, data_test_str[i]) == 0);
    }
}

int main(int argc, char const *argv[])
{
    // first test, for write related functions
    test_strcpy();
    // test_strncpy();
    test_strcat();
    test_memset();
    test_memmove();
    test_memcpy();

    // second test, for read-only related functions
    test_strlen();
    test_strcmp();
    test_strncmp();
    test_memcmp();

    // third test, for sprintf
    test_sprintf();

    printf("[INFO] All tests passed.\n");
    return 0;
}
