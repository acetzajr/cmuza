#include "acetza/printing.h"

#include "acetza/types.h"

#include <stdio.h>

void az_print_u64(u64_t number) {
  if (number < 1000) {
    printf("%ld", number);
    return;
  }
  az_print_u64(number / 1000);
  printf(",%03ld", number % 1000);
}
