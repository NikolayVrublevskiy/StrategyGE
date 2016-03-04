#version 330 core

// input
in vec2 out_UV;

// output
out vec4 color;

//uniforms
uniform sampler2D myTextureSampler;

void main()
{
	color = vec4(0.0, 1.0, 0.0, 1.0);//texture( myTextureSampler, out_UV );
}