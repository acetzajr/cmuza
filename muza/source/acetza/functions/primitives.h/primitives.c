#include "acetza/muza/functions/primitives.h"

#include "acetza/types.h"

#include <math.h>

f64_t mz_primitives_saw(f64_t part) { return 1.0 - 2.0 * part; }

f64_t mz_primitives_sqr(f64_t part) { return part < 0.5 ? 1.0 : -1.0; }

f64_t mz_primitives_tri(f64_t part) {
  if (part < 0.25) {
    return 4.0 * part;
  }
  if (part < 0.75) {
    return 2.0 - 4.0 * part;
  }
  return 4.0 * part - 4.0;
}

f64_t mz_primitives_sin(f64_t part) { return sin(2.0 * M_PI * part); }
