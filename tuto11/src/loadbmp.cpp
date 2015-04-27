#include "opengl.hpp"
#include "bmp.hpp"
#include <iostream>

GLuint loadBMP(const std::string& path) {
    unsigned char* data;
    uBmpheader     header;
    GLuint         texture_id;
    FILE*          file = std::fopen(path.c_str(),"rb");

    if (!file) {
        std::cerr << "Image could not be opened : " << path << std::endl;
        return 0;
    }
    if (std::fread(header.data, 1, 54, file) != 54) {
        std::cerr << "Incorrect BMP file (headersize) : " << path << std::endl;
        return 0;
    }
    if (header.info.magic[0] != 'B' || header.info.magic[1] != 'M') {
        std::cerr << "Incorrect BMP file (magicnumber) : " << path << std::endl;
        return 0;
    }

    if (header.info.img_size == 0) {
        header.info.img_size =
            header.info.img_width * header.info.img_height * 3;
    }

    data = new unsigned char[header.info.img_size]; {
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
    }
    std::fclose(file);

    glGenTextures(1, &(texture_id));
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 header.info.img_width, header.info.img_height,
                 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    delete[] data;
    return texture_id;
}
