#version 150

uniform int useTextures;
uniform sampler2D tex;

uniform mat4 model;
uniform vec3 cameraPos;

#define POINT_LIGHT 0
#define SUN_LIGHT 1

uniform struct {
    int type;
    vec3 position;
} light;

uniform struct {
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 ambientColor;

    float specularIntensity;
    float specularHardness;

    int emit;
} material; //Valeurs par défaut

in vec3 fragVert;
in vec3 fragNorm;
in vec2 fragTexCoord;

out vec4 finalColor;

void main() {
    //Calcul des positions réelles des éléments de la scene
    vec3 normal = normalize(transpose(inverse(mat3(model))) * fragNorm);
    vec3 position = vec3(model * vec4(fragVert, 1));
    vec3 lightPos = light.position; //vec3(model * vec4(lightPos, 1));

    //Calcul du vecteur fragment->camera
    vec3 fragToCam = normalize(cameraPos - position);


    //Calcul des caractéristiques de la lumière
    //détermination du vecteur lumière
    vec3 lightVect;
    float lightVectLength;

    if (light.type == SUN_LIGHT) {
        lightVect = - lightPos;
    }
    else {
        lightVect = position - lightPos;
    }

    lightVectLength = length(lightVect);
    lightVect = normalize(lightVect);

    //atténuation en mode POINT_LIGHT
    float attenuation = 1;
    if (light.type == POINT_LIGHT) {
        attenuation *= 1 / (1 + lightVectLength * lightVectLength * 0);
    }

    if (material.emit == 0) {
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
        finalColor = vec4(pow(ambientIntensity + attenuation * (diffuseIntensity + specularIntensity), gamma), 1);
    }
    else {
        float ratio = dot(fragToCam, normal);
        finalColor = vec4((material.diffuseColor * ratio + material.ambientColor * (1 - ratio)) * 2, 1);
    }

    if (useTextures == 1) {
        finalColor *= texture(tex, fragTexCoord);
    }
}