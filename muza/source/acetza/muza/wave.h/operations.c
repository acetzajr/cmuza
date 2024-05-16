#include "acetza/muza/wave.h"

#include "acetza/muza/types.h"
#include "acetza/panic.h"
#include "acetza/types.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void mz_wave_resize(mz_wave_t *wave, mz_size_t frames) {
  wave->frames = frames;
  mz_size_t size = sizeof(mz_sample_t) * frames * wave->channels;
  mz_sample_t *samples;
  if (wave->samples == NULL) {
    samples = malloc(size);
  } else {
    samples = realloc(wave->samples, size);
  }
  if (samples == NULL) {
    az_panic(1, "could not resize the wave");
  }
  wave->samples = samples;
}

void mz_wave_resize_fill(mz_wave_t *wave, mz_size_t frames, mz_sample_t fill) {
  mz_size_t old_size = wave->frames;
  mz_wave_resize(wave, frames);
  if (old_size >= frames) {
    return;
  }
  for (mz_index_t frame = old_size; frame < wave->frames; ++frame) {
    for (mz_index_t channel = 0; channel < wave->channels; ++channel) {
      *mz_wave_sample(wave, frame, channel) = fill;
    }
  }
}

void mz_wave_normalize(mz_wave_t *wave) {
  mz_amplitude_t max = mz_wave_get_max(wave);
  if (max == 0.0) {
    return;
  }
  mz_amplitude_t amplitude = 1.0 / max;
  mz_wave_mul(wave, amplitude);
}

void mz_wave_mul(mz_wave_t *wave, mz_amplitude_t amplitude) {
  for (mz_index_t index = 0; index < wave->frames * wave->channels; ++index) {
    wave->samples[index] *= amplitude;
  }
}

void mz_wave_clone(mz_wave_t *src, mz_wave_t *dst) {
  dst->frames = src->frames;
  dst->channels = src->channels;
  dst->frame_rate = src->frame_rate;
  mz_size_t size = sizeof(f64_t) * dst->frames * dst->channels;
  dst->samples = malloc(size);
  memcpy(dst->samples, src->samples, size);
}
