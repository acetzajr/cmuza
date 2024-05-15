#include "acetza/muza/wavers/basic.h"

#include "acetza/muza/functions/primitives.h"
#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/types.h"
#include <math.h>

mz_basic_t mz_basic_default = {mz_primitives_sin, 360.0, 1.0, 1.0, 2, 44'100};

void mz_basic_build(mz_basic_t *basic, mz_primitive_t primitive,
                    mz_frequency_t frequency, mz_duration_t duration,
                    mz_amplitude_t amplitude, mz_channels_t channels,
                    mz_frame_rate_t frame_rate) {
  basic->primitive = primitive;
  basic->frequency = frequency;
  basic->duration = duration;
  basic->amplitude = amplitude;
  basic->channels = channels;
  basic->frame_rate = frame_rate;
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
