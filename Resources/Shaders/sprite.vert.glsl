#version 330 core
layout (location = 0) in vec4 positionTexture; // vec2 position vec2 texCoord


out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 model; // Model matrix for Rotation, Translation and scaling
uniform mat4 view;

void main(){
    gl_Position = projection  * view * model   * vec4(positionTexture.xy, 1.0, 1.0);
    TexCoord = positionTexture.zw;            
}