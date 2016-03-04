#version 330 core

// input
in vec2 out_UV;

// output
out vec4 color;

//uniforms
uniform sampler2D myTextureSampler;

void main()
{
	color = texture( myTextureSampler, out_UV );
}