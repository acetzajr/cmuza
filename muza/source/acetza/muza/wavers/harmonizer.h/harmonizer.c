#include "acetza/muza/wavers/harmonizer.h"

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/waver.h"

void mz_harmonizer_init(mz_harmonizer_t *harmonizer) {
  harmonizer->fundamental = mz_harmonizer_ref.fundamental;
  harmonizer->harmonic = mz_harmonizer_ref.harmonic;
  harmonizer->depth = mz_harmonizer_ref.depth;
  harmonizer->numberer = mz_harmonizer_ref.numberer;
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
