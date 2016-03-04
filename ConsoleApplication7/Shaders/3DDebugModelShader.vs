#version 330 core

//input
//layout(location = 0) in vec4 in_posL;
layout(location = 0) in vec3 in_posL;
layout(location = 1) in vec2 in_UV;

//output
out vec2 out_UV;

//uniforms
uniform mat4 u_WVP;

void main()
{
    //gl_Position = in_posL;//vec4(in_posL, 1.0);
	gl_Position = u_WVP * vec4(in_posL, 1.0);
	out_UV = in_UV;
}

