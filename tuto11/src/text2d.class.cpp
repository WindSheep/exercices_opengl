#include "text2d.class.hpp"
#include "texture.class.hpp"
#include "shaderprogram.class.hpp"
#include <iostream> /* @todo: to be removed */

ShaderProgram* Text2D::s_program = NULL;
Texture*       Text2D::s_texture_normal = NULL;
Texture*       Text2D::s_texture_highlight = NULL;

static void _genText2DBuffers(const std::string& text, int y, int x, int size,
                              unsigned int& n_tri,
                              GLuint& vbuffer,
                              GLuint& uvbuffer) {
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UVs;

    if (y <= 600) {
        y = 600 - y;
    }
    for (unsigned int i = 0 ; i < text.length(); ++(i)) {
        glm::vec2 vertex_up_left    = glm::vec2(x + i * size, y + size);
        glm::vec2 vertex_up_right   = glm::vec2(x + i * size + size, y + size);
        glm::vec2 vertex_down_right = glm::vec2(x + i * size + size, y);
        glm::vec2 vertex_down_left  = glm::vec2(x + i * size, y);

        // 1st triangle
        vertices.push_back(vertex_up_left);
        vertices.push_back(vertex_down_left);
        vertices.push_back(vertex_up_right);
        // 2nd triangle
        vertices.push_back(vertex_down_right);
        vertices.push_back(vertex_up_right);
        vertices.push_back(vertex_down_left);

        char character = text[i];
        float uv_x = (character % 16) / 16.0f;
        float uv_y = (character / 16) / 16.0f;

        glm::vec2 uv_up_left    = glm::vec2(uv_x, uv_y);
        glm::vec2 uv_up_right   = glm::vec2(uv_x + 1 / 16.0f, uv_y);
        glm::vec2 uv_down_right = glm::vec2(uv_x + 1 / 16.0f, (uv_y + 1 / 16.0f));
        glm::vec2 uv_down_left  = glm::vec2(uv_x, (uv_y + 1 / 16.0f));

        // 1st triagle
        UVs.push_back(uv_up_left);
        UVs.push_back(uv_down_left);
        UVs.push_back(uv_up_right);
        // 2nd triangle
        UVs.push_back(uv_down_right);
        UVs.push_back(uv_up_right);
        UVs.push_back(uv_down_left);

        n_tri += 2;
    }
    glGenBuffers(1, &(vbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &(vertices[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &(uvbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &(UVs[0]), GL_STATIC_DRAW);
}

/* CTOR */ Text2D::Text2D(const std::string& str,
                          unsigned int y, unsigned int x,
                          unsigned int size, bool highlight) :
    _n_tri(0), _vbuffer(0), _uvbuffer(0), _highlight(highlight) {
    _genText2DBuffers(str, y, x, size, this->_n_tri,
                      this->_vbuffer, this->_uvbuffer);
}

/* DTOR */ Text2D::~Text2D(void) {
    glDeleteBuffers(1, &(this->_vbuffer));
    glDeleteBuffers(1, &(this->_uvbuffer));
}

void Text2D::drawPart(void) {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbuffer);
    glVertexAttribPointer(
                          0,        // layout
                          2,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0,        // stride
                          (void*)0  // array_buffer offset
                          );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->_uvbuffer);
    glVertexAttribPointer(
                          1,        // layout
                          2,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized
                          0,        // stride
                          (void*)0  // array buffer offset
                          );

    Texture* font = this->_highlight ?
        Text2D::s_texture_highlight : Text2D::s_texture_normal;
    font->load(*(this->_program));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Text2D::draw(void) {
    if (Text2D::s_isInit() || Text2D::s_init()) {
        this->_program = Text2D::s_program;
        this->_program->use();

        this->drawPart();
        glDrawArrays(GL_TRIANGLES, 0, this->_n_tri * 3);
        glDisable(GL_BLEND);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }
}

/* GETTERS && SETTERS {{{ */
void Text2D::setHighlight(bool highlight) {
    this->_highlight = highlight;
}

bool Text2D::getHighlight(void) const {
    return this->_highlight;
}

void Text2D::getHighlight(bool& highlight) const {
    highlight = this->_highlight;
}

bool Text2D::s_init(void) {
    if (!Text2D::s_isInit()) {
        Text2D::s_program = new ShaderProgram("shaders/text2d/vertex.gl", "shaders/text2d/fragment.gl");
        Text2D::s_texture_normal = new Texture("fonts/Holstein.DDS");
        Text2D::s_texture_highlight = new Texture("fonts/Arial.bmp");
    }
    return true;
}

void Text2D::s_deInit(void) {
    delete Text2D::s_texture_normal; Text2D::s_texture_normal = NULL;
    delete Text2D::s_texture_highlight; Text2D::s_texture_highlight = NULL;
    delete Text2D::s_program; Text2D::s_program = NULL;
}

bool Text2D::s_isInit(void) {
    return Text2D::s_program != NULL &&
        Text2D::s_texture_normal != NULL &&
        Text2D::s_texture_highlight != NULL;
}
/* GETTERS && SETTERS }}} */
