#pragma once

#include "acetza/math.h"
#include "acetza/types.h"

#include <glib.h>

void az_u64_print(u64_t number);

void az_rational_print(const az_rational_t *ration);

void az_rational_print_mz(const az_rational_t *ration);

void az_rational_array_print(GArray *array);

void az_rational_array_print_mz(GArray *array);

u64_t az_rational_print_str(const az_rational_t *ration, char *str);

u64_t az_u64_print_str(u64_t number, char *str);
