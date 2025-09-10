#version 330 core

layout(location = 0) in vec2 aPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model; // Model matrix for Rotation, Translation and scaling

void main()
{
    gl_Position = projection * model * view * vec4(aPos, 1.0, 1.0);
}
