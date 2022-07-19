#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <fstream> 
#include <string.h>
#include <encode.h>
#include "mpp_time.h"

using namespace std;

void swapYUV_I420toNV12(unsigned char* i420bytes, unsigned char* nv12bytes, int width, int height)
{
    int nLenY = width * height;
    int nLenU = nLenY / 4;

    memcpy(nv12bytes, i420bytes, width * height);

    for (int i = 0; i < nLenU; i++)
    {
        nv12bytes[nLenY + 2 * i] = i420bytes[nLenY + i];                    // U
        nv12bytes[nLenY + 2 * i + 1] = i420bytes[nLenY + nLenU + i];        // V
    }
}

void BGR2YUV_nv12(cv::Mat src, cv::Mat &dst)
{
    int w_img = src.cols;
    int h_img = src.rows;
    dst = cv::Mat(h_img*1.5, w_img, CV_8UC1, cv::Scalar(0));
    cv::Mat src_YUV_I420(h_img*1.5, w_img, CV_8UC1, cv::Scalar(0));  //YUV_I420
    cvtColor(src, src_YUV_I420, cv::COLOR_BGR2YUV_I420);
    swapYUV_I420toNV12(src_YUV_I420.data, dst.data, w_img, h_img);
}

int main(int argc, char* argv[]) {
  string img_path = "/root/app/soft/mpp_control/1.jpg";
  string img_path1 = "/root/app/soft/mpp_control/t.png";
  cv::Mat img = cv::imread(img_path);
  cv::Mat img1 = cv::imread(img_path1);
  cv::Mat yuvImg;
  cv::Mat yuvImg1;
  // cv::cvtColor(img, yuvImg, cv::COLOR_BGR2YUV_YV12);
  BGR2YUV_nv12(img, yuvImg);
  BGR2YUV_nv12(img1, yuvImg1);
  printf("w: %d %d %d %d \n", img.cols, img.rows, img.channels(), img.cols*img.rows*3);
  
  char* pdst = (char*)malloc(1024*1024*8);
  int length = 0;
  int index = 0;
  whale::vision::MppEncoder mppenc;
  mppenc.MppEncdoerInit(img.cols, img.rows, 1, 3, 2);

  while (1) {
    msleep(50);
    index += 1;

    if (index % 2 == 0) {
      mppenc.encode(yuvImg.data, img.cols*img.rows*1.5, pdst, &length);
    } else {
      mppenc.encode(yuvImg1.data, img.cols*img.rows*1.5, pdst, &length);
    }

    string filepath = to_string(index) + ".jpg";
    FILE* fp = fopen(filepath.c_str(), "wb+");
    printf("length: %d \n", length);
    fwrite((const char*)pdst, 1, length, fp);
    fclose(fp);
    // mppenc.destory();
    // delete mppenc;
  }

  return 0;
}

