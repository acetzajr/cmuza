#include "acetza/muza/synths/synth0.h"

#include "acetza/muza/functions/numberers.h"
#include "acetza/muza/functions/primitives.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/basic.h"
#include "acetza/muza/wavers/enveloper.h"
#include "acetza/muza/wavers/harmonizer.h"
#include "acetza/muza/wavers/waver.h"

void mz_synth0_init(mz_synth0_t *synth) {
  mz_basic_initializer.primitive = mz_primitives_tri;
  mz_harmonizer_initializer.numberer = mz_numberers_sqr;
  mz_basic_init(&synth->wavers.basic);
  mz_waver_init(&synth->generics.basic, MZ_BASIC, &synth->wavers.basic);
  mz_harmonizer_init(&synth->wavers.harmonizer, &synth->generics.basic,
                     &synth->generics.basic);
  mz_waver_init(&synth->generics.harmonizer, MZ_HARMONIZER,
                &synth->wavers.harmonizer);
  mz_enveloper_init(&synth->wavers.enveloper, &synth->generics.harmonizer);
  mz_waver_init(&synth->generics.enveloper, MZ_ENVELOPER,
                &synth->wavers.enveloper);
  synth->frequency = 360.0;
  synth->duration = 1.0;
  synth->amplitude = 1.0;
}

void mz_synth0_wave(mz_synth0_t *synth, mz_wave_t *wave) {
  mz_waver_set_frequency(&synth->generics.enveloper, synth->frequency);
  mz_waver_set_duration(&synth->generics.enveloper, synth->duration);
  mz_waver_wave(&synth->generics.enveloper, wave);
  // mz_wave_reverb(wave, 1, 7, 1.0 / 16.0, 1.0 / 2.0);
  // mz_wave_normalize(wave);
  mz_wave_mul(wave, synth->amplitude);
}
