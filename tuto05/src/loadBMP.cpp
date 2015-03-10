#include "openGL.hpp"
#include <cstdint>
#include <iostream>

# pragma pack(1)
struct Bmpheader_windows
{
  /* @goto: http://en.wikipedia.org/wiki/BMP_file_format */
  typedef uint8_t       uint1;
  typedef uint16_t      uint2;
  typedef uint32_t      uint4;
  typedef uint64_t      uint8;

  typedef int8_t        int1;
  typedef int16_t       int2;
  typedef int32_t       int4;
  typedef int64_t       int8;
  typedef unsigned char uchar;

  /* @note: suppose little endian integers ? */
  uchar         magic[2];
  int4          file_size;
  char          reserveddata_00[0x02];
  char          reserveddata_01[0x02];
  int4          data_pos;

  /* @note: windows format */
  uint4         head_size;
  int4          img_width;
  int4          img_height;
  int2          n_planes;
  uint2         bpp;
  uint4         compression_method;
  uint4         img_size;
  int4          x_ppm;
  int4          y_pm;
  int4          n_colors;
  int4          n_icolors;
};

union uBmpheader
{
  unsigned char     data[54];
  Bmpheader_windows info;
};
# pragma pack()

GLuint loadBMP(const std::string& path)
{
  GLuint         bmp_id;
  unsigned char* data_start;
  unsigned char* data;
  uBmpheader     header;

  FILE * file = std::fopen(path.c_str(),"rb");
  if (!file) {
    std::cerr << "Image could not be opened : " << path << std::endl;
    return 0;
  }
  if (std::fread(header.data, 1, 54, file) != 54) {
    std::cerr << "Not a correct BMP file (header size) : " << path << std::endl;
    return 0;
  }
  if (header.info.magic[0] != 'B' || header.info.magic[1] != 'M') {
    std::cerr << "Not a correct BMP file (magic number) : " << path << std::endl;
    return 0;
  }

  if (header.info.img_size == 0) {
    header.info.img_size = header.info.img_width * header.info.img_height * 3;
  }

  data = new unsigned char[header.info.img_size];
  {
    unsigned char* data_ptr = data;
    for (size_t len = header.info.img_size; len > 1;) {
      size_t n = std::fread(data, 1, len, file);

      if (n < 1) {
        std::cerr << "Read failed : " << path << std::endl;
        std::fclose(file);
        return 0;
      }
      len -= n;
      data_ptr = &(data_ptr[n]);
    }
  } std::fclose(file);

  GLuint texture_id;
  glGenTextures(1, &(texture_id));
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, header.info.img_width, header.info.img_height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  delete[] data;
  return texture_id;
}
