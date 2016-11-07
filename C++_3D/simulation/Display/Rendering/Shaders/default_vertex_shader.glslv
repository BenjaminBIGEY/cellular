#version 150

uniform mat4 projection;
uniform mat4 camera;
uniform mat4 model;

in vec3 vert;
in vec2 vertTexCoord;
in vec3 vertNorm;

out vec2 fragTexCoord;
out vec3 fragVert;
out vec3 fragNorm;

void main() {
    //Passage au fragment shader
    fragTexCoord = vertTexCoord;
    fragVert = vert;
    fragNorm = vertNorm;

    //Application des modifications de position.
    gl_Position = projection * camera * model * vec4(vert, 1);
}