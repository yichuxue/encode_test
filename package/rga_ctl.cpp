#include <rga_ctl.h>
#include "im2d.h"

unsigned char* src_buffer = NULL;
unsigned char* rga_src_buffer = NULL;
// unsigned char* dst_buf = NULL;

// IM_STATUS 			STATUS;
// rga_buffer_t 		src;
// rga_buffer_t 		dst;
// im_rect         src_rect;
// im_rect         dst_rect;

// int im_resize(BufferInfo buffer_info, unsigned char* dst_buf) {
  

// 	int h_stride = buffer_info.h_stride;
// 	int v_stride = buffer_info.v_stride;
// 	int dst_width = buffer_info.dst_width;
// 	int dst_height = buffer_info.dst_height;

// 	// src_buffer = (unsigned char *)mpp_buffer_get_ptr(buffer_info.buffer);
// 	src_buffer = buffer_info.frame;

// 	memset(&src_rect, 0, sizeof(src_rect));
//   memset(&dst_rect, 0, sizeof(dst_rect));

// 	memset(&src, 0, sizeof(src));
//   memset(&dst, 0, sizeof(dst));

//   src = wrapbuffer_virtualaddr(src_buffer, h_stride, v_stride, buffer_info.src_format);
// 	dst = wrapbuffer_virtualaddr(dst_buf, dst_width, dst_height, buffer_info.dst_format);

//   int ret = imcheck(src, dst, src_rect, dst_rect);
// 	if (IM_STATUS_NOERROR != ret) {
// 		printf("Rga resize: %d, check error! %s\n", __LINE__, imStrError((IM_STATUS)ret));
// 		return -1;
// 	}

//   STATUS = imresize(src, dst);

// 	if (STATUS <= 0) {
// 		printf("Rga resize: resize error for status: %s\n", imStrError(STATUS));
// 		return -1;
// 	}
//   return 0;
// }

int fx_resize(RgaInfo buffer_info) {
  IM_STATUS 			STATUS;
	rga_buffer_t 		fx_resize_src;
	rga_buffer_t 		fx_resize_dst;
	im_rect         fx_resize_src_rect;
	im_rect         fx_resize_dst_rect;

	memset(&fx_resize_src_rect, 0, sizeof(fx_resize_src_rect));
  memset(&fx_resize_dst_rect, 0, sizeof(fx_resize_dst_rect));

	memset(&fx_resize_src, 0, sizeof(fx_resize_src));
  memset(&fx_resize_dst, 0, sizeof(fx_resize_dst));

  fx_resize_src = wrapbuffer_virtualaddr(buffer_info.src_data, buffer_info.src_width, buffer_info.src_height, RK_FORMAT_YCbCr_420_SP);
	fx_resize_dst = wrapbuffer_virtualaddr(buffer_info.dst_data, buffer_info.dst_width, buffer_info.dst_height, RK_FORMAT_YCbCr_420_SP);

  int ret = imcheck(fx_resize_src, fx_resize_dst, fx_resize_src_rect, fx_resize_dst_rect);
	if (IM_STATUS_NOERROR != ret) {
		printf("Rga resize: %d, check error! %s\n", __LINE__, imStrError((IM_STATUS)ret));
		return -1;
	}

  STATUS = imresize(fx_resize_src, fx_resize_dst);

	if (STATUS <= 0) {
		printf("Rga resize: resize error for status: %s\n", imStrError(STATUS));
		return -1;
	}

  return 0;
}

