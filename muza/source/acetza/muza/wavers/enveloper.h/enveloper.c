#include "acetza/muza/wavers/enveloper.h"

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/enveloper/transform.h"
#include "acetza/muza/wavers/waver.h"



void mz_enveloper_init(mz_enveloper_t *enveloper) {
  enveloper->waver = mz_enveloper_ref.waver;
  enveloper->attack = mz_enveloper_ref.attack;
  enveloper->hold = mz_enveloper_ref.hold;
  enveloper->decay = mz_enveloper_ref.decay;
  enveloper->sustain = mz_enveloper_ref.sustain;
  enveloper->release = mz_enveloper_ref.release;
  enveloper->attack_transformer = mz_enveloper_ref.attack_transformer;
  enveloper->decay_transformer = mz_enveloper_ref.decay_transformer;
  enveloper->release_transformer = mz_enveloper_ref.release_transformer;
}

void mz_enveloper_wave(mz_enveloper_t *enveloper, mz_wave_t *wave) {
  mz_waver_wave(enveloper->waver, wave);
  mz_duration_t duration = mz_wave_duration(wave);
  mz_transform_until_t until =
      mz_transform_until_release(enveloper, wave, duration);
  mz_transform(wave, enveloper->release_transformer, until.time,
               until.amplitude, duration, 0.0, duration);
}
