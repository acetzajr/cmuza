#pragma once

#include "acetza/muza/types.h"

struct MuzaWave {
  mz_frames_t frames;
  mz_channels_t channels;
  mz_frame_rate_t frame_rate;
  mz_sample_t *samples;
};

typedef struct MuzaWave mz_wave_t;

void mz_wave_free(mz_wave_t *wave);

void mz_wave_with_duration(mz_wave_t *wave, mz_duration_t duration,
                           mz_channels_t channels, mz_frame_rate_t frame_rate);

mz_index_t mz_time_to_frame(mz_time_t time, mz_frame_rate_t frame_rate);

mz_time_t mz_frame_to_time(mz_index_t frame, mz_frame_rate_t frame_rate);

mz_sample_t *mz_wave_sample(mz_wave_t *wave, mz_index_t frame,
                            mz_index_t channel);

void mz_wave_save(mz_wave_t *wave, const char *path);

mz_duration_t mz_wave_duration(mz_wave_t *wave);
