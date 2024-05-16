#include "acetza/muza/wave.h"

#include "acetza/muza/types.h"
#include <stddef.h>
#include <stdlib.h>

void mz_wave_free(mz_wave_t *wave) { free(wave->samples); }

void mz_wave_with_duration(mz_wave_t *wave, mz_duration_t duration,
                           mz_channels_t channels, mz_frame_rate_t frame_rate) {
  wave->frames = mz_time_to_frame(duration, frame_rate);
  wave->channels = channels;
  wave->frame_rate = frame_rate;
  mz_size_t size = sizeof(mz_sample_t) * wave->frames * channels;
  if (size == 0) {
    wave->samples = NULL;
    return;
  }
  wave->samples = malloc(size);
}

void mz_wave_new(mz_wave_t *wave, mz_channels_t channels,
                 mz_frame_rate_t frame_rate) {
  wave->frames = 0;
  wave->channels = channels;
  wave->frame_rate = frame_rate;
  wave->samples = NULL;
}
