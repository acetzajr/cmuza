#include "acetza/muza/wavers/basic.h"

#include "acetza/muza/functions/primitives.h"
#include "acetza/muza/wave.h"
#include "acetza/types.h"
#include <math.h>

void mz_basic_default(wv_basic_t *basic) {
  basic->primitive = mz_primitives_saw;
  basic->frequency = 360.0;
  basic->duration = 1.0;
  basic->amplitude = 1.0;
  basic->channels = 2;
  basic->frame_rate = 44'100;
}

void mz_basic_wave(wv_basic_t *basic, mz_wave_t *wave) {
  mz_wave_with_duration(wave, basic->duration, basic->channels,
                        basic->frame_rate);
  for (u64_t frame = 0; frame < wave->frames; ++frame) {
    f64_t time = mz_frame_to_time(frame, wave->frame_rate);
    f64_t part = fmod(time * basic->frequency, 1.0);
    f64_t sample = basic->primitive(part) * basic->amplitude;
    for (u64_t channel = 0; channel < wave->channels; ++channel) {
      *mz_wave_get_sample(wave, frame, channel) = sample;
    }
  }
}
