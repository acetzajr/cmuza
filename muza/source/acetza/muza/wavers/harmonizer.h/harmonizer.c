#include "acetza/muza/wavers/harmonizer.h"

#include "acetza/muza/functions/numberers.h"
#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/waver.h"

mz_harmonizer_t mz_harmonizer_default = {&mz_waver_default, &mz_waver_default,
                                         7, mz_numberers_saw};

void mz_harmonizer_build(mz_harmonizer_t *harmonizer, mz_waver_t *fundamental,
                         mz_waver_t *harmonic, mz_depth_t depth,
                         mz_numberer_t numberer) {
  harmonizer->fundamental = fundamental;
  harmonizer->harmonic = harmonic;
  harmonizer->depth = depth;
  harmonizer->numberer = numberer;
}

void mz_harmonizer_wave(mz_harmonizer_t *harmonizer, mz_wave_t *wave) {
  mz_waver_wave(harmonizer->fundamental, wave);
  mz_frequency_t frequency = mz_waver_frequency(harmonizer->fundamental);
  for (mz_index_t index = 2; index - 1 < harmonizer->depth; ++index) {
    mz_index_t number = harmonizer->numberer(index);
    mz_waver_set_frequency(harmonizer->harmonic,
                           frequency * (mz_frequency_t)number);
    mz_wave_t tmp;
    mz_waver_wave(harmonizer->harmonic, &tmp);
    mz_wave_add(wave, &tmp, 0.0, 1.0 / (mz_amplitude_t)number);
    mz_wave_free(&tmp);
  }
  mz_wave_normalize(wave);
}
