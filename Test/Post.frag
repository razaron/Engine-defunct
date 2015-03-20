#version 150
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texFramebuffer;
void main() {
    outColor = vec4(1.0, 1.0, 1.0, 1.0) - texture(texFramebuffer, Texcoord);
}