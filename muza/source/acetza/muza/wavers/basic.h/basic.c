#include "acetza/muza/wavers/basic.h"

#include "acetza/muza/wave.h"
#include "acetza/types.h"
#include <math.h>

void mz_basic_init(mz_basic_t *basic) {
  basic->primitive = mz_basic_ref.primitive;
  basic->frequency = mz_basic_ref.frequency;
  basic->duration = mz_basic_ref.duration;
  basic->amplitude = mz_basic_ref.amplitude;
  basic->channels = mz_basic_ref.channels;
  basic->frame_rate = mz_basic_ref.frame_rate;
}

void mz_basic_wave(mz_basic_t *basic, mz_wave_t *wave) {
  mz_wave_with_duration(wave, basic->duration, basic->channels,
                        basic->frame_rate);
  for (u64_t frame = 0; frame < wave->frames; ++frame) {
    f64_t time = mz_frame_to_time(frame, wave->frame_rate);
    f64_t part = fmod(time * basic->frequency, 1.0);
    f64_t sample = basic->primitive(part) * basic->amplitude;
    for (u64_t channel = 0; channel < wave->channels; ++channel) {
      *mz_wave_sample(wave, frame, channel) = sample;
    }
  }
}
