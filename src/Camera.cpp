
#include <cmath>
#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

Camera::Camera() :
position(0.0f, 0.0f, 1.0f),
horizontalAngle(0.0f),
verticalAngle(0.0f),
fieldOfView(50.0f),
nearPlane(0.01f),
farPlane(100.0f),
viewportAspectRatio(16.0f/10.0f)
{
}

void Camera::Move(const glm::vec3& offset)
{
    position += offset;
}

void Camera::Rotate(float upAngle, float rightAngle)
{
    this->horizontalAngle += rightAngle;
    this->verticalAngle += upAngle;
    normalizeAngles();
}

void Camera::LookAt(const glm::vec3& position)
{
    assert(position != this->position);
    glm::vec3 direction = glm::normalize(position - this->position);
    this->verticalAngle = glm::radians(asinf(-direction.y));
    this->horizontalAngle = -glm::radians(atan2f(-direction.x, -direction.z));
    normalizeAngles();
}

glm::vec3 Camera::GetPosition() const
{
    return position;
}

float Camera::GetFieldOfView() const
{
    return fieldOfView;
}

float Camera::GetNearPlane() const
{
    return nearPlane;
}

float Camera::GetFarPlane() const
{
    return farPlane;
}

float Camera::GetAspectRatio() const
{
    return this->viewportAspectRatio;
}

void Camera::SetPosition(const glm::vec3& position)
{
    this->position = position;
}

void Camera::SetNearPlane(float nearPlane)
{
    assert(nearPlane > 0.0f);
    assert(farPlane > nearPlane);
    this->nearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
    assert(farPlane > nearPlane);
    this->farPlane = farPlane;
}

void Camera::SetAspectRatio(float viewportAspectRatio)
{
    assert(viewportAspectRatio > 0.0);
    this->viewportAspectRatio = viewportAspectRatio;
}

void Camera::SetFieldOfView(float fieldOfView)
{
    assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
    this->fieldOfView = fieldOfView;
}

glm::vec3 Camera::forward() const
{
    glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0,0,-0.1,1);
    return glm::vec3(forward);
}

glm::vec3 Camera::backward() const
{
    glm::vec4 backward = glm::inverse(orientation()) * glm::vec4(0,0,0.1,1);
    return glm::vec3(backward);
}

glm::vec3 Camera::right() const
{
    glm::vec4 right = glm::inverse(orientation()) * glm::vec4(0.1,0,0,1);
    return glm::vec3(right);
}

glm::vec3 Camera::left() const
{
    glm::vec4 left = glm::inverse(orientation()) * glm::vec4(-0.1,0,0,1);
    return glm::vec3(left);
}

glm::vec3 Camera::up() const
{
    glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0,0.1,0,1);
    return glm::vec3(up);
}

glm::vec3 Camera::down() const
{
    glm::vec4 down = glm::inverse(orientation()) * glm::vec4(0,-0.1,0,1);
    return glm::vec3(down);
}

glm::mat4 Camera::matrix() const
{
    return projection() * view();
}

glm::mat4 Camera::orientation() const
{
    glm::mat4 orientation;
    orientation = glm::rotate(orientation, glm::radians(this->verticalAngle), glm::vec3(1,0,0));
    orientation = glm::rotate(orientation, glm::radians(this->horizontalAngle), glm::vec3(0,1,0));
    return orientation;
}

glm::mat4 Camera::projection() const
{
    return glm::perspective(glm::radians(this->fieldOfView), this->viewportAspectRatio, this->nearPlane, this->farPlane);
}

glm::mat4 Camera::view() const
{
    return orientation() * glm::translate(glm::mat4(), -this->position);
}

void Camera::normalizeAngles()
{
    this->horizontalAngle = fmodf(this->horizontalAngle, 360.0f);
    //fmodf can return negative values, but this will make them all positive
    if(this->horizontalAngle < 0.0f)
        this->horizontalAngle += 360.0f;
    
    if(this->verticalAngle > MaxVerticalAngle)
        this->verticalAngle = MaxVerticalAngle;
    else if(this->verticalAngle < -MaxVerticalAngle)
        this->verticalAngle = -MaxVerticalAngle;
}