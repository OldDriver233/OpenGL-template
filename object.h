//
// Created by paradisus on 24-2-1.
//

#ifndef OBJECT_H
#define OBJECT_H
#include <glad/glad.h>

enum class Description {
    COORD3,
    COORD2,
    COORD3_COLOR3,
    COORD3_UV2,
};

class Object {
public:
    float* vertices;
    Description description;
    int* indices;
    unsigned int VAO, VBO, EBO;
    Object(float *vert, int vert_size, const Description desc, int *id, int id_size): vertices(vert), description(desc), indices(id) {
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);
        switch (desc) {
            case Description::COORD3:
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
                glEnableVertexAttribArray(0);
                break;
            case Description::COORD2:
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)nullptr);
                glEnableVertexAttribArray(0);
                break;
            case Description::COORD3_COLOR3:
                break;
            case Description::COORD3_UV2:
                break;
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void draw() const;
};



#endif //OBJECT_H
