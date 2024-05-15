#include "acetza/muza/wave.h"
#include "acetza/panic.h"
#include "acetza/types.h"

#include <sndfile-64.h>
#include <stddef.h>

void mz_wave_save(mz_wave_t *wave, const char *path) {
  SF_INFO info;
  info.samplerate = (int)wave->frame_rate;
  info.channels = (int)wave->channels;
  info.format = SF_FORMAT_WAV | SF_FORMAT_DOUBLE;
  SNDFILE *file = sf_open(path, SFM_WRITE, &info);
  if (file == NULL) {
    az_panic(1, "file %s could not be opened", path);
  }
  u64_t written =
      sf_writef_double(file, wave->samples, (sf_count_t)wave->frames);
  if (written != wave->frames) {
    az_panic(1, "%ld frames written but %ld requested", written, wave->frames);
  }
  sf_close(file);
}
