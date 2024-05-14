#include "acetza/printing.h"

#include <stdio.h>

void az_print_long_with_comas(long n) {
  if (n < 1000) {
    printf("%ld", n);
    return;
  }
  az_print_long_with_comas(n / 1000);
  printf(",%03ld", n % 1000);
}
