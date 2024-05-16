#include "acetza/muza/synths/synth0.h"
#include "acetza/muza/wavers/basic.h"
#include "acetza/muza/wavers/enveloper.h"
#include "acetza/muza/wavers/harmonizer.h"

void mz_synth0_init(mz_synth0_t *synth) {
  mz_basic_init(&synth->insides.basic);
  mz_harmonizer_init(&synth->insides.harmonizer);
  mz_enveloper_init(&synth->insides.enveloper);
}

void mz_synth0_wave(mz_synth0_t * /*synth*/) {}
