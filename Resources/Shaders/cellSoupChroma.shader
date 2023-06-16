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
uniform float uTime;
uniform sampler2D uTexture;

int getRed(int x, int y) 
{ return int(texture2D(uTexture, (gl_FragCoord.xy + vec2(x, y)) / vec2(uWidth, uHeight)).r); }
int getGreen(int x, int y)
{ return int(texture2D(uTexture, (gl_FragCoord.xy + vec2(x, y)) / vec2(uWidth, uHeight)).g); }
int getBlue(int x, int y)
{ return int(texture2D(uTexture, (gl_FragCoord.xy + vec2(x, y)) / vec2(uWidth, uHeight)).b); }

float rule(int count)
{
	if (count == 0)
		return 1;
	else if (count < 5)
		return 0;
	else return 1;
}

void main() 
{
	int sumR =getRed(-1, -1) + getRed(-1, 0) + getRed(-1, 1) + getRed(0, -1)
		+ getRed(0, 1)  + getRed(1, -1) +	getRed(1, 0) + getRed(1, 1);
	int sumB = getBlue(-1, -1) + getBlue(-1, 0) + getBlue(-1, 1) + getBlue(0, -1)
		+ getBlue(0, 1) + getBlue(1, -1) + getBlue(1, 0) + getBlue(1, 1);
	int sumG = getGreen(-1, -1) + getGreen(-1, 0) + getGreen(-1, 1) + getGreen(0, -1)
		+ getGreen(0, 1) + getGreen(1, -1) + getGreen(1, 0) + getGreen(1, 1);

	f_color = vec4( rule(sumR), rule(sumG), rule(sumB), 1);
}