#include "acetza/muza/wavers/enveloper.h"

#include "acetza/muza/functions/transformers.h"
#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/enveloper/transform.h"
#include "acetza/muza/wavers/waver.h"

#include <stddef.h>

mz_enveloper_t mz_enveloper_default = {&mz_waver_default,
                                       1.0 / 16.0,
                                       1.0 / 12.0,
                                       1.0 / 8.0,
                                       1.0 / 2.0,
                                       1.0 / 4.0,
                                       mz_transformers_smooth,
                                       mz_transformers_smooth,
                                       mz_transformers_smooth};

void mz_enveloper_build(mz_enveloper_t *enveloper, mz_waver_t *waver,
                        mz_attack_t attack, mz_hold_t hold, mz_decay_t decay,
                        mz_sustain_t sustain, mz_release_t release,
                        mz_transformer_t attack_transformer,
                        mz_transformer_t decay_transformer,
                        mz_transformer_t release_transformer) {
  enveloper->waver = waver;
  enveloper->attack = attack;
  enveloper->hold = hold;
  enveloper->decay = decay;
  enveloper->sustain = sustain;
  enveloper->release = release;
  enveloper->attack_transformer = attack_transformer;
  enveloper->decay_transformer = decay_transformer;
  enveloper->release_transformer = release_transformer;
}

void mz_enveloper_copy(mz_enveloper_t *enveloper, mz_enveloper_t *other) {
  mz_enveloper_build(enveloper, other->waver, other->attack, other->hold,
                     other->decay, other->sustain, other->release,
                     other->attack_transformer, other->decay_transformer,
                     other->release_transformer);
}

void mz_enveloper_wave(mz_enveloper_t *enveloper, mz_wave_t *wave) {
  mz_waver_wave(enveloper->waver, wave);
  mz_duration_t duration = mz_wave_duration(wave);
  mz_transform_until_t until =
      mz_transform_until_release(enveloper, wave, duration);
  mz_transform(wave, enveloper->release_transformer, until.time,
               until.amplitude, duration, 0.0, duration);
}
