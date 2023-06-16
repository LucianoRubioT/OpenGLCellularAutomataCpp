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
uniform float uIntensity;
uniform float uQuantize;
uniform sampler2D uTexture;

//uniform sampler2D uTexture, uBeforeUnit, uAfterUnit;

void main()
{
	ivec2 ires = textureSize(uTexture, 0);
	float ResS = float(ires.s);
	float ResT = float(ires.t);
	//vec3 irgb = texture(uTexture, v_texCoord).rgb;
	//vec3 brgb = texture(uBeforeUnit, v_texCoord).rgb;
	//vec3 argb = texture(uAfterUnit, v_texCoord).rgb;
	vec3 rgb = texture(uTexture, v_texCoord).rgb;
	vec2 stp0 = vec2(1. / ResS, 0.);
	vec2 st0p = vec2(0., 1. / ResT);
	vec2 stpp = vec2(1. / ResS, 1. / ResT);
	vec2 stpm = vec2(1. / ResS, -1. / ResT);
	const vec3 W = vec3(0.2125, 0.7154, 0.0721);
	float i00 = dot(texture(uTexture, v_texCoord).rgb, W);
	float im1m1 = dot(texture(uTexture, v_texCoord - stpp).rgb, W);
	float ip1p1 = dot(texture(uTexture, v_texCoord + stpp).rgb, W);
	float im1p1 = dot(texture(uTexture, v_texCoord - stpm).rgb, W);
	float ip1m1 = dot(texture(uTexture, v_texCoord + stpm).rgb, W);
	float im10 = dot(texture(uTexture, v_texCoord - stp0).rgb, W);
	float ip10 = dot(texture(uTexture, v_texCoord + stp0).rgb, W);
	float i0m1 = dot(texture(uTexture, v_texCoord - st0p).rgb, W);
	float i0p1 = dot(texture(uTexture, v_texCoord + st0p).rgb, W);
	// next two lines apply the H and V Sobel filters at the pixel
	float h = -1. * im1p1 - 2. * i0p1 - 1. * ip1p1 + 1. * im1m1 + 2. * i0m1 + 1. * ip1m1;
	float v = -1. * im1m1 - 2. * im10 - 1. * im1p1 + 1. * ip1m1 + 2. * ip10 + 1. * ip1p1;
	float mag = length(vec2(h, v)); // how much change
	 // is there?
	if (mag > uIntensity)
	{ // if too much, use black
		f_color = vec4(0., 0., 0., 1.);
	}
	else
	{ // else quantize the color
		rgb.rgb *= uQuantize;
		rgb.rgb += vec3(.5, .5, .5); // round
		ivec3 intrgb = ivec3(rgb.rgb); // truncate
		rgb.rgb = vec3(intrgb) / uQuantize;
		f_color = vec4(rgb, 1.);
	}
}