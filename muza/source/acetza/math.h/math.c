#include "acetza/math.h"

#include "acetza/types.h"
#include "glib.h"

f64_t az_epsilon = 0.000'1;

u64_t az_gcd(u64_t num_a, u64_t num_b) {
  // Everything divides 0
  if (num_a == 0) {
    return num_b;
  }
  if (num_b == 0) {
    return num_a;
  }
  // base case
  if (num_a == num_b) {
    return num_a;
  }
  // a is greater
  if (num_a > num_b) {
    return az_gcd(num_a - num_b, num_b);
  }
  return az_gcd(num_a, num_b - num_a);
}

void az_rational_copy(az_rational_t *src, az_rational_t *dst) {
  dst->numerator = src->numerator;
  dst->denominator = src->denominator;
}

void az_rational_mul(az_rational_t *ration_a, az_rational_t *ration_b,
                     az_rational_t *result) {
  result->numerator = ration_a->numerator * ration_b->numerator;
  result->denominator = ration_a->denominator * ration_b->denominator;
  az_rational_norm(result);
}

void az_rational_mul_fast(az_rational_t *ration_a, az_rational_t *ration_b,
                          az_rational_t *result) {
  result->numerator = ration_a->numerator * ration_b->numerator;
  result->denominator = ration_a->denominator * ration_b->denominator;
}

void az_rational_div(az_rational_t *numerator, az_rational_t *denominator,
                     az_rational_t *result) {
  az_rational_t copy_a;
  az_rational_t copy_b;
  az_rational_copy(numerator, &copy_a);
  az_rational_copy(denominator, &copy_b);
  result->numerator = copy_a.numerator * copy_b.denominator;
  result->denominator = copy_a.denominator * copy_b.numerator;
  az_rational_norm(result);
}

void az_rational_norm(az_rational_t *ration) {
  u64_t gcd = az_gcd(ration->numerator, ration->denominator);
  ration->numerator /= gcd;
  ration->denominator /= gcd;
}

f64_t az_rational_f64(const az_rational_t *ration) {
  return ((f64_t)ration->numerator) / ((f64_t)ration->denominator);
}

i64_t az_rational_cmp(const az_rational_t *ration_a,
                      const az_rational_t *ration_b) {
  f64_t float_a = az_rational_f64(ration_a);
  f64_t float_b = az_rational_f64(ration_b);
  f64_t difference = float_a - float_b;
  if (difference > az_epsilon) {
    return 1;
  }
  if (difference < -az_epsilon) {
    return -1;
  }
  return 0;
}

i64_t az_rational_eq(const az_rational_t *ration_a,
                     const az_rational_t *ration_b) {
  if (ration_a->numerator != ration_b->numerator) {
    return 0;
  }
  if (ration_a->denominator != ration_b->denominator) {
    return 0;
  }
  return 1;
}

gint az_rational_cmp_g(gconstpointer item_a, gconstpointer item_b) {
  return (gint)az_rational_cmp(item_a, item_b);
}

u64_t az_u64_comma_digits(u64_t number) {
  u64_t digits = 1;
  while (number >= 10) {
    ++digits;
    number /= 10;
  }
  u64_t commas = (digits - 1) / 3;
  return digits + commas;
}
