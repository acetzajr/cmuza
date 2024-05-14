#include "acetza/muza/wave.h"

#include "acetza/types.h"

u64_t mz_time_to_frame(f64_t time, u64_t frame_rate) {
  return (u64_t)(time * ((f64_t)frame_rate));
}

f64_t mz_frame_to_time(u64_t frame, u64_t frame_rate) {
  return ((f64_t)frame) / ((f64_t)frame_rate);
}
