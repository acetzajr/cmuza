#include "acetza/muza/wavers/waver.h"

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/basic.h"
#include "acetza/muza/wavers/enveloper.h"
#include "acetza/panic.h"

mz_waver_t mz_waver_default = {MZ_BASIC, &mz_basic_ref};

void mz_waver_build(mz_waver_t *waver, wv_type_t type, void *ptr) {
  waver->type = type;
  waver->waver = ptr;
}

void mz_waver_wave(mz_waver_t *waver, mz_wave_t *wave) {
  switch (waver->type) {
  case MZ_BASIC:
    mz_basic_wave(waver->waver, wave);
    return;
  case MZ_ENVELOPER:
    mz_enveloper_wave(waver->waver, wave);
    return;
  default:
    az_panic(1, "waver type with code '%d' not recognized", waver->type);
    return;
  }
}

mz_frequency_t mz_waver_frequency(mz_waver_t *waver) {
  switch (waver->type) {
  case MZ_BASIC:
    mz_basic_t *basic = waver->waver;
    return basic->frequency;
  case MZ_ENVELOPER:
  case MZ_HARMONIZER:
    return mz_waver_frequency(waver->waver);
  default:
    az_panic(1, "waver type with code '%d' not recognized", waver->type);
    return 0.0;
  }
}

void mz_waver_set_frequency(mz_waver_t *waver, mz_frequency_t frequency) {
  switch (waver->type) {
  case MZ_BASIC:
    mz_basic_t *basic = waver->waver;
    basic->frequency = frequency;
    return;
  case MZ_ENVELOPER:
  case MZ_HARMONIZER:
    mz_waver_set_frequency(waver->waver, frequency);
    return;
  default:
    az_panic(1, "waver type with code '%d' not recognized", waver->type);
  }
}
