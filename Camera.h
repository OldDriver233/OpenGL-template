//
// Created by paradisus on 24-2-3.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <concepts>

enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    float yaw;
    float pitch;

    float movement_speed;
    float mouse_sensitivity;
    float zoom;

    Camera(glm::vec3 position, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f):
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    movement_speed(2.5f),
    mouse_sensitivity(0.1f),
    zoom(45.0f) {
        this->position = position;
        this->world_up = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->_update_vectors();
    }

    [[nodiscard]]
    glm::mat4 get_view() const;

    void process_keyboard(CameraMovement, float);

    void process_mouse(float, float, GLboolean);

    void process_scroll(float);

private:
    void _update_vectors();
};



#endif //CAMERA_H
