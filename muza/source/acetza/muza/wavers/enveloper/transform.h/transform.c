#include "acetza/muza/wavers/enveloper/transform.h"

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/enveloper.h"
#include "acetza/types.h"

mz_transform_until_t mz_transform_until_release(mz_enveloper_t *enveloper,
                                                mz_wave_t *wave,
                                                mz_duration_t duration) {
  mz_transform_until_t until;
  mz_time_t release_start = duration - enveloper->release;
  if (release_start <= 0.0) {
    until.time = 0.0;
    until.amplitude = 1.0;
    return until;
  }
  mz_transform_result_t result;
  result = mz_transform(wave, enveloper->attack_transformer, 0.0, 0.0,
                        enveloper->attack, 1.0, release_start);
  if (result.disrupted) {
    until.time = release_start;
    until.amplitude = result.amplitude;
    return until;
  }
  mz_time_t hold_end = enveloper->attack + enveloper->hold;
  if (hold_end >= release_start) {
    until.time = release_start;
    until.amplitude = 1.0;
    return until;
  }
  mz_time_t decay_end = hold_end + enveloper->decay;
  result = mz_transform(wave, enveloper->decay_transformer, hold_end, 1.0,
                        decay_end, enveloper->sustain, release_start);
  if (result.disrupted) {
    until.time = release_start;
    until.amplitude = result.amplitude;
    return until;
  }
  mz_index_t start = mz_time_to_frame(decay_end, wave->frame_rate);
  mz_index_t end = mz_time_to_frame(release_start, wave->frame_rate);
  for (mz_index_t frame = start; frame < end; ++frame) {
    for (mz_index_t channel = 0; channel < wave->channels; ++channel) {
      *mz_wave_sample(wave, frame, channel) *= enveloper->sustain;
    }
  }
  until.time = release_start;
  until.amplitude = enveloper->sustain;
  return until;
}

mz_transform_result_t
mz_transform(mz_wave_t *wave, mz_transformer_t transformer,
             mz_time_t start_time, mz_amplitude_t start_amplitude,
             mz_time_t end_time, mz_amplitude_t end_amplitude,
             mz_time_t limit) {
  mz_index_t frame_limit = mz_time_to_frame(limit, wave->frame_rate);
  mz_index_t start = mz_time_to_frame(start_time, wave->frame_rate);
  mz_index_t end = mz_time_to_frame(end_time, wave->frame_rate);
  mz_amplitude_t difference = end_amplitude - start_amplitude;
  mz_amplitude_t last = start_amplitude + transformer(0.0) * difference;
  f64_t frames = (f64_t)(end - start);
  mz_transform_result_t result;
  f64_t index = 0.0;
  for (mz_index_t frame = start; frame < end; ++frame, ++index) {
    if (frame >= frame_limit) {
      result.disrupted = 1;
      result.amplitude = last;
      result.time = mz_frame_to_time(frame, wave->frame_rate);
      return result;
    }
    mz_part_t part = index / frames;
    last = start_amplitude + transformer(part) * difference;
    for (mz_index_t channel = 0; channel < wave->channels; ++channel) {
      *mz_wave_sample(wave, frame, channel) *= last;
    }
  }
  result.disrupted = 0;
  result.amplitude = last;
  result.time = end_time;
  return result;
}
