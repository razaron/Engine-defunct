#version 150

in vec3 Colour;
in vec2 Texcoord;

out vec4 outColour;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;

void main()
{
	vec4 colKitten = texture(texKitten, Texcoord);
	vec4 colPuppy = texture(texPuppy, Texcoord);
    outColour = mix(colKitten, colPuppy, 0.5) * vec4(Colour, 1.0);
	//outColour = vec4(1.0,1.0,1.0, 1.0);
}
