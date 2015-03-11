#include "ShaderProgram.class.hpp"

GLuint                                 loadShaders(const std::string& vertex_path, const std::string& fragment_path);

//-/* CONSTRUCTORS / DESTRUCTORS */-//
/* CONSTRUCTOR */                      ShaderProgram::ShaderProgram(const std::string& vertex_path, const std::string& fragment_path) :
  _id(loadShaders(vertex_path, fragment_path))
{ }

/* DESTRUCTOR */                       ShaderProgram::~ShaderProgram(void)
{ glDeleteProgram(this->_id); }

//-/* FUNCTIONS */-//
void                                   ShaderProgram::use(void)
{ glUseProgram(this->_id); }

void                                   ShaderProgram::modifyMVP(const glm::mat4& mvp)
{
  GLuint matrix_id = glGetUniformLocation(this->_id, "MVP");
  glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]); /* @todo: &mvp[0][0] */
}

//-/* GETTERS / SETTERS */-//
GLuint                                 ShaderProgram::getId(void) const
{ return this->_id; }

void                                   ShaderProgram::getId(GLuint& id) const
{ id = this->_id; }

const std::string&                     ShaderProgram::s_getVertexShaderName(void)
{ static const std::string name = "vertex.gl"; return name; }

const std::string&                     ShaderProgram::s_getFragmentShaderName(void)
{ static const std::string name = "fragment.gl"; return name; }
