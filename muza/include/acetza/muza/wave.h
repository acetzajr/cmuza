#pragma once

#include "acetza/types.h"

struct MuzaWave {
  u64_t frames;
  u64_t channels;
  u64_t frame_rate;
  f64_t *samples;
};

typedef struct MuzaWave mz_wave_t;

void mz_wave_free(mz_wave_t *wave);

void mz_wave_with_duration(mz_wave_t *wave, f64_t duration, u64_t channels,
                           u64_t frame_rate);

u64_t mz_time_to_frame(f64_t time, u64_t frame_rate);

f64_t mz_frame_to_time(u64_t frame, u64_t frame_rate);

f64_t *mz_wave_get_sample(mz_wave_t *wave, u64_t frame, u64_t channel);
