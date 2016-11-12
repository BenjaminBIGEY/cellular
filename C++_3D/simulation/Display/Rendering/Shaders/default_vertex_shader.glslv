#version 150 core // GLSL version

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

in vec3 vert;
in vec3 vertNorm;
in vec4 vertColor;


out vec3 fragVert;
out vec3 fragNorm;
out vec4 fragColor;


void main() {
    // Passage to the fragment shader
    fragVert = vert;
    fragNorm = vertNorm;
    fragColor = vertColor;

    // Application of position modifications
    gl_Position = projection * camera * model * vec4(vert, 1);
}