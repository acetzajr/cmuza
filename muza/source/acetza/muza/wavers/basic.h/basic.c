#include "acetza/muza/wavers/basic.h"

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"

#include <math.h>

void mz_basic_init(mz_basic_t *basic) {
  basic->primitive = mz_basic_initializer.primitive;
  basic->frequency = mz_basic_initializer.frequency;
  basic->duration = mz_basic_initializer.duration;
  basic->channels = mz_basic_initializer.channels;
  basic->frame_rate = mz_basic_initializer.frame_rate;
}

void mz_basic_wave(mz_basic_t *basic, mz_wave_t *wave) {
  mz_wave_with_duration(wave, basic->duration, basic->channels,
                        basic->frame_rate);
  for (mz_index_t frame = 0; frame < wave->frames; ++frame) {
    mz_time_t time = mz_frame_to_time(frame, wave->frame_rate);
    mz_part_t part = fmod(time * basic->frequency, 1.0);
    mz_sample_t sample = basic->primitive(part);
    for (mz_index_t channel = 0; channel < wave->channels; ++channel) {
      *mz_wave_sample(wave, frame, channel) = sample;
    }
  }
}
