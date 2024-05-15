#pragma once

#include "acetza/math.h"
#include "acetza/types.h"

extern az_rational_t mz_diatonic_up_mul;
extern az_rational_t mz_diatonic_down_mul;

void mz_rational_norm(az_rational_t *ration);

void mz_rational_set(az_rational_t *ration, u64_t numerator, u64_t denominator);
