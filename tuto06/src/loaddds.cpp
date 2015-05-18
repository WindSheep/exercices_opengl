#include "opengl.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

/* @todo: optimize this with union aswell */
GLuint loadDDS(const std::string& path) {
    unsigned char header[124];
    FILE*         fp;

    /* try to open the file */
    fp = std::fopen(path.c_str(), "rb");
    if (fp == NULL) {
        std::cout << path << "could not be opened." << std::endl;
        return 0;
    }
    /* verify the type of file */
    char filecode[4];
    std::fread(filecode, 1, 4, fp);
    if (std::strncmp(filecode, "DDS ", 4) != 0) {
        std::fclose(fp);
        return 0;
    }
    /* get the surface desc */
    std::fread(&header, 124, 1, fp);

    unsigned int height      = *(unsigned int*)&(header[8]);
    unsigned int width	   = *(unsigned int*)&(header[12]);
    unsigned int linearSize  = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);

    unsigned char* buffer;
    unsigned int   bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)std::malloc(bufsize * sizeof(unsigned char));
    std::fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    std::fclose(fp);

    unsigned int format;
    switch (fourCC) {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        std::free(buffer);
        return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++(level)) {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);
        offset += size;
        width /= 2;
        height /= 2;
        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if (width < 1) { width = 1; }
        if (height < 1) { height = 1; }
    }

    free(buffer);
    return textureID;
}
