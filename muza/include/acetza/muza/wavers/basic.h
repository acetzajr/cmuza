#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"

typedef struct {
  mz_primitive_t primitive;
  mz_frequency_t frequency;
  mz_duration_t duration;
  mz_channels_t channels;
  mz_frame_rate_t frame_rate;
} mz_basic_t;

typedef mz_basic_t mz_basic_initializer_t;

extern mz_basic_initializer_t mz_basic_initializer;

void mz_basic_init(mz_basic_t *basic);

void mz_basic_wave(mz_basic_t *basic, mz_wave_t *wave);
