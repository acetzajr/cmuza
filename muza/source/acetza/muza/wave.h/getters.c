#include "acetza/muza/wave.h"

#include "acetza/muza/types.h"

mz_duration_t mz_wave_duration(mz_wave_t *wave) {
  return mz_frame_to_time(wave->frames, wave->frame_rate);
}
