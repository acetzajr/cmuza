#pragma once

#include "acetza/types.h"

#include <glib.h>

extern f64_t az_epsilon;

typedef struct {
  u64_t numerator;
  u64_t denominator;
} az_rational_t;

extern az_rational_t mz_rational_1_1;
extern az_rational_t mz_rational_1_2;
extern az_rational_t mz_rational_2_1;

u64_t az_gcd(u64_t num_a, u64_t num_b);

void az_rational_copy(az_rational_t *src, az_rational_t *dst);

void az_rational_mul(az_rational_t *ration_a, az_rational_t *ration_b,
                     az_rational_t *result);

void az_rational_mul_fast(az_rational_t *ration_a, az_rational_t *ration_b,
                          az_rational_t *result);

void az_rational_div(az_rational_t *numerator, az_rational_t *denominator,
                     az_rational_t *result);

void az_rational_norm(az_rational_t *ration);

f64_t az_rational_f64(const az_rational_t *ration);

i64_t az_rational_cmp(const az_rational_t *ration_a,
                      const az_rational_t *ration_b);

i64_t az_rational_eq(const az_rational_t *ration_a,
                     const az_rational_t *ration_b);

gint az_rational_cmp_g(gconstpointer item_a, gconstpointer item_b);

u64_t az_u64_comma_digits(u64_t number);
