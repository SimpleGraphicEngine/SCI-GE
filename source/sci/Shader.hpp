#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm/glm.hpp>

static const char* g_default_vertex_shader_source =
    "#version 330 core                                       \n"
    "layout (location = 0) in vec3 pos;                      \n"
    "uniform mat4 transform;                                 \n"
    "void main()                                             \n"
    "{                                                       \n"
    "    gl_Position = transform * vec4(pos, 1.0);           \n"
    "}                                                       \0";

static const char* g_default_fragment_shader_source =
    "#version 330 core                                 \n"
    "out vec4 FragColor;                               \n"
    "uniform vec4 color;                               \n"
    "void main()                                       \n"
    "{                                                 \n"
    "    FragColor = color;                            \n"
    "}                                                 \0";

class Shader final
{
public:
    Shader(const char* vertex_source, const char* fragment_source);
    ~Shader();

    void use();

    bool has_uniform(const char* name);
    void set_bool(const char* name, bool value);
    void set_float(const char* name, float value);
    void set_int(const char* name, int value);
    void set_vec2(const char* name, const glm::vec2& value);
    void set_vec3(const char* name, const glm::vec3& value);
    void set_vec4(const char* name, const glm::vec4& value);
    void set_mat2(const char* name, const glm::mat2x2& value);
    void set_mat3(const char* name, const glm::mat3x3& value);
    void set_mat4(const char* name, const glm::mat4x4& value);

protected:
    int get_uniform_location(const char* name);
    unsigned int create_shader(const int type, const char* source) const;
    void check_status(const int type, unsigned int id) const;

private:
    unsigned int m_program_id;
};

#endif // !SHADER_HPP