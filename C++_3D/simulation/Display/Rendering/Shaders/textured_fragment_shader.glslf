#version 150 core

uniform int       useTextures;
uniform sampler2D tex;

uniform mat4 model;
uniform vec3 cameraPos;

uniform vec3 lightPosition;

uniform struct {
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 ambientColor;

    float specularIntensity;
    float specularHardness;
} material;

in vec3 fragVert;
in vec3 fragNorm;
in vec4 fragTexCoord;

out vec4 finalColor;

void main() {
    vec4 color;
    if (useTextures == 1) {
        color = texture(tex, fragTexCoord);
    }
    else {
        color = Vec4(1);
    }

    // Calculation of reals positions of scene elements
    vec3 normal   = normalize(transpose(inverse(mat3(model))) * fragNorm);
    vec3 position = vec3(model * vec4(fragVert, 1));

    // Calculation of fragment->camera vector
    vec3 fragToCam = normalize(cameraPos - position);



    // Calculation of light characteristics (light vector)
    vec3 lightVect = position - lightPosition;;
    float lightVectLength = length(lightVect);
    lightVect = normalize(lightVect);

    float attenuation = 1 / (1 + lightVectLength * lightVectLength * 0);






    //Calcul de l'effet de la lumière sur le matériau
    //intensité diffuse
    float diffuseCoef = max(- dot(normal, lightVect), 0);
    vec3 diffuseIntensity = vec3(diffuseCoef);
    diffuseIntensity *= material.diffuseColor;

    //intensité ambiente
    vec3 ambientIntensity = vec3(0.2);
    ambientIntensity *= material.ambientColor;

    //intensité speculaire
    vec3 specularIntensity = vec3(0.0);
    if (diffuseCoef != 0) {
        specularIntensity = vec3(pow(max(dot(fragToCam, reflect(lightVect, normal)), 0), material.specularHardness));
    }
    specularIntensity *= material.specularColor * material.specularIntensity;


    //Calcul final
    vec3 gamma = vec3(1);
    finalColor = vec4(pow(ambientIntensity + attenuation * (diffuseIntensity + specularIntensity), gamma), 0.8);




    if (useTextures == 1) {
        finalColor *= texture(tex, fragTexCoord);
    }
}