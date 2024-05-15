#include "acetza/printing.h"

#include "acetza/math.h"
#include "acetza/types.h"

#include <stdio.h>

void az_u64_print(u64_t number) {
  if (number < 1000) {
    printf("%ld", number);
    return;
  }
  az_u64_print(number / 1000);
  printf(",%03ld", number % 1000);
}

void az_rational_print(az_rational_t *ration) {
  printf("[ ");
  az_u64_print(ration->numerator);
  printf(" / ");
  az_u64_print(ration->denominator);
  printf(" ]");
}
