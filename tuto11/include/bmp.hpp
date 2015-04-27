#ifndef  BMP_HPP
# define BMP_HPP

#include <cstdint>

# pragma pack(1)
struct Bmpheader_windows {
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

union uBmpheader {
    unsigned char     data[54];
    Bmpheader_windows info;
};
# pragma pack()

#endif
