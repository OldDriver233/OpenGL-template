//
// Created by paradisus on 24-2-3.
//

#include "Camera.h"

void Camera::_update_vectors() {
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(f);
    this->right = glm::normalize(glm::cross(front, world_up));
    this->up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::get_view() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::process_keyboard(CameraMovement dir, float delta_time) {
    const float vel = this->movement_speed * delta_time;
    switch (dir) {
        case CameraMovement::FORWARD:
            position += front * vel;
            break;
        case CameraMovement::BACKWARD:
            position -= front * vel;
            break;
        case CameraMovement::LEFT:
            position -= right * vel;
            break;
        case CameraMovement::RIGHT:
            position += right * vel;
            break;
    }
}

template<std::totally_ordered T>
inline T clamp(T val, T min, T max) {
    return val < min ? min : (val > max ? max : val);
}

void Camera::process_mouse(float x, float y, GLboolean constrain_pitch = true) {
    x *= this->mouse_sensitivity;
    y *= this->mouse_sensitivity;

    this->yaw += x;
    this->pitch += y;

    [[likely]]
    if(constrain_pitch) {
        this->pitch = clamp(this->pitch, -89.0f, 89.0f);
    }

    this->_update_vectors();
}

void Camera::process_scroll(float y) {
    this->zoom -= y;
    this->zoom = clamp(this->zoom, 1.0f, 45.0f);
}
