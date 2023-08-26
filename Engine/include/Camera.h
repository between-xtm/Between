#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>

enum class CameraMovement
{
    FORWARD = 0,
    BACKWORD,
    LEFT,
    RIGHT,
};

class Camera
{
public:
    Camera();
    Camera(glm::vec3 position, glm::vec3 up, float yaw = -90.0f, float pitch = 0.0f);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    virtual void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

    glm::mat4 getViewMatrix() { return glm::lookAt(mPosition, mPosition + mFront, mUp); }

    void setPosition(glm::vec3 Position) { mPosition = Position; }
    glm::vec3 getPosition() { return mPosition; }
    void setFront(glm::vec3 Point) { mFront = Point; }
    glm::vec3 getFront() { return mFront; }
    void setUp(glm::vec3 Up) { mUp = Up; }
    glm::vec3 getUp() { return mUp; }
    void setRight(glm::vec3 Right) { mRight = Right; }
    glm::vec3 getRight() { return mRight; }
    void getWorldUp(glm::vec3 WorldUp) { mWorldUp = WorldUp; }
    glm::vec3 setWorldUp() { return mWorldUp; }
    void setYaw(float Yaw) { mYaw = Yaw; }
    float getYaw() { return mYaw; }
    void setRaw(float Raw) { mRaw = Raw; }
    float getRaw() { return mRaw; }
    void setPitch(float Pitch) { mPitch = Pitch; }
    float getPitch() { return mPitch; }
    void setMovementSpeed(float MovementSpeed) { mMovementSpeed = MovementSpeed; }
    float getMovementSpeed() { return mMovementSpeed; }
    void setMouseSensitivity(float MouseSinitivity) { mMouseSensitivity = MouseSinitivity; }
    float getMouseSensitivity() { return mMouseSensitivity; }
    void setZoom(float Zoom) { mZoom = Zoom; }
    float getZoom() { return mZoom; }

private:
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;

    float mYaw = -90.0f;
    float mRaw = 0.0f;
    float mPitch = 0.0f;

    float mMovementSpeed = 1.8f;
    float mMouseSensitivity = 0.1f;
    float mZoom = 45.0f;

    void updateCameraVectors();
};

class CameraInstance
{
private:
    static CameraInstance* mInstance;
    Camera* mCamera = nullptr;
    // 禁止复制 禁止构造
    CameraInstance();
    CameraInstance& operator=(const CameraInstance&);

    unsigned int uboCameraMatrices;

public:
    ~CameraInstance();

    static void DestoryCamera();

    static CameraInstance* GetCamera();


    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    virtual void ProcessKeyboard(CameraMovement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);


    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return mCamera->getViewMatrix();
    }

    glm::vec3 GetPosition()
    {
        return mCamera->getPosition();
    }

    void SetMovementSpeed(float movespeed)
    {
        mCamera->setMovementSpeed(movespeed);
    }

    glm::mat4 getPerspective()
    {
        glm::mat4 p = glm::perspective(mCamera->getZoom(), static_cast<float>(800) / static_cast<float>(600), 0.1f,
                                       10000.0f);
        return p;
    }

    void UpdateUniform();
};
