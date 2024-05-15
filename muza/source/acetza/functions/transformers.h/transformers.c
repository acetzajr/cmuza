#include "acetza/muza/functions/transformers.h"

#include "acetza/muza/types.h"
#include "acetza/types.h"

#include <math.h>

const f64_t AZ_HALF_PI = M_PI / 2.0;

mz_amplitude_t mz_transformers_smooth(mz_part_t part) {
  return sin(AZ_HALF_PI * part);
}

mz_amplitude_t mz_transformers_smooth_inverse(mz_part_t part) {
  return sin(AZ_HALF_PI * part + AZ_HALF_PI);
}
