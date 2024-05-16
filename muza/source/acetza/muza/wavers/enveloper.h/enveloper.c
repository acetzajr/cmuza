#include "acetza/muza/wavers/enveloper.h"

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/enveloper/transform.h"
#include "acetza/muza/wavers/waver.h"
#include "acetza/panic.h"

#include <stddef.h>

void mz_enveloper_init(mz_enveloper_t *enveloper) {
  enveloper->wavers.waver = NULL;
  enveloper->attack = mz_enveloper_initializer.attack;
  enveloper->hold = mz_enveloper_initializer.hold;
  enveloper->decay = mz_enveloper_initializer.decay;
  enveloper->sustain = mz_enveloper_initializer.sustain;
  enveloper->release = mz_enveloper_initializer.release;
  enveloper->attack_transformer = mz_enveloper_initializer.attack_transformer;
  enveloper->decay_transformer = mz_enveloper_initializer.decay_transformer;
  enveloper->release_transformer = mz_enveloper_initializer.release_transformer;
}

void mz_enveloper_wave(mz_enveloper_t *enveloper, mz_wave_t *wave) {
  if (enveloper->wavers.waver == NULL) {
    az_panic(1, "enveloper waver is null");
  }
  mz_waver_wave(enveloper->wavers.waver, wave);
  mz_duration_t duration = mz_wave_duration(wave);
  mz_transform_until_t until =
      mz_transform_until_release(enveloper, wave, duration);
  mz_transform(wave, enveloper->release_transformer, until.time,
               until.amplitude, duration, 0.0, duration);
}
