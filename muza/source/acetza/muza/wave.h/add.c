#include "acetza/muza/wave.h"

#include "acetza/muza/types.h"
#include <sys/param.h>

void mz_wave_add(mz_wave_t *wave, mz_wave_t *other, mz_time_t time,
                 mz_amplitude_t amplitude) {
  mz_index_t start = mz_time_to_frame(time, wave->frame_rate);
  mz_index_t end = start + other->frames;
  if (end > wave->frames) {
    mz_wave_resize_fill(wave, end, 0.0);
  }
  mz_count_t channels = MIN(wave->channels, other->channels);
  mz_index_t other_frame = 0;
  for (mz_index_t wave_frame = start; wave_frame < end;
       ++wave_frame, ++other_frame) {
    for (mz_index_t channel = 0; channel < channels; ++channel) {
      *mz_wave_sample(wave, wave_frame, channel) +=
          *mz_wave_sample(other, other_frame, channel) * amplitude;
    }
  }
}

void mz_wave_add_mod(mz_wave_t *wave, mz_wave_t *other, mz_time_t time,
                     mz_amplitude_t amplitude) {
  mz_count_t channels = MIN(wave->channels, other->channels);
  for (mz_index_t
           other_frame = 0,
           frame = mz_time_to_frame(time, wave->frame_rate) % wave->frames;
       other_frame < other->frames;
       ++other_frame, frame = (frame + 1) % wave->frames) {
    for (mz_index_t channel = 0; channel < channels; ++channel) {
      *mz_wave_sample(wave, frame, channel) +=
          *mz_wave_sample(other, other_frame, channel) * amplitude;
    }
  }
}
