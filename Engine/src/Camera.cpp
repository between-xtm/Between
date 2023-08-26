#include "Camera.h"

#include <algorithm>


Camera::Camera()
{
    updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
    mPosition = position;
    mUp = up;
    mYaw = yaw;
    mPitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
    mPosition = glm::vec3(posX, posY, posZ);
    mUp = glm::vec3(upX, upY, upZ);
    mYaw = yaw;
    mPitch = pitch;
    updateCameraVectors();
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = mMovementSpeed * deltaTime;
    switch (direction)
    {
    case CameraMovement::FORWARD:
    case CameraMovement::BACKWORD:
        mPosition += mFront * velocity;
    case CameraMovement::LEFT:
    case CameraMovement::RIGHT:
        mPosition += mRight * velocity;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;
    mYaw += xoffset;
    mPitch += yoffset;

    if (constrainPitch)
    {
        mPitch = fmax(fmin(mPitch, 89.0f), -89.0f);
    }
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    mZoom -= yoffset;
    mZoom = glm::clamp(mZoom, 1.0f, 45.0f);
}

void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    front.y = sin(glm::radians(mPitch));
    front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(front);
    // also re-calculate the Right and Up vector
    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    mUp = glm::normalize(glm::cross(mRight, mFront));
}

/* CameraInstance */

CameraInstance* CameraInstance::mInstance = nullptr;

CameraInstance::CameraInstance()
{
    mCamera = new Camera();

    // 创建共享uniform布局块的缓冲对象
    glGenBuffers(1, &uboCameraMatrices);

    glBindBuffer(GL_UNIFORM_BUFFER, uboCameraMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboCameraMatrices, 0, 2 * sizeof(glm::mat4));
    UpdateUniform();
}

CameraInstance::~CameraInstance()
{
    delete mCamera;
}

void CameraInstance::DestoryCamera()
{
    delete mInstance;
    mInstance = nullptr;
}

CameraInstance* CameraInstance::GetCamera()
{
    if (mInstance == nullptr)
    {
        mInstance = new CameraInstance();
    }
    return mInstance;
}

void CameraInstance::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    mCamera->ProcessKeyboard(direction, deltaTime);
}

void CameraInstance::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    mCamera->ProcessMouseMovement(xoffset, yoffset);
}

void CameraInstance::ProcessMouseScroll(float yoffset)
{
    mCamera->ProcessMouseScroll(yoffset);
}

void CameraInstance::UpdateUniform()
{
    glm::mat4 projection = glm::perspective(mCamera->getZoom(), static_cast<float>(800) / static_cast<float>(600), 0.1f,
                                            100000.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboCameraMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glm::mat4 view = mCamera->getViewMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, uboCameraMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
}
