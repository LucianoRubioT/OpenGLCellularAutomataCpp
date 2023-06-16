#shader.vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;
uniform vec4 uColor;
uniform mat4 uModel;
out vec4 v_color;
out vec2 v_texCoord;

void main()
{
	gl_Position = uModel * position;
	v_color = vec4(color, 0.0) * uColor;
	v_texCoord = texCoord;
}

#shader.fragment
#version 330 core

in vec2 v_texCoord;
in vec4 v_color;
out vec4 f_color;
uniform int uWidth;
uniform int uHeight;
uniform sampler2D uTexture;

int getNeighbour(int x, int y) 
{ return int(texture2D(uTexture, (gl_FragCoord.xy + vec2(x, y)) / vec2(uWidth, uHeight)).r); }

void main() 
{
	int count = getNeighbour(1, 0) + getNeighbour(-1, 0) + getNeighbour(0, 1) + getNeighbour(0, -1)
		+ getNeighbour(1, 1) + getNeighbour(1, -1) + getNeighbour(-1, -1) + getNeighbour(-1, 1);
	
	if (count == 0)
	{
		f_color = vec4(1, 0, 1, 1);
	}
	else if (count < 5)
	{
		f_color = vec4(0, 1, 0, 1);
	}
	else f_color = vec4(1, 0, 0, 1);

}