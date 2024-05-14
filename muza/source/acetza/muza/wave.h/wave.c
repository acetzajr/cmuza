#include "acetza/muza/wave.h"

#include "acetza/types.h"
#include <stdlib.h>

void mz_wave_free(mz_wave_t *wave) { free(wave->samples); }

void mz_wave_with_duration(mz_wave_t *wave, f64_t duration, u64_t channels,
                           u64_t frame_rate) {
  wave->frames = mz_time_to_frame(duration, frame_rate);
  wave->channels = channels;
  wave->frame_rate = frame_rate;
  wave->samples = malloc(sizeof(f64_t) * wave->frames * channels);
}

f64_t *mz_wave_get_sample(mz_wave_t *wave, u64_t frame, u64_t channel) {
  return &wave->samples[frame * wave->channels + channel];
}
