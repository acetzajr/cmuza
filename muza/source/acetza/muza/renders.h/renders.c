#include "acetza/muza/renders.h"

#include "acetza/muza/intervals.h"
#include "acetza/muza/math.h"
#include "acetza/muza/synths/synth0.h"
#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"

#include <stdio.h>

void mz_hello() { printf("Hello muza\n"); }

void mz_master_0(mz_wave_t *wave) {
  mz_wave_reverb(wave, 1, 7, 1.0 / 12.0, 2.0 / 3.0);
  mz_wave_normalize(wave);
}

void mz_render_0() {
  mz_wave_t wave;
  mz_wave_new(&wave, 2, 44'100);
  mz_synth0_t synth;
  mz_synth0_init(&synth);
  mz_frequency_t base = 360.0;
  mz_time_t time = 0.0;
  {
    mz_wave_t tmp;
    synth.frequency = mz_rational_mul(&mzx01___1___1, base);
    mz_synth0_wave(&synth, &tmp);
    mz_wave_add(&wave, &tmp, time, 1.0);
  }
  {
    mz_wave_t tmp;
    synth.frequency = mz_rational_mul(&mzx05__81__64, base);
    mz_synth0_wave(&synth, &tmp);
    mz_wave_add(&wave, &tmp, time, 1.0);
  }
  time += 1.0;
  {
    mz_wave_t tmp;
    synth.frequency = mz_rational_mul(&mzx01___1___1, base);
    mz_synth0_wave(&synth, &tmp);
    mz_wave_add(&wave, &tmp, time, 1.0);
  }
  {
    mz_wave_t tmp;
    synth.frequency = mz_rational_mul(&mzx06___4___3, base);
    mz_synth0_wave(&synth, &tmp);
    mz_wave_add(&wave, &tmp, time, 1.0);
  }
  mz_master_0(&wave);
  mz_wave_save(&wave, "tmp/wave.wav");
}

void mz_render_1() {
  mz_wave_t wave;
  mz_wave_new(&wave, 2, 44'100);
  mz_synth0_t synth;
  mz_synth0_init(&synth);
  mz_frequency_t base = 90.0;
  mz_time_t time = 0.0;
  mz_time_t step = 1.0 / 4.0;
  synth.duration = step;
  for (mz_index_t i = 0; i < 3; ++i) {
    for (mz_index_t note = 0; note < 12; ++note, time += step) {
      {
        mz_wave_t tmp;
        synth.frequency = mz_rational_mul(mzx_intervals[note], base);
        mz_synth0_wave(&synth, &tmp);
        mz_wave_add(&wave, &tmp, time, 1.0);
      }
    }
  }

  mz_master_0(&wave);
  mz_wave_save(&wave, "tmp/wave.wav");
}

mz_render_t az_render_ref = mz_render_1;
