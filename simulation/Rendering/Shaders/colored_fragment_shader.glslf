#version 150 core

uniform mat4 model;
uniform vec3 cameraPosition;


in vec4 fragColor;

out vec4 finalColor;



void main() {
    finalColor = fragColor;
}