#version 330 core

//input
layout(location = 0) in vec3 in_posL;

//uniforms
uniform mat4 u_WVP;

void main()
{
    gl_Position = u_WVP * vec4(in_posL, 1.0);
}

