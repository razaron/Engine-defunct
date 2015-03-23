#version 150

in vec3 position;
in vec3 colour;

out vec4 Colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 ovColour = vec3(1.0, 1.0, 1.0);
uniform float alpha = 1.0;

void main()
{
	Colour = vec4(colour*ovColour, alpha);
    gl_Position = projection * view * model * vec4(position, 1.0);
}