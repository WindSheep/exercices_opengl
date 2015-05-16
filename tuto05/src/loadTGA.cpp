#include "openGL.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

/* HPP */
# include <cstdint>

/**
 * TGA file :
 * - header
 * - meta data (image id)
 * - colormap
 * - image data
 * - footer (TGA v2.0+)
 */
# pragma pack(1)
struct Tgaheader
{
    /* @goto: http://nehe.gamedev.net/tutorial/loading_compressed_and_uncompressed_tga%27s/22001/ */
    /* @goto: http://en.wikipedia.org/wiki/Truevision_TGA */
    /* @goto: http://www.fileformat.info/format/tga/egff.htm */
    /* @note: size = 18 */
    typedef uint16_t word;
    typedef uint8_t  byte;

    enum class eImageType : byte
    {
        /* @note: unencoded */
        // NONE = 0,
        // COLORMAPPED = 1,
        TRUECOLOR = 2,
        // MONOCHROME = 3,
        /* @note: encoded */
        // COLORMAPPED_COMPRESSED = 9,
        TRUECOLOR_COMPRESSED = 10,
        // MONOCHROMED_COMPRESSED = 11,
    };

    /* @note: no magic number */
    byte       metadata_len;   /* @note: known as image_id */
    byte       color_map_type; /* @note: = (bool)0|1 (include plalette) */
    eImageType image_type;
    /* @note: ColorMapSpecification */
    word       cmap_start_off;
    word       cmap_len;
    byte       cmap_bit_pp;    /* @note: 15|16|24|32 */
    /* @note: ImageSpecification */
    word       img_x_off;
    word       img_y_off;
    word       img_width;
    word       img_height;
    byte       img_bit_pp;
    byte       img_descriptor; /* @note: bit 0-3[n_attr_pp] 4-5[origin_coord] */
};

union uTgaheader
{
    typedef uint8_t   byte;

    byte              data[18];
    Tgaheader         info;
};
# pragma pack()
/* HPP */

static bool _loadUncompressedTGA(FILE* file, const std::string& path,
                                 const uTgaheader& header,
                                 unsigned char* img_data) {
    GLuint img_byte_pp = header.info.img_bit_pp / 8;
    GLuint img_size = img_byte_pp * header.info.img_width * header.info.img_height;

    if (std::fread(img_data, 1, img_size, file) != img_size) {
        std::cerr << "Incorrect TGA file (image size) : " << path << std::endl;
        return false;
    }
    for (GLuint i = 0; i < img_size; i += img_byte_pp) {
        /* @note: swap BGR to RGB (xor instead of temp variable = speedup) */
        img_data[i] ^= img_data[i + 2];
        img_data[i + 2] ^= img_data[i];
        img_data[i] ^= img_data[i + 2];
    }
    return true;
}

/* @todo: _loadCompressedTGA to be tested */
static bool _loadCompressedTGA(FILE* file, const std::string& path,
                               const uTgaheader& header,
                               unsigned char* img_data) {
    GLuint img_byte_pp = header.info.img_bit_pp / 8;
    GLuint img_size = img_byte_pp * header.info.img_width * header.info.img_height;

    GLuint pixel_max = header.info.img_height * header.info.img_width;
    GLuint i_pixel = 0;
    GLuint i_byte  = 0;
    GLubyte* colorbuffer = new GLubyte[img_byte_pp];

    do {
        GLubyte chunkheader = 0;
        if (std::fread(&chunkheader, sizeof(GLubyte), 1, file) != 1)
            return false;
        if (chunkheader < 128)
        {
            /* @note: 'raw' chunck */
            ++(chunkheader);
            for (short ih = 0; ih < chunkheader; ++(ih)) {
                if (std::fread(colorbuffer, 1, img_byte_pp, file) != img_byte_pp)
                    return false;
                /* @note: write BGR to RGB */
                img_data[i_byte] = colorbuffer[2];
                img_data[i_byte + 1] = colorbuffer[1];
                img_data[i_byte + 2] = colorbuffer[0];
                /* note: write Alpha byte (32bit_pp image) */
                if (img_byte_pp == 4)
                    img_data[i_byte + 3] = colorbuffer[3];
                i_byte += img_byte_pp;
                ++(i_pixel);
            }
        }
        else
        {
            /* @note: 'RLE' header */
            chunkheader -= 127; /*@note get rid of the id bit */
            if (std::fread(colorbuffer, 1, img_byte_pp, file) != img_byte_pp)
                return false;
            for (short ih = 0; ih < chunkheader; ++(ih)) {
                /* @note: write BGR to RGB */
                img_data[i_byte] = colorbuffer[2];
                img_data[i_byte + 1] = colorbuffer[1];
                img_data[i_byte + 2] = colorbuffer[0];
                /* note: write Alpha byte (32bit_pp image) */
                if (img_byte_pp == 4)
                    img_data[i_byte + 3] = colorbuffer[3];
                i_byte += img_byte_pp;
                ++(i_pixel);
            }
        }
    } while (i_pixel < pixel_max);

    return true;
}

GLuint loadTGA(const std::string& path)
{
    typedef Tgaheader _Header;
    GLuint         texture_id;
    unsigned char* img_data;
    uTgaheader     header;
    FILE*          file = std::fopen(path.c_str(), "rb");

    GLuint         type;
    bool           (*fct)(FILE* file, const std::string& path, const uTgaheader& header, unsigned char* data);

    if (file == NULL) {
        std::cerr << "Image could not be opened : " << path << std::endl;
        return 0;
    }

    if (std::fread(&(header.info), sizeof(_Header), 1, file) != 1) {
        std::cerr << "Incorrect TGA file (headersize) : " << path << std::endl;
        return 0;
    }
    if (header.info.img_width <= 0 || header.info.img_height <= 0) {
        std::cerr << "Incorrect TGA file (image size) : " << path << std::endl;
        return 0;
    }
    if (header.info.image_type == _Header::eImageType::TRUECOLOR)
        fct = &_loadUncompressedTGA;
    else if (header.info.image_type == _Header::eImageType::TRUECOLOR_COMPRESSED)
        fct = &_loadCompressedTGA;
    else {
        std::cerr << "Incorrect TGA file (image type) : " << path << std::endl;
        return 0;
    }

    if (header.info.img_bit_pp == 24)
        type = GL_RGB;
    else if (header.info.img_bit_pp == 32)
        type = GL_RGBA;
    else {
        std::cerr << "Incorrect TGA file (bitperpixel) : " << path << std::endl;
        return 0;
    }
    /* @note: assume we have no image id/colormap, no footer either */

    GLuint img_byte_pp = header.info.img_bit_pp / 8;
    GLuint img_size = img_byte_pp * header.info.img_width * header.info.img_height;

    img_data = new GLubyte[img_size];
    if (! (*fct)(file, path, header, img_data)) {
        std::fclose(file);
        delete[] img_data;
        return 0;
    }
    std::fclose(file);

    glGenTextures(1, &(texture_id));
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexImage2D(GL_TEXTURE_2D, 0, type,
                 header.info.img_width, header.info.img_height,
                 0, GL_BGR, GL_UNSIGNED_BYTE, img_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete[] img_data;
    return texture_id;
}
