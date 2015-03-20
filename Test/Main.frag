#version 150

in vec3 Colour;

out vec4 outColour;

void main()
{
	outColour = vec4(Colour, 1.0);
	//outColour = vec4(1.0,1.0,1.0, 1.0);
}
