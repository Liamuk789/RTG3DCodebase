#version 450 core

layout(binding = 0) uniform sampler2D basetexture;
layout(binding = 1) uniform sampler2D normalMap;

struct PointLight {
    vec3 pntPos;
    vec3 pntCol;
    vec3 pntAtt;
};

struct TorchLight {
    vec3 torPos;
    vec3 torCol;
    vec3 torAtt;
};

uniform int numPointLights;
uniform PointLight pointLights[10];

uniform int numTorchLights;
uniform TorchLight torchLights[36];

uniform vec3 DIRDir;
uniform vec3 DIRCol;
uniform vec3 DIRAmb;

in vec3 surfaceWorldPos;
in vec3 surfaceNormal;
in vec2 texCoord;
in mat3 TBN;

out vec4 FragColour;

void main() 
{
    //Sample and transform the normal map
    vec3 normal = texture(normalMap, texCoord.xy).rgb;
    normal = normal * 2.0 - 1.0; // Convert from [0,1] to [-1,1]
    normal = normalize(TBN * normal); // Transform to world space

    //Sample the base texture (including alpha)
    vec4 baseTexture = texture(basetexture, texCoord.xy);
    vec3 baseColour = baseTexture.rgb;
    float alpha = baseTexture.a; // Sample alpha channel

    // Directional light calculations
    vec3 normalizedDIRDir = normalize(DIRDir);
    float dirL = max(dot(normal, normalizedDIRDir), 0.0);
    vec3 directionalDiffuse = baseColour * DIRCol * dirL;
    vec3 directionalAmbient = DIRAmb;

    vec3 totalPointDiffuse = vec3(0.0);
    vec3 totalTorchDiffuse = vec3(0.0);

    // Point light calculations
    for (int i = 0; i < numPointLights; i++) {
        vec3 surfaceToLightVec = pointLights[i].pntPos - surfaceWorldPos;
        vec3 surfaceToLightNormalised = normalize(surfaceToLightVec);

        float pntL = max(dot(normal, surfaceToLightNormalised), 0.0);
        float pntD = length(surfaceToLightVec);

        float maxCalcDistance = 12.0f;

        if (pntD < maxCalcDistance) {
            float kc = pointLights[i].pntAtt.x;
            float kl = pointLights[i].pntAtt.y;
            float kq = pointLights[i].pntAtt.z;

            float atten = 1.0 / (kc + (kl * pntD) + (kq * (pntD * pntD)));
            float edgeSoftness = smoothstep(maxCalcDistance * 0.9, maxCalcDistance, pntD);
            atten *= 1.0 - edgeSoftness;
            totalPointDiffuse += baseColour * pointLights[i].pntCol * pntL * atten;
        }
    }

    // Torch light calculations
    for (int i = 0; i < numTorchLights; i++) {
        vec3 surfaceToLightVec = torchLights[i].torPos - surfaceWorldPos;
        vec3 surfaceToLightNormalised = normalize(surfaceToLightVec);

        float torL = max(dot(normal, surfaceToLightNormalised), 0.0);
        float torD = length(surfaceToLightVec);

        float maxCalcDistance = 10.0f;

        if (torD < maxCalcDistance) {
            float kc = torchLights[i].torAtt.x;
            float kl = torchLights[i].torAtt.y;
            float kq = torchLights[i].torAtt.z;

            float atten = 1.0 / (kc + (kl * torD) + (kq * (torD * torD)));
            float edgeSoftness = smoothstep(maxCalcDistance * 0.9, maxCalcDistance, torD);
            atten *= 1.0 - edgeSoftness;
            totalTorchDiffuse += baseColour * torchLights[i].torCol * torL * atten;
        }
    }

    // Combine light contributions
    vec3 finalColour = directionalAmbient + directionalDiffuse + totalPointDiffuse + totalTorchDiffuse;

    // Output final color with alpha
    FragColour = vec4(finalColour.rgb, alpha);

    //Grayscale conversion
    // Convert to grayscale
    //float grayscale = 0.299 * finalColour.r + 0.587 * finalColour.g + 0.114 * finalColour.b;

    // Output grayscale color with alpha
    //FragColour = vec4(vec3(grayscale), alpha);
}
