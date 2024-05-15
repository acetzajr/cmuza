#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"

struct WvBasic {
  mz_primitive_t primitive;
  mz_frequency_t frequency;
  mz_duration_t duration;
  mz_amplitude_t amplitude;
  mz_channels_t channels;
  mz_frame_rate_t frame_rate;
};

typedef struct WvBasic mz_basic_t;

extern mz_basic_t mz_basic_ref;

void mz_basic_init(mz_basic_t *basic);

void mz_basic_wave(mz_basic_t *basic, mz_wave_t *wave);
