#version 450

layout( push_constant ) uniform constants
{
    mat4 view;
    mat4 proj;
	mat4 model;
} PushConstants;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 texCoord;

layout(location = 0) out vec2 uv;

void main() {
    gl_Position = PushConstants.proj * PushConstants.view * PushConstants.model * vec4(inPosition, 1.0);
	uv = texCoord;
}