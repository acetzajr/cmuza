#pragma once

#include "acetza/muza/types.h"

typedef struct {
  mz_frames_t frames;
  mz_channels_t channels;
  mz_frame_rate_t frame_rate;
  mz_sample_t *samples;
} mz_wave_t;

// BUILD / FREE

void mz_wave_with_duration(mz_wave_t *wave, mz_duration_t duration,
                           mz_channels_t channels, mz_frame_rate_t frame_rate);

void mz_wave_free(mz_wave_t *wave);

// INPUT / OUTPUT

void mz_wave_save(mz_wave_t *wave, const char *path);

// GETTERS

mz_sample_t *mz_wave_sample(mz_wave_t *wave, mz_index_t frame,
                            mz_index_t channel);

mz_duration_t mz_wave_duration(mz_wave_t *wave);

mz_amplitude_t mz_wave_get_max(mz_wave_t *wave);

// OPERATIONS

void mz_wave_resize(mz_wave_t *wave, mz_size_t frames);

void mz_wave_resize_fill(mz_wave_t *wave, mz_size_t frames, mz_sample_t fill);

void mz_wave_add(mz_wave_t *wave, mz_wave_t *other, mz_time_t time,
                 mz_amplitude_t amplitude);

void mz_wave_add_mod(mz_wave_t *wave, mz_wave_t *other, mz_time_t time,
                     mz_amplitude_t amplitude);

void mz_wave_normalize(mz_wave_t *wave);

void mz_wave_clone(mz_wave_t *src, mz_wave_t *dst);

// EFFECTS

void mz_wave_reverb(mz_wave_t *wave, mz_bool_t extend, mz_count_t iterations,
                    mz_time_t delay, mz_amplitude_t decay);

// FRAME_RATE

mz_index_t mz_time_to_frame(mz_time_t time, mz_frame_rate_t frame_rate);

mz_time_t mz_frame_to_time(mz_index_t frame, mz_frame_rate_t frame_rate);
