#include "acetza/printing.h"

#include "acetza/math.h"
#include "acetza/muza/types.h"
#include "acetza/types.h"

#include <glib.h>
#include <stdio.h>

void az_u64_print(u64_t number) {
  if (number < 1000) {
    printf("%ld", number);
    return;
  }
  az_u64_print(number / 1000);
  printf(",%03ld", number % 1000);
}

void az_rational_print(const az_rational_t *ration) {
  printf("[ ");
  az_u64_print(ration->numerator);
  printf(" / ");
  az_u64_print(ration->denominator);
  printf(" ]");
}

void az_rational_print_mz(const az_rational_t *ration) {
  printf("[ ");
  printf("%3ld", ration->numerator);
  printf(" / ");
  printf("%3ld", ration->denominator);
  printf(" ]");
}

u64_t az_u64_print_str_inner(u64_t number, char *str, u64_t printed) {
  if (number < 1000) {
    printed += sprintf(str + printed, "%ld", number);
    return printed;
  }
  printed = az_u64_print_str_inner(number / 1000, str + printed, printed);
  printed += sprintf(str + printed, ",%03ld", number % 1000);
  return printed;
}

u64_t az_u64_print_str(u64_t number, char *str) {
  return az_u64_print_str_inner(number, str, 0);
}

u64_t az_rational_print_str(const az_rational_t *ration, char *str) {
  u64_t printed = sprintf(str, "[ ");
  printed += az_u64_print_str(ration->numerator, str + printed);
  printed += sprintf(str + printed, " / ");
  printed += az_u64_print_str(ration->denominator, str + printed);
  printed += sprintf(str + printed, " ]");
  return printed;
}

void az_rational_array_print(GArray *array) {
  for (mz_index_t index = 0; index < array->len; ++index) {
    az_rational_t *ration = &g_array_index(array, az_rational_t, index);
    az_rational_print(ration);
  }
}

void az_rational_array_print_mz(GArray *array) {
  for (mz_index_t index = 0; index < array->len; ++index) {
    az_rational_t *ration = &g_array_index(array, az_rational_t, index);
    az_rational_print_mz(ration);
  }
}
