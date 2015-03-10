#include "openGL.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

static GLuint compileShader(const std::string& path, const GLenum type)
{
  // Create the shaders
  GLuint id     = glCreateShader(type);
  GLint  result = GL_FALSE;

  if (id == 0) {
    return 0;
  }
  // Read the Shader code from the file
  std::string code;
  std::ifstream ss(path, std::ios::in);
  if (ss.is_open()) {
    std::string line = "";
    while (getline(ss, line)) {
      code += line + "\n";
    }
    ss.close();
  }

  // Compile
  std::cout << "Compiling shader : " << path << std::endl;
  const char* source = code.c_str();
  glShaderSource(id, 1, &(source), NULL);
  glCompileShader(id);

  // Check
  int    infolog_len;
  glGetShaderiv(id, GL_COMPILE_STATUS, &(result));
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &(infolog_len));
  GLchar errmsg[infolog_len];
  glGetShaderInfoLog(id, infolog_len, NULL, errmsg);
  std::cout << errmsg << std::endl;

  if (result == GL_FALSE) {
    glDeleteShader(id);
    return 0;
  }
  return id;
}

static GLuint compileProgram(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
  GLint  result = GL_FALSE;
  GLuint program_id;

  // Link the program
  std::cout << "Linking program" << std::endl;
  program_id = glCreateProgram();
  glAttachShader(program_id, vertex_shader_id);
  glAttachShader(program_id, fragment_shader_id);
  glLinkProgram(program_id);

  // Check the program
  int    infolog_len;
  glGetProgramiv(program_id, GL_LINK_STATUS, &(result));
  glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &(infolog_len));
  GLchar errmsg[infolog_len];

  glGetProgramInfoLog(program_id, infolog_len, NULL, errmsg);
  std::cout << errmsg << std::endl;

  if (result == GL_FALSE) {
    glDeleteProgram(program_id);
    return 0;
  }

  return program_id;
}

GLuint        loadShaders(const std::string& vertex_fpath, const std::string& fragment_fpath)
{
  GLuint vertex_shader_id;
  GLuint fragment_shader_id;
  GLuint program_id;

  vertex_shader_id = compileShader(vertex_fpath, GL_VERTEX_SHADER);
  fragment_shader_id = compileShader(fragment_fpath, GL_FRAGMENT_SHADER);
  program_id = compileProgram(vertex_shader_id, fragment_shader_id);
  glDeleteShader(vertex_shader_id);
  glDeleteShader(fragment_shader_id);
  return program_id;
}
