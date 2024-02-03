//
// Created by paradisus on 24-1-29.
//

#ifndef SHADER_H
#define SHADER_H

#include "glad/include/glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <format>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    Shader(const char *vertex_path, const char *fragment_path);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 mat) const;
};

inline Shader::Shader(const char* vertex_path, const char* fragment_path) {
    std::string vertex_code;
    std::string fragment_code;
    std::ifstream v_file, f_file;
    v_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    v_file.open(vertex_path);
    f_file.open(fragment_path);
    std::stringstream v_stream, f_stream;

    v_stream << v_file.rdbuf();
    f_stream << f_file.rdbuf();

    v_file.close();
    f_file.close();

    vertex_code = v_stream.str();
    fragment_code = f_stream.str();

    const char *v_shader = vertex_code.c_str();
    const char *f_shader = fragment_code.c_str();

    unsigned int vertex, fragment;
    int success;
    char info[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_shader, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, nullptr, info);
        std::cerr<<std::format("ERR! Vertex shader compilation failed\n{0}", info);
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_shader, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, nullptr, info);
        std::cerr<<std::format("ERR! Fragment shader compilation failed\n{0}", info);
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, info);
        std::cerr<<std::format("ERR! Linking failed\n{0}", info);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

inline void Shader::use() {
    glUseProgram(ID);
}

inline void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

inline void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

inline void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

inline void Shader::setMat4(const std::string &name, glm::mat4 mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}


#endif //SHADER_H
