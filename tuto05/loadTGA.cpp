#include "openGL.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

/* HPP */
/* @goto: http://nehe.gamedev.net/tutorial/loading_compressed_and_uncompressed_tga%27s/22001/ */
# pragma pack(1)
struct sTexture
{
    GLubyte* image_data; // Hold All The Color Values For The Image.
    GLuint   bit_pp;     // Hold The Number Of Bits Per Pixel.
    GLuint   width;      // The Width Of The Entire Image.
    GLuint   height;     // The Height Of The Entire Image.
    GLuint   texID;      // Texture ID For Use With glBindTexture.
    GLuint   type;       // Data Stored In * ImageData (GL_RGB Or GL_RGBA)
};

enum class eCompress : unsigned int
{
    NONE = 2,
    COMPRESSED = 0,
    UNCOMPRESSED = 1,
};

struct sTGAHeader /* @note : magic ? */
{
    GLubyte header[12]; // File Header To Determine File Type
};

struct sTGA
{
    GLubyte header[6];     // Holds The First 6 Useful Bytes Of The File
    GLuint  byte_pp;       /* @note: 3|4 */
    GLuint  image_size;    // Amount Of Memory Needed To Hold The Image
    GLuint  type;          // The Type Of Image, GL_RGB Or GL_RGBA
    GLuint  height;        // Height Of Image
    GLuint  width;         // Width Of Image
    GLuint  bit_pp;        // Number Of BITS Per Pixel (24 Or 32)
};
# pragma pack()
/* HPP */

sTGAHeader tgaheader;
sTGA       tga;

/* @todo: use union etc */
static bool loadUncompressedTGA(sTexture* texture, const std::string& path, FILE* file) {
    std::cout << "uncompressed TGA" << std::endl;
    /* DOWN: SAME CODE */
    if (std::fread(tga.header, sizeof(tga.header), 1, file) == 0) {
        std::cerr << "Incorrect TGA file (headersize (2)) : " << path << std::endl;
        return false;
    }
    texture->width  = tga.header[1] * 256 + tga.header[0]; // Calculate Height
    texture->height = tga.header[3] * 256 + tga.header[2]; // Calculate The Width
    texture->bit_pp = tga.header[4];                       // Calculate Bits Per Pixel
    tga.width = texture->width;                            // Copy Width Into Local Structure
    tga.height = texture->height;                          // Copy Height Into Local Structure
    tga.bit_pp = texture->bit_pp;                          // Copy Bpp Into Local Structure

    if (texture->width <= 0 || texture->height <= 0) {
        std::cerr << "Incorrect TGA file (image size number) : " << path << std::endl;
        return false;
    }
    if (texture->bit_pp == 24) {
        std::cerr << "TGA type GL_RGB" << std::endl;
        texture->type = GL_RGB;
    }
    else if (texture->bit_pp == 32) {
        std::cerr << "TGA type GL_RGBA" << std::endl;
        texture->type = GL_RGBA;
    }
    else {
        std::cerr << "Incorrect TGA file (bitperpixel) : " << path << std::endl;
        return false;
    }
    tga.byte_pp = tga.bit_pp / 8;
    tga.image_size = tga.byte_pp * tga.width * tga.height;

    texture->image_data = static_cast<GLubyte*>(std::malloc(tga.image_size));
    if (texture->image_data == NULL) {
        std::cerr << "malloc fail" << std::endl;
        return false;
    }
    /* UP : SAME CODE */

    if (std::fread(texture->image_data, 1, tga.image_size, file) != tga.image_size) {
        std::cerr << "Incorrect TGA file (image size (real)) : " << path << std::endl;
        return false;
    }

    for (GLuint i = 0; i < static_cast<GLuint>(tga.image_size); i += tga.byte_pp) {
        /* @note: swap BGR to RGB (xor instead of temp variable = speedup) */
        // texture->image_data[i] ^= texture->image_data[i + 2];
        // texture->image_data[i + 2] ^= texture->image_data[i];
        // texture->image_data[i] ^= texture->image_data[i + 2];

        // texture->image_data[i] ^= texture->image_data[i + 2] ^=
        //     texture->image_data[i] ^= texture->image_data[i + 2];
    }
    std::fclose(file);
    return true;
}

static bool loadCompressedTGA(sTexture* texture, const std::string& path, FILE* file) {
    std::cout << "compressed TGA" << std::endl;
    /* DOWN: SAME CODE */
    if (std::fread(tga.header, sizeof(tga.header), 1, file) == 0)
        return false;
    texture->width  = tga.header[1] * 256 + tga.header[0];
    texture->height = tga.header[3] * 256 + tga.header[2];
    texture->bit_pp = tga.header[4];
    tga.width = texture->width;
    tga.height = texture->height;
    tga.bit_pp = texture->bit_pp;
    if (texture->width <= 0 || texture->height <= 0)
        return false;
    if (texture->bit_pp == 24)
        texture->type = GL_RGB;
    else if (texture->bit_pp == 32)
        texture->type = GL_RGBA;
    else
        return false;

    tga.byte_pp = tga.bit_pp / 8;
    tga.image_size = tga.byte_pp * tga.width * tga.height;

    texture->image_data = static_cast<GLubyte*>(std::malloc(tga.image_size));
    if (texture->image_data == NULL)
        return false;
    /* UP : SAME CODE */

    GLuint pixelcount = tga.height * tga.width; // Number Of Pixels In The Image
    GLuint currentpixel = 0;            // Current Pixel We Are Reading From Data
    GLuint currentbyte  = 0;            // Current Byte We Are Writing Into Imagedata
    // Storage For 1 Pixel
    GLubyte* colorbuffer = static_cast<GLubyte*>(std::malloc(tga.byte_pp));

    do {
        GLubyte chunkheader = 0; // Variable To Store The Value Of The Id Chunk
        if (std::fread(&chunkheader, sizeof(GLubyte), 1, file) == 0) // Attempt To Read The Chunk's Header
            return false;
        if (chunkheader < 128) // If The Chunk Is A 'RAW' Chunk
        {
            ++(chunkheader); // Add 1 To The Value To Get Total Number Of Raw Pixels
            // Start Pixel Reading Loop
            for (short counter = 0; counter < chunkheader; ++(counter))
            {
                // Try To Read 1 Pixel
                if (std::fread(colorbuffer, 1, tga.byte_pp, file) != tga.byte_pp)
                    return false;
                /* @note: write BGR to RGB */
                texture->image_data[currentbyte] = colorbuffer[2];
                texture->image_data[currentbyte + 1] = colorbuffer[1];
                texture->image_data[currentbyte + 2] = colorbuffer[0];
                /* note: write Alpha byte (32bit_pp image) */
                if (tga.byte_pp == 4)
                    texture->image_data[currentbyte + 3] = colorbuffer[3];
                currentbyte += tga.byte_pp;
                ++(currentpixel);
            }
        }
        else // If It's An RLE Header
        {
            chunkheader -= 127; // Subtract 127 To Get Rid Of The ID Bit
            // Read The Next Pixel
            if (std::fread(colorbuffer, 1, tga.byte_pp, file) != tga.byte_pp)
                return false;

            // Start The Loop
            for (short counter = 0; counter < chunkheader; ++(counter))
            {
                /* @note: write BGR to RGB */
                texture->image_data[currentbyte] = colorbuffer[2];
                texture->image_data[currentbyte + 1] = colorbuffer[1];
                texture->image_data[currentbyte + 2] = colorbuffer[0];
                /* note: write Alpha byte (32bit_pp image) */
                if (tga.byte_pp == 4)
                    texture->image_data[currentbyte + 3] = colorbuffer[3];
                currentbyte += tga.byte_pp;
                ++(currentpixel);
            }
        }
    } while (currentpixel < pixelcount);

    std::fclose(file);
    return true;
}

GLuint loadTGA(const std::string& path)
{
    static GLubyte s_h_uncomp[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    static GLubyte s_h_comp[12] = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    FILE*      file;
    sTGAHeader tgaheader;
    sTGA       tga;

    sTexture*  texture_tmp;
    GLuint     texture_id;

    bool       ret;

    texture_tmp = new sTexture();
    file = std::fopen(path.c_str(), "rb");
    if (file == NULL) {
        std::cerr << "Image could not be opened : " << path << std::endl;
        return false;
    }

    if (std::fread(&tgaheader, sizeof(tgaheader), 1, file) == 0) {
        std::cerr << "Incorrect TGA file (headersize) : " << path << std::endl;
        return false;
    }

    if (std::memcmp(s_h_uncomp, &(tgaheader), sizeof(tgaheader)) == 0) {
        ret = loadUncompressedTGA(texture_tmp, path, file);
    }
    else if (std::memcmp(s_h_comp, &tgaheader, sizeof(tgaheader)) == 0) {
        ret = loadCompressedTGA(texture_tmp, path, file);
    }
    else {
        std::cerr << "Incorrect TGA file (magic number) : " << path << std::endl;
        return false;
    }

    std::cout << "ret = " << static_cast<int>(ret) << std::endl;

    glGenTextures(1, &(texture_id));
    glBindTexture(GL_TEXTURE_2D, texture_id);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, header.info.img_width, header.info.img_height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexImage2D(GL_TEXTURE_2D, 0, texture_tmp->type,
                 texture_tmp->width, texture_tmp->height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture_tmp->image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // delete texture_tmp;

    return texture_id;
}
