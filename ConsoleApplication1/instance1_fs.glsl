#version 330 core
out vec4 FragColor;

in vec3 fColor;

uniform float time;

void main()
{
    FragColor = vec4(sin(time)*fColor.x, cos(time)*fColor.y,sin(2*time)*fColor.z, 1.0);
}