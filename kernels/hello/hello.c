#include <am.h>
#include <klib.h>
#include <klib-macros.h>

int main(const char *args) {
  printf("Hello world!\n");
  const char *fmt =
    "Hello, AbstractMachine!\n"
    "mainargs = '%'.\n";

  for (const char *p = fmt; *p; p++) {
    (*p == '%') ? putstr(args) : putch(*p);
  }
  return 0;
}
