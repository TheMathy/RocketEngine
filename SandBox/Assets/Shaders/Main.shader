#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textureCoords;
layout(location = 2) in vec3 normal;

out vec2 TextureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

uniform vec3 u_lightPosition;

void main()
{
    vec4 worldPosition = u_ModelMatrix * vec4(position, 1.0);
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * worldPosition;
    TextureCoords = textureCoords;

    surfaceNormal = (u_ModelMatrix * vec4(normal, 0.0)).xyz;
    toLightVector = u_lightPosition - worldPosition.xyz;
    toCameraVector = (inverse(u_ViewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz; 
}

#shader fragment
#version 330 core

in vec2 TextureCoords;
in vec3 surfaceNormal;
in vec3 toLightVector;
in vec3 toCameraVector;

out vec4 out_Color;

uniform sampler2D textureSampler;
uniform vec3 u_lightColor;

uniform float u_shineDamper;
uniform float u_reflectivity;

void main()
{
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightVector);

    float nDot1 = dot(unitNormal, unitLightVector);
    float brightness = max(nDot1, 0.0);
    vec3 diffuse = brightness * u_lightColor;

    vec3 unitVectorToCamera = normalize(toCameraVector);
    vec3 lightDirection = -unitVectorToCamera;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
    specularFactor = max(specularFactor, 0.0);
    float dampedFactor = pow(specularFactor, u_shineDamper);
    vec3 finalSpecular = dampedFactor * u_lightColor;

    out_Color = vec4(diffuse, 1.0) * texture(textureSampler, TextureCoords) + vec4(finalSpecular, 1.0);
} 