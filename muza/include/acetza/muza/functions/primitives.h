#pragma once

#include "acetza/types.h"

typedef f64_t (*mz_primitive_t)(f64_t part);

f64_t mz_primitives_saw(f64_t part);

f64_t mz_primitives_sqr(f64_t part);

f64_t mz_primitives_tri(f64_t part);

f64_t mz_primitives_sin(f64_t part);
