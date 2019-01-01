#include "Shader.hpp"

#include <GL/glew.h>

Shader::Shader(const char* vertex_source, const char* fragment_source)
    : m_program_id(0)
{
    auto vertex_shader_id = create_shader(GL_VERTEX_SHADER, vertex_source);
    auto fragment_shader_id = create_shader(GL_FRAGMENT_SHADER, fragment_source);

    m_program_id = glCreateProgram();
    glAttachShader(m_program_id, vertex_shader_id);
    glAttachShader(m_program_id, fragment_shader_id);
    glLinkProgram(m_program_id);

    check_status(GL_LINK_STATUS, m_program_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}

Shader::~Shader()
{
    glDeleteProgram(m_program_id);
}

void Shader::use()
{
    glUseProgram(m_program_id);
}

bool Shader::has_uniform(const char* name)
{
    return -1 != get_uniform_location(name);
}

void Shader::set_bool(const char* name, bool value)
{
    glProgramUniform1i(m_program_id, get_uniform_location(name), (int)value);
}

void Shader::set_float(const char* name, float value)
{
    glProgramUniform1f(m_program_id, get_uniform_location(name), value);
}

void Shader::set_int(const char* name, int value)
{
    glProgramUniform1i(m_program_id, get_uniform_location(name), value);
}

void Shader::set_vec2(const char* name, const glm::vec2& value)
{
    glProgramUniform2f(m_program_id, get_uniform_location(name), value.x, value.y);
}

void Shader::set_vec3(const char* name, const glm::vec3& value)
{
    glProgramUniform3f(m_program_id, get_uniform_location(name), value.x, value.y, value.z);
}

void Shader::set_vec4(const char* name, const glm::vec4& value)
{
    glProgramUniform4f(m_program_id, get_uniform_location(name), value.x, value.y, value.z, value.w);
}

void Shader::set_mat2(const char* name, const glm::mat2x2& value)
{
    glProgramUniformMatrix2fv(m_program_id, get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::set_mat3(const char* name, const glm::mat3x3& value)
{
    glProgramUniformMatrix3fv(m_program_id, get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::set_mat4(const char* name, const glm::mat4x4& value)
{
    glProgramUniformMatrix4fv(m_program_id, get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

inline GLint Shader::get_uniform_location(const char* name)
{
    return glGetUniformLocation(m_program_id, name);
}

GLuint Shader::create_shader(const int type, const char* source) const
{
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    check_status(GL_COMPILE_STATUS, id);

    return id;
}

#include <cstdio>
void Shader::check_status(const int type, unsigned int id) const
{
    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512] = { 0 };
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        // TODO: add logger message
        printf("%s\n", infoLog);
    }
}
