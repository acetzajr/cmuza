#pragma once

#include "acetza/muza/functions/primitives.h"
#include "acetza/muza/wave.h"
#include "acetza/types.h"

struct BasicWaver {
  mz_primitive_t primitive;
  f64_t frequency;
  f64_t duration;
  f64_t amplitude;
  u64_t channels;
  u64_t frame_rate;
};

typedef struct BasicWaver wv_basic_t;

void mz_basic_default(wv_basic_t *basic);

void mz_basic_wave(wv_basic_t *basic, mz_wave_t *wave);
