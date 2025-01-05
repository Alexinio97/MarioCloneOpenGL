#include "includes/Core/Box2DRenderer.h"
#include <glad/glad.h>
#include <vector>


Box2DRenderer::Box2DRenderer(Shader& shader)
    : m_Shader(&shader)
{
}

void Box2DRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    std::vector<glm::vec2> glVertices(vertexCount);
    for (int i = 0; i < vertexCount; ++i)
    {
        glVertices[i] = glm::vec2(vertices[i].x, vertices[i].y);
    }

    m_Shader->Use();
    // TODO: add color to shader here

    GLuint vao, vbo;
    
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * vertexCount, glVertices.data(), GL_STATIC_DRAW); // upload vertex data to GPU memory into a buffer

    // Set vertex attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL); // how the vertex  attributes are laid out and how they should be interpreted by the GPU 
    glEnableVertexAttribArray(0); // enable the vertex attribute array
    
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

    // Cleanup
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Box2DRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
}

void Box2DRenderer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
}

void Box2DRenderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
}

void Box2DRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
}

void Box2DRenderer::DrawTransform(const b2Transform& xf)
{
}

void Box2DRenderer::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
}
