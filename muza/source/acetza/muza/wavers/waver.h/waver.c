#include "acetza/muza/wavers/waver.h"

#include "acetza/muza/wave.h"
#include "acetza/muza/wavers/basic.h"
#include "acetza/muza/wavers/enveloper.h"
#include "acetza/panic.h"

mz_waver_t mz_waver_default = {MZ_BASIC, &mz_basic_default};

void mz_waver_build(mz_waver_t *waver, wv_type_t type, void *ptr) {
  waver->type = type;
  waver->ptr = ptr;
}

void mz_waver_copy(mz_waver_t *waver, mz_waver_t *other) {
  mz_waver_build(waver, other->type, other->ptr);
}

void mz_waver_wave(mz_waver_t *waver, mz_wave_t *wave) {
  switch (waver->type) {
  case MZ_BASIC:
    mz_basic_wave(waver->ptr, wave);
    return;
  case MZ_ENVELOPER:
    mz_enveloper_wave(waver->ptr, wave);
    return;
  default:
    az_panic(1, "waver type with code '%d' not recognized", waver->type);
    return;
  }
}
