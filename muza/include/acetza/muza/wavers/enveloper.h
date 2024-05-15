#pragma once

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/waver.h"

typedef struct {
  mz_waver_t *waver;
  mz_attack_t attack;
  mz_hold_t hold;
  mz_decay_t decay;
  mz_sustain_t sustain;
  mz_release_t release;
  mz_transformer_t attack_transformer;
  mz_transformer_t decay_transformer;
  mz_transformer_t release_transformer;
} mz_enveloper_t;

extern mz_enveloper_t mz_enveloper_ref;

void mz_enveloper_init(mz_enveloper_t *enveloper);

void mz_enveloper_wave(mz_enveloper_t *enveloper, mz_wave_t *wave);
