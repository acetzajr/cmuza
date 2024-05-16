#include "acetza/muza/math.h"

#include "acetza/math.h"
#include "acetza/types.h"

az_rational_t mz_diatonic_up_mul = {.numerator = 3, .denominator = 2};
az_rational_t mz_diatonic_down_mul = {.numerator = 2, .denominator = 3};

void mz_rational_norm(az_rational_t *ration) {
  az_rational_norm(ration);
  while (az_rational_cmp(ration, &mz_rational_1_1) < 0) {
    az_rational_mul_fast(ration, &mz_rational_2_1, ration);
  }
  while (az_rational_cmp(ration, &mz_rational_2_1) >= 0) {
    az_rational_mul_fast(ration, &mz_rational_1_2, ration);
  }
  az_rational_norm(ration);
}

void mz_rational_set(az_rational_t *ration, u64_t numerator,
                     u64_t denominator) {
  ration->numerator = numerator;
  ration->denominator = denominator;
  mz_rational_norm(ration);
}

f64_t mz_rational_mul(az_rational_t *ration, f64_t factor) {
  return az_rational_f64(ration) * factor;
}
