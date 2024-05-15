#include "acetza/muza/wave.h"

#include "acetza/muza/types.h"

mz_duration_t mz_wave_duration(mz_wave_t *wave) {
  return mz_frame_to_time(wave->frames, wave->frame_rate);
}

mz_amplitude_t mz_wave_get_max(mz_wave_t *wave) {
  mz_amplitude_t max = 0.0;
  for (mz_index_t index = 0; index < wave->frames * wave->channels; ++index) {
    if (wave->samples[index] > max) {
      max = wave->samples[index];
    }
  }
  return max;
}
