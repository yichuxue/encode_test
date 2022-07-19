// extern "C" {
// #include "im2d.hpp"
// };

#include <stdio.h>
#include <string.h>

#include "mpp_log.h"
#include "mpp_mem.h"
#include "mpp_env.h"
#include "mpp_time.h"
#include "mpp_common.h"

#include "mpp_frame.h"
#include "mpp_buffer_impl.h"
#include "mpp_frame_impl.h"

// #include <opencv2/core/core.hpp>
// #include <opencv2/imgcodecs/imgcodecs.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/highgui/highgui.hpp>

// #include <codec.h>
#include "rga.h"
// typedef struct {
//   int width;
//   int height;
//   int h_stride;
//   int v_stride;
//   MppBuffer buffer;
//   int result;
// } BufferInfo;

typedef struct {
  char* src_data;
  char* dst_data;
  int frame_index;
  int init;
  int src_width;
  int src_height;
  int dst_width;
  int dst_height;
  int format;
  int src_format;
  int dst_format;
} RgaInfo;

// int im_resize(BufferInfo buffer_info, unsigned char* dst_buf);

int fx_resize(RgaInfo buffer_info);