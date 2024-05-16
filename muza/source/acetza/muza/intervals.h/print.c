#include "acetza/muza/intervals.h"

#include "acetza/math.h"
#include "acetza/muza/math.h"
#include "acetza/muza/types.h"
#include "acetza/panic.h"
#include "acetza/printing.h"
#include "acetza/types.h"
#include "glibconfig.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  az_rational_t ration1;
  az_rational_t ration2;
} mz_ration_pair_t;

az_rational_t mz_rational_1_1 = {.numerator = 1, .denominator = 1};
az_rational_t mz_rational_1_2 = {.numerator = 1, .denominator = 2};
az_rational_t mz_rational_2_1 = {.numerator = 2, .denominator = 1};

char *mz_ration_pair_str(mz_ration_pair_t *pair) {
  u64_t size = 17;
  size += az_u64_comma_digits(pair->ration1.numerator);
  size += az_u64_comma_digits(pair->ration1.denominator);
  size += az_u64_comma_digits(pair->ration2.numerator);
  size += az_u64_comma_digits(pair->ration2.denominator);
  char *str = malloc(sizeof(char) * size + 1);
  u64_t printed = az_rational_print_str(&pair->ration1, str);
  printed += sprintf(str + printed, " * ");
  printed += az_rational_print_str(&pair->ration2, str + printed);
  if (printed != size) {
    az_panic(1, "mz_ration_pair_str printed %ld, but should be %ld", printed,
             size);
  }
  return str;
}

guint mz_ration_pair_hash_g(gconstpointer key) {
  const mz_ration_pair_t *pair = key;
  return pair->ration1.numerator + pair->ration2.numerator +
         pair->ration1.denominator + pair->ration2.denominator;
}

guint mz_rational_hash_g(gconstpointer key) {
  const az_rational_t *ration = key;
  return ration->numerator + ration->denominator;
}

gboolean mz_rational_eq_g(gconstpointer item_a, gconstpointer item_b) {
  const az_rational_t *ration1 = item_a;
  const az_rational_t *ration2 = item_b;
  return (gboolean)az_rational_eq(ration1, ration2);
}

gboolean mz_ration_pair_eq_g(gconstpointer item_a, gconstpointer item_b) {
  const mz_ration_pair_t *pair_a = item_a;
  const mz_ration_pair_t *pair_b = item_b;
  if (!az_rational_eq(&pair_a->ration1, &pair_b->ration1)) {
    return FALSE;
  }
  if (!az_rational_eq(&pair_a->ration2, &pair_b->ration2)) {
    return FALSE;
  }
  return TRUE;
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

GArray *mz_diatonic() {
  GArray *diatonic = g_array_new(0, 0, sizeof(az_rational_t));
  g_array_append_vals(diatonic, &mz_rational_1_1, 1);
  mz_diatonic_up(diatonic);
  mz_diatonic_down(diatonic);
  g_array_sort(diatonic, az_rational_cmp_g);
  return diatonic;
}

GArray *mz_intervals_from_scale(GArray *scale) {
  GArray *intervals = g_array_new(0, 0, sizeof(az_rational_t));
  az_rational_t tmp[scale->len];
  az_rational_t *ration;
  az_rational_t *next;
  mz_index_t last = scale->len - 1;
  for (mz_index_t index = 0; index < last; ++index) {
    ration = &g_array_index(scale, az_rational_t, index);
    next = &g_array_index(scale, az_rational_t, index + 1);
    az_rational_div(next, ration, tmp + index);
  }
  ration = &g_array_index(scale, az_rational_t, last);
  next = &mz_rational_2_1;
  az_rational_div(next, ration, tmp + last);
  g_array_append_vals(intervals, tmp, scale->len);
  return intervals;
}

void mz_ration_test(az_rational_t *ration_a, az_rational_t *ration_b) {
  az_rational_t ration;
  az_rational_mul(ration_a, ration_b, &ration);
  az_rational_print(&ration);
  printf(" = ");
  az_rational_print(ration_a);
  printf(" * ");
  az_rational_print(ration_b);
  printf("\n");
}

void mz_find_intervals(GHashTable *table, GArray *array1, GArray *array2) {
  mz_ration_pair_t pair;
  az_rational_t ration;
  for (mz_index_t index1 = 0; index1 < array1->len; ++index1) {
    pair.ration1 = g_array_index(array1, az_rational_t, index1);
    for (mz_index_t index2 = 0; index2 < array2->len; ++index2) {
      pair.ration2 = g_array_index(array2, az_rational_t, index2);
      az_rational_mul(&pair.ration1, &pair.ration2, &ration);
      mz_rational_norm(&ration);
      if (ration.denominator > 256) {
        continue;
      }
      if (g_hash_table_contains(table, &ration)) {
        continue;
      }
      az_rational_t *key = g_new(az_rational_t, 1);
      *key = ration;
      g_hash_table_add(table, key);
    }
  }
}

void mz_print_intervals_table_entry(gpointer key, gpointer /*value*/,
                                    gpointer /*user_data*/) {
  const az_rational_t *ration = key;
  az_rational_print_mz(ration);
}

void mz_print_intervals_table(GHashTable *table) {
  g_hash_table_foreach(table, mz_print_intervals_table_entry, NULL);
  printf(" = table\n");
}

void mz_intervals_table_take(gpointer key, gpointer /*value*/,
                             gpointer /*user_data*/) {
  const az_rational_t *ration = key;
  az_rational_print(ration);
  printf("\n");
}

void mz_print_intervals() {
  GArray *diatonic = mz_diatonic();
  az_rational_array_print_mz(diatonic);
  printf(" = diatonic\n");
  GArray *diatonic_intervals = mz_intervals_from_scale(diatonic);
  az_rational_array_print_mz(diatonic_intervals);
  printf(" = diatonic intervals\n");
  GHashTable *table = g_hash_table_new(mz_rational_hash_g, mz_rational_eq_g);
  mz_find_intervals(table, diatonic, diatonic);
  mz_find_intervals(table, diatonic, diatonic_intervals);
  mz_find_intervals(table, diatonic_intervals, diatonic);
  mz_find_intervals(table, diatonic_intervals, diatonic_intervals);
  mz_print_intervals_table(table);
  GArray *intervals = g_array_new(FALSE, FALSE, sizeof(az_rational_t));
  GHashTableIter iter;
  gpointer key;
  g_hash_table_iter_init(&iter, table);
  while (g_hash_table_iter_next(&iter, &key, NULL)) {
    az_rational_t *table_ration = key;
    // printf("&table[%ld] = %ld\n", i++, (u64_t)table_ration);
    g_array_append_vals(intervals, table_ration, 1);
    g_hash_table_iter_steal(&iter);
    g_free(table_ration);
  }
  g_array_sort(intervals, az_rational_cmp_g);
  az_rational_array_print_mz(intervals);
  printf(" = intervals\n");
  /*
  for (mz_index_t index = 0; index < intervals->len; ++index) {
    az_rational_t *ration = &g_array_index(intervals, az_rational_t, index);
    printf("&intervals[%ld] = %ld\n", index, (u64_t)ration);
  }*/
  g_array_unref(diatonic);
  g_array_unref(diatonic_intervals);
  g_hash_table_unref(table);
  g_array_unref(intervals);
}
