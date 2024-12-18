#pragma once

#include <includes/Core/Renderer.h>
#include <iostream>

Renderer::Renderer(Shader& shader)
    : m_VAO(0), m_VBO(0), m_EBO(0), m_Shader(shader)
{
    SetupQuad();
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Renderer::SetupQuad()
{
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position and texture attribute
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Renderer::Render(const Texture2D& texture)
{        
    glBindTexture(GL_TEXTURE_2D, texture.GetTextureId()); 
    m_Shader.Use();

    glBindVertexArray(m_VAO);        
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::RenderSprite(const Texture2D& texture, glm::vec2 position, glm::vec2 size, int spriteIndex, int spriteWidth, int spriteHeight)
{    
    int spriteColumns = texture.GetWidth() / spriteWidth;
    int spriteRows = texture.GetHeight() / spriteHeight;

    int column = spriteIndex % spriteColumns;
    int row = spriteIndex / spriteColumns;

    float u_start = static_cast<float>(column) * static_cast<float>(spriteWidth) / texture.GetWidth();
    float v_start = static_cast<float>(row) * static_cast<float>(spriteHeight) / texture.GetHeight();
    float u_end = u_start + (static_cast<float>(spriteWidth) / texture.GetWidth());
    float v_end = v_start + (static_cast<float>(spriteHeight) / texture.GetHeight());


    float vertices[] = {
        // positions          // colors           // texture coords
           0.0f, 1.0f,   u_start, v_start, // top right
           1.0f,  0.0f,   u_end, v_end,   // bottom right
           0.0f,  0.0f,   u_start, v_end,     // bottom left
           1.0f, 1.0f,   u_end, v_start    // top left
    };

    unsigned int indices[] = {
        0,2,1,
        0,1,3
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);        
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position and texture attribute
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_Shader.SetInteger("ourTexture", 0);
    
    // Bind texture and render
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));  // when z = 40.0f, it is far outside the visible range of [-1.0f, 1.0f] texture was not displaying
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));    
    model = glm::scale(model, glm::vec3(size, 0.0f));
    m_Shader.SetMatrix4("model", model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.GetTextureId());
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}