#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <reactphysics3d/reactphysics3d.h>

#include "../glfw/glfwWindow.hpp"


class DebugRenderer
{
public:

    DebugRenderer(OpenGLGame::GlfwWindow* window);
    ~DebugRenderer();

    DebugRenderer(const DebugRenderer&) = delete;
    DebugRenderer& operator=(const DebugRenderer&) = delete;

    void render(
        const rp3d::DebugRenderer& physicsDebugRenderer,
        const glm::mat4& view,
        const glm::mat4& projection
    );

    void setLineWidth(float width);

    void setDepthTest(bool enabled);

private:

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 color;
    };

private:

    GLuint shaderProgram = 0;

    GLuint lineVAO = 0;
    GLuint lineVBO = 0;

    GLuint triangleVAO = 0;
    GLuint triangleVBO = 0;

    GLint viewLocation = -1;
    GLint projectionLocation = -1;

    float lineWidth = 2.0f;

    bool depthTest = true;

private:

    void createShader();

    void createBuffers();

    GLuint compileShader(
        GLenum type,
        const char* source
    );

    glm::vec3 convertVector(
        const rp3d::Vector3& vector
    );

    glm::vec3 convertColor(
        rp3d::uint32 color
    );
};