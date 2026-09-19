#include "DebugRenderer.hpp"

#include <iostream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include "../glfw/glfwWindow.hpp"


// ============================================================
// Shader
// ============================================================

static const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;

void main()
{
    gl_Position =
        projection *
        view *
        vec4(aPosition, 1.0);

    vertexColor = aColor;
}
)";


static const char* fragmentShaderSource = R"(
#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}
)";


// ============================================================
// Constructor
// ============================================================

DebugRenderer::DebugRenderer(OpenGLGame::GlfwWindow* window)
{
    createShader();
    createBuffers();
}


// ============================================================
// Destructor
// ============================================================

DebugRenderer::~DebugRenderer()
{
    if (lineVAO != 0)
    {
        glDeleteVertexArrays(
            1,
            &lineVAO
        );
    }

    if (lineVBO != 0)
    {
        glDeleteBuffers(
            1,
            &lineVBO
        );
    }

    if (triangleVAO != 0)
    {
        glDeleteVertexArrays(
            1,
            &triangleVAO
        );
    }

    if (triangleVBO != 0)
    {
        glDeleteBuffers(
            1,
            &triangleVBO
        );
    }

    if (shaderProgram != 0)
    {
        glDeleteProgram(shaderProgram);
    }
}


// ============================================================
// Create shader program
// ============================================================

void DebugRenderer::createShader()
{
    GLuint vertexShader =
        compileShader(
            GL_VERTEX_SHADER,
            vertexShaderSource
        );

    GLuint fragmentShader =
        compileShader(
            GL_FRAGMENT_SHADER,
            fragmentShaderSource
        );


    shaderProgram = glCreateProgram();

    glAttachShader(
        shaderProgram,
        vertexShader
    );

    glAttachShader(
        shaderProgram,
        fragmentShader
    );

    glLinkProgram(shaderProgram);


    GLint success = 0;

    glGetProgramiv(
        shaderProgram,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetProgramInfoLog(
            shaderProgram,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "DebugRenderer shader program linking failed:\n"
            << infoLog
            << std::endl;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // Cache uniform locations.
    // We don't need to call glGetUniformLocation()
    // every frame.

    viewLocation =
        glGetUniformLocation(
            shaderProgram,
            "view"
        );

    projectionLocation =
        glGetUniformLocation(
            shaderProgram,
            "projection"
        );
}


// ============================================================
// Compile individual shader
// ============================================================

GLuint DebugRenderer::compileShader(
    GLenum type,
    const char* source
)
{
    GLuint shader =
        glCreateShader(type);


    glShaderSource(
        shader,
        1,
        &source,
        nullptr
    );

    glCompileShader(shader);


    GLint success = 0;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );


    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            shader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr
            << "DebugRenderer shader compilation failed:\n"
            << infoLog
            << std::endl;
    }


    return shader;
}


// ============================================================
// Create VAOs and VBOs
// ============================================================

void DebugRenderer::createBuffers()
{
    // ========================================================
    // Lines
    // ========================================================

    glGenVertexArrays(
        1,
        &lineVAO
    );

    glGenBuffers(
        1,
        &lineVBO
    );


    glBindVertexArray(lineVAO);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        lineVBO
    );


    // The actual size is supplied during render().
    glBufferData(
        GL_ARRAY_BUFFER,
        0,
        nullptr,
        GL_DYNAMIC_DRAW
    );


    // Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(
            offsetof(Vertex, position)
            )
    );

    glEnableVertexAttribArray(0);


    // Color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(
            offsetof(Vertex, color)
            )
    );

    glEnableVertexAttribArray(1);


    // ========================================================
    // Triangles
    // ========================================================

    glGenVertexArrays(
        1,
        &triangleVAO
    );

    glGenBuffers(
        1,
        &triangleVBO
    );


    glBindVertexArray(triangleVAO);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        triangleVBO
    );


    glBufferData(
        GL_ARRAY_BUFFER,
        0,
        nullptr,
        GL_DYNAMIC_DRAW
    );


    // Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(
            offsetof(Vertex, position)
            )
    );

    glEnableVertexAttribArray(0);


    // Color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(
            offsetof(Vertex, color)
            )
    );

    glEnableVertexAttribArray(1);


    // Clean up bindings

    glBindBuffer(
        GL_ARRAY_BUFFER,
        0
    );

    glBindVertexArray(0);
}


// ============================================================
// Convert RP3D Vector3 -> GLM vec3
// ============================================================

glm::vec3 DebugRenderer::convertVector(
    const rp3d::Vector3& vector
)
{
    return glm::vec3(
        static_cast<float>(vector.x),
        static_cast<float>(vector.y),
        static_cast<float>(vector.z)
    );
}


// ============================================================
// Convert RP3D packed RGB color -> GLM vec3
// ============================================================

glm::vec3 DebugRenderer::convertColor(
    rp3d::uint32 color
)
{
    // RP3D colors are stored as:
    //
    // 0xRRGGBB
    //
    // Extract each component.

    float red =
        static_cast<float>(
            (color >> 16) & 0xFF
            ) / 255.0f;

    float green =
        static_cast<float>(
            (color >> 8) & 0xFF
            ) / 255.0f;

    float blue =
        static_cast<float>(
            color & 0xFF
            ) / 255.0f;


    return glm::vec3(
        red,
        green,
        blue
    );
}


// ============================================================
// Set line width
// ============================================================

void DebugRenderer::setLineWidth(
    float width
)
{
    lineWidth = width;
}


// ============================================================
// Set depth testing
// ============================================================

void DebugRenderer::setDepthTest(
    bool enabled
)
{
    depthTest = enabled;
}


// ============================================================
// Render
// ============================================================

void DebugRenderer::render(
    const rp3d::DebugRenderer& physicsDebugRenderer,
    const glm::mat4& view,
    const glm::mat4& projection
)
{
    // ========================================================
    // Get RP3D data
    // ========================================================

    const rp3d::DebugRenderer::DebugLine* lines =
        physicsDebugRenderer.getLinesArray();

    const rp3d::uint32 numberOfLines =
        physicsDebugRenderer.getNbLines();


    const rp3d::DebugRenderer::DebugTriangle* triangles =
        physicsDebugRenderer.getTrianglesArray();

    const rp3d::uint32 numberOfTriangles =
        physicsDebugRenderer.getNbTriangles();


    // Nothing to render.
    if (
        numberOfLines == 0 &&
        numberOfTriangles == 0
        )
    {
        return;
    }


    // ========================================================
    // Save OpenGL state
    // ========================================================

    GLboolean wasDepthTestEnabled =
        glIsEnabled(GL_DEPTH_TEST);


    // ========================================================
    // Set depth testing
    // ========================================================

    if (depthTest)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }


    // ========================================================
    // Use shader
    // ========================================================

    glUseProgram(shaderProgram);


    glUniformMatrix4fv(
        viewLocation,
        1,
        GL_FALSE,
        glm::value_ptr(view)
    );

    glUniformMatrix4fv(
        projectionLocation,
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );


    // ========================================================
    // Render lines
    // ========================================================

    if (
        lines != nullptr &&
        numberOfLines > 0
        )
    {
        std::vector<Vertex> vertices;

        vertices.reserve(
            numberOfLines * 2
        );


        for (
            rp3d::uint32 i = 0;
            i < numberOfLines;
            ++i
            )
        {
            const auto& line = lines[i];


            vertices.push_back({
                convertVector(line.point1),
                convertColor(line.color1)
                });


            vertices.push_back({
                convertVector(line.point2),
                convertColor(line.color2)
                });
        }


        glBindVertexArray(lineVAO);

        glBindBuffer(
            GL_ARRAY_BUFFER,
            lineVBO
        );


        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(
                vertices.size() * sizeof(Vertex)
                ),
            vertices.data(),
            GL_DYNAMIC_DRAW
        );


        glLineWidth(lineWidth);


        glDrawArrays(
            GL_LINES,
            0,
            static_cast<GLsizei>(
                vertices.size()
                )
        );
    }


    // ========================================================
    // Render triangles
    // ========================================================

    if (
        triangles != nullptr &&
        numberOfTriangles > 0
        )
    {
        std::vector<Vertex> vertices;

        vertices.reserve(
            numberOfTriangles * 3
        );


        for (
            rp3d::uint32 i = 0;
            i < numberOfTriangles;
            ++i
            )
        {
            const auto& triangle =
                triangles[i];


            vertices.push_back({
                convertVector(triangle.point1),
                convertColor(triangle.color1)
                });


            vertices.push_back({
                convertVector(triangle.point2),
                convertColor(triangle.color2)
                });


            vertices.push_back({
                convertVector(triangle.point3),
                convertColor(triangle.color3)
                });
        }


        glBindVertexArray(triangleVAO);

        glBindBuffer(
            GL_ARRAY_BUFFER,
            triangleVBO
        );


        glBufferData(
            GL_ARRAY_BUFFER,
            static_cast<GLsizeiptr>(
                vertices.size() * sizeof(Vertex)
                ),
            vertices.data(),
            GL_DYNAMIC_DRAW
        );


        glDrawArrays(
            GL_TRIANGLES,
            0,
            static_cast<GLsizei>(
                vertices.size()
                )
        );
    }


    // ========================================================
    // Restore OpenGL state
    // ========================================================

    glBindBuffer(
        GL_ARRAY_BUFFER,
        0
    );

    glBindVertexArray(0);

    glUseProgram(0);


    if (wasDepthTestEnabled)
    {
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
}