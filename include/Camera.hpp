
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    
    void Move(const glm::vec3& offset);
    void Rotate(float up, float right);
    void LookAt(const glm::vec3& point);
    
    glm::vec3 GetPosition() const;
    float GetNearPlane() const;
    float GetFarPlane() const;
    float GetAspectRatio() const;
    float GetFieldOfView() const;
    
    void SetPosition(const glm::vec3& position);
    void SetNearPlane(float nearPlane);
    void SetFarPlane(float farPlane);
    void SetAspectRatio(float viewportAspectRatio);
    void SetFieldOfView(float angle);
    
    // unit orientation vectors
    glm::vec3 forward() const;
    glm::vec3 backward() const;
    glm::vec3 right() const;
    glm::vec3 left() const;
    glm::vec3 up() const;
    glm::vec3 down() const;
    
    // camera matrices
    glm::mat4 matrix() const;
    glm::mat4 orientation() const;
    glm::mat4 projection() const;
    glm::mat4 view() const;
    
private:
    glm::vec3 position;
    float horizontalAngle;
    float verticalAngle;
    float fieldOfView;
    float nearPlane;
    float farPlane;
    float viewportAspectRatio;
    
    void normalizeAngles();
};

#endif
