#include "acetza/muza/wavers/waver.h"

#include "acetza/muza/types.h"
#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/basic.h"
#include "acetza/muza/wavers/enveloper.h"
#include "acetza/muza/wavers/harmonizer.h"
#include "acetza/panic.h"

void mz_waver_init(mz_waver_t *waver, wv_type_t type, void *ptr) {
  waver->type = type;
  waver->waver = ptr;
}

void mz_waver_wave(mz_waver_t *waver, mz_wave_t *wave) {
  switch (waver->type) {
  case MZ_WAVER:
    mz_waver_wave(waver->waver, wave);
    return;
  case MZ_BASIC:
    mz_basic_wave(waver->waver, wave);
    return;
  case MZ_ENVELOPER:
    mz_enveloper_wave(waver->waver, wave);
    return;
  case MZ_HARMONIZER:
    mz_harmonizer_wave(waver->waver, wave);
    return;
  default:
    az_panic(1, "waver type with code '%d' not recognized", waver->type);
    return;
  }
}

mz_frequency_t mz_waver_frequency(mz_waver_t *waver) {
  switch (waver->type) {
  case MZ_WAVER:
    return mz_waver_frequency(waver->waver);
  case MZ_BASIC:
    mz_basic_t *basic = waver->waver;
    return basic->frequency;
  case MZ_ENVELOPER:
    mz_enveloper_t *enveloper = waver->waver;
    return mz_waver_frequency(enveloper->wavers.waver);
  case MZ_HARMONIZER:
    mz_harmonizer_t *harmonizer = waver->waver;
    return mz_waver_frequency(harmonizer->wavers.fundamental);
  default:
    az_panic(1, "waver type with code '%d' not recognized", waver->type);
    return 0.0;
  }
}

void mz_waver_set_frequency(mz_waver_t *waver, mz_frequency_t frequency) {
  switch (waver->type) {
  case MZ_WAVER:
    mz_waver_set_frequency(waver->waver, frequency);
    return;
  case MZ_BASIC:
    mz_basic_t *basic = waver->waver;
    basic->frequency = frequency;
    return;
  case MZ_ENVELOPER:
    mz_enveloper_t *enveloper = waver->waver;
    mz_waver_set_frequency(enveloper->wavers.waver, frequency);
    return;
  case MZ_HARMONIZER:
    mz_harmonizer_t *harmonizer = waver->waver;
    mz_waver_set_frequency(harmonizer->wavers.fundamental, frequency);
    return;
  default:
    az_panic(1, "waver type with code '%d' not recognized", waver->type);
  }
}

void mz_waver_set_duration(mz_waver_t *waver, mz_duration_t duration) {
  switch (waver->type) {
  case MZ_WAVER:
    mz_waver_set_duration(waver->waver, duration);
    return;
  case MZ_BASIC:
    mz_basic_t *basic = waver->waver;
    basic->duration = duration;
    return;
  case MZ_ENVELOPER:
    mz_enveloper_t *enveloper = waver->waver;
    mz_waver_set_duration(enveloper->wavers.waver, duration);
    return;
  case MZ_HARMONIZER:
    mz_harmonizer_t *harmonizer = waver->waver;
    mz_waver_set_duration(harmonizer->wavers.fundamental, duration);
    mz_waver_set_duration(harmonizer->wavers.harmonic, duration);
    return;
  default:
    az_panic(1, "waver type with code '%d' not recognized", waver->type);
  }
}
