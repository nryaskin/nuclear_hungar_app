#version 330
uniform mat4 gWorld;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec4 vColor;

void main()
{
  gl_Position = gWorld * vec4(position, 1.0);
  vColor = vec4(color, 1.0);
}
