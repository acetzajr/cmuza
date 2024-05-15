#pragma once

#include "acetza/types.h"

typedef u8_t mz_bool_t;
typedef f64_t mz_sample_t;
typedef f64_t mz_part_t;
typedef f64_t mz_amplitude_t;
typedef f64_t mz_frequency_t;
typedef f64_t mz_duration_t;
typedef f64_t mz_time_t;
typedef f64_t mz_attack_t;
typedef f64_t mz_hold_t;
typedef f64_t mz_decay_t;
typedef f64_t mz_sustain_t;
typedef f64_t mz_release_t;
typedef u64_t mz_channels_t;
typedef u64_t mz_frame_rate_t;
typedef u64_t mz_frames_t;
typedef u64_t mz_index_t;
typedef u64_t mz_size_t;
typedef u64_t mz_count_t;
typedef u64_t mz_depth_t;
typedef mz_sample_t (*mz_primitive_t)(mz_part_t part);
typedef mz_amplitude_t (*mz_transformer_t)(mz_part_t part);
typedef mz_index_t (*mz_numberer_t)(mz_index_t index);
