#version 330 core
layout (location = 0) in vec3 GlassPos;
layout (location = 1) in vec3 GlassNormal;
layout (location = 2) in vec2 GlassTexCoords;

out vec2 GlassTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    GlassTexCoord = GlassTexCoords;    
    gl_Position = projection * view * model * vec4(GlassPos, 1.0);
}