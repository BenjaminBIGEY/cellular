#version 150 core // GLSL version

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

in vec3 vert;
in vec3 vertNorm;
in vec2 vertTexCoord;


out vec3 fragVert;
out vec3 fragNorm;
out vec2 fragTexCoord;


void main() {
    // Passage to the fragment shader
    fragVert = vert;
    fragNorm = vertNorm;
    fragTexCoord = vertTexCoord;

    // Application of position modifications
    gl_Position = projection * camera * model * vec4(vert, 1);
}