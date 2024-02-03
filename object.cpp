//
// Created by paradisus on 24-2-1.
//

#include "object.h"

void Object::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
