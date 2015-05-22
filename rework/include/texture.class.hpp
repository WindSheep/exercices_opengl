#ifndef  TEXTURE_CLASS_HPP
# define TEXTURE_CLASS_HPP

# include "opengl.hpp"
# include <string>

class ShaderProgram;

class Texture {
public:
  /* CTOR */         Texture(const std::string& path);
  virtual /* DTOR */ ~Texture(void);

    /* DELETED {{{ */
    /* CTOR */       Texture(void) = delete;
    /* CTOR */       Texture(const Texture& src) = delete;
    Texture&         operator=(const Texture& src) = delete;
    /* DELETED }}} */

    void             load(const ShaderProgram& program) const;

    /* GETTERS && SETTERS {{{ */
    GLuint           getId(void) const;
    void             getId(GLuint& id) const;
    /* GETTERS && SETTERS }}} */

private:
    GLuint           _id;
};

#endif
