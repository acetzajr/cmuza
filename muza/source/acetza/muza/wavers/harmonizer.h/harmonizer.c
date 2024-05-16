#include "acetza/muza/wavers/harmonizer.h"

#include "acetza/muza/functions/numberers.h"
#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/waver.h"
#include "acetza/panic.h"

#include <stddef.h>

mz_harmonizer_initializer_t mz_harmonizer_initializer = {
    .depth = 7, .numberer = mz_numberers_saw};

void mz_harmonizer_init(mz_harmonizer_t *harmonizer) {
  harmonizer->wavers.fundamental = NULL;
  harmonizer->wavers.harmonic = NULL;
  harmonizer->depth = mz_harmonizer_initializer.depth;
  harmonizer->numberer = mz_harmonizer_initializer.numberer;
}

void mz_harmonizer_wave(mz_harmonizer_t *harmonizer, mz_wave_t *wave) {
  if (harmonizer->wavers.fundamental == NULL) {
    az_panic(1, "harmonizer fundamental is null");
  }
  if (harmonizer->wavers.harmonic == NULL) {
    az_panic(1, "harmonizer harmonic is null");
  }
  mz_waver_wave(harmonizer->wavers.fundamental, wave);
  mz_frequency_t frequency = mz_waver_frequency(harmonizer->wavers.fundamental);
  for (mz_index_t index = 2; index - 1 < harmonizer->depth; ++index) {
    mz_index_t number = harmonizer->numberer(index);
    mz_waver_set_frequency(harmonizer->wavers.harmonic,
                           frequency * (mz_frequency_t)number);
    mz_wave_t tmp;
    mz_waver_wave(harmonizer->wavers.harmonic, &tmp);
    mz_wave_add(wave, &tmp, 0.0, 1.0 / (mz_amplitude_t)number);
    mz_wave_free(&tmp);
  }
  mz_wave_normalize(wave);
}
