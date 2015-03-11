#include "openGL.hpp"
#include <string>

// GLuint loadTGA(const std::string& path)
// {
//   GLuint textureID;

//   glGenTextures(1, &textureID);
//   glBindTexture(GL_TEXTURE_2D, textureID);
//   glfwLoadTexture2D(path.c_str(), 0); /* @note: wtf i dont have this function */

//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//   glGenerateMipmap(GL_TEXTURE_2D);

//   return textureID;
// }
