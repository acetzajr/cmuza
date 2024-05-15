#include "acetza/muza/intervals.h"

#include "acetza/math.h"
#include "acetza/muza/types.h"
#include "acetza/printing.h"

#include <glib.h>
#include <stdio.h>

az_rational_t mz_diatonic_up_mul = {.numerator = 3, .denominator = 2};
az_rational_t mz_diatonic_down_mul = {.numerator = 2, .denominator = 3};
az_rational_t mz_rational_1_1 = {.numerator = 1, .denominator = 1};
az_rational_t mz_rational_1_2 = {.numerator = 1, .denominator = 2};
az_rational_t mz_rational_2_1 = {.numerator = 2, .denominator = 1};

void mz_rational_norm(az_rational_t *ration) {
  while (az_rational_cmp(ration, &mz_rational_1_1) < 0) {
    az_rational_mul(ration, &mz_rational_2_1, ration);
  }
  while (az_rational_cmp(ration, &mz_rational_2_1) >= 0) {
    az_rational_mul(ration, &mz_rational_1_2, ration);
  }
}

void mz_diatonic_down(GArray *scale) {
  az_rational_t down_arm[3];
  az_rational_mul(&mz_rational_1_1, &mz_diatonic_down_mul, down_arm);
  mz_rational_norm(down_arm);
  az_rational_mul(down_arm, &mz_diatonic_down_mul, down_arm + 1);
  mz_rational_norm(down_arm + 1);
  az_rational_mul(down_arm + 1, &mz_diatonic_down_mul, down_arm + 2);
  mz_rational_norm(down_arm + 2);
  g_array_append_vals(scale, down_arm, 3);
}

void mz_diatonic_up(GArray *scale) {
  az_rational_t up_arm[3];
  az_rational_mul(&mz_rational_1_1, &mz_diatonic_up_mul, up_arm);
  mz_rational_norm(up_arm);
  az_rational_mul(up_arm, &mz_diatonic_up_mul, up_arm + 1);
  mz_rational_norm(up_arm + 1);
  az_rational_mul(up_arm + 1, &mz_diatonic_up_mul, up_arm + 2);
  mz_rational_norm(up_arm + 2);
  g_array_append_vals(scale, up_arm, 3);
}

void mz_diatonic(GArray *scale) {
  g_array_append_vals(scale, &mz_rational_1_1, 1);
  mz_diatonic_up(scale);
  mz_diatonic_down(scale);
  g_array_sort(scale, az_rational_gcmp);
}

void mz_print_intervals() {
  GArray *scale = g_array_new(FALSE, FALSE, sizeof(az_rational_t));
  mz_diatonic(scale);
  for (mz_index_t index = 0; index < scale->len; ++index) {
    az_rational_t *ration = &g_array_index(scale, az_rational_t, index);
    az_rational_print(ration);
  }
  printf("\n");
}
