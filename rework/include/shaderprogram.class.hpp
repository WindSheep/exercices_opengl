#ifndef  SHADERPROGRAM_CLASS_HPP
# define SHADERPROGRAM_CLASS_HPP

# include "opengl.hpp"
# include <string>
# include <vector>

// loadShaders(const char* vertex_fpath, const char* fragment_fpath)
class ShaderProgram {
public:
    typedef std::vector<ShaderProgram*> program_holder;

    /* CTOR */         ShaderProgram(const std::string& vertex_path,
                                     const std::string& fragment_path);
    virtual /* DTOR */ ~ShaderProgram(void);

    /* DELETED {{{ */
    /* CTOR */         ShaderProgram(void) = delete;
    /* CTOR */         ShaderProgram(const ShaderProgram& src) = delete;
    ShaderProgram&     operator=(const ShaderProgram& src) = delete;
    /* DELETED }}} */

    void               use(void);
    // void               modifyMVP(const glm::mat4& mvp);

    /* GETTERS && SETTERS {{{ */
    GLuint             getId(void) const;
    void               getId(GLuint& id) const;

    static const std::string& s_getVertexShaderName(void);
    static const std::string& s_getFragmentShaderName(void);
    /* GETTERS && SETTERS }}} */

private:
    GLuint                               _id;

    static ShaderProgram::program_holder _program_list;
};

#endif
