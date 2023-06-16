#shader.vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoord;
uniform mat4 uModel;
out vec2 v_texCoord;

void main()
{
	gl_Position = uModel * position;
	v_texCoord = texCoord;
}

#shader.fragment
#version 330 core

in vec2 v_texCoord;
out vec4 f_color;
uniform sampler2D uTexture;

void main()
{
	f_color = texture(uTexture, v_texCoord);
}