#version 450 core

layout(binding = 0) uniform sampler2D texture;

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

struct SpotLight {
    vec3 spotPos;
    vec3 spotDir;
    vec3 spotCol;
    vec3 spotAtt;
    float spotCutoff;
    float spotOuterCutoff;
};

uniform int numPointLights;
uniform PointLight pointLights[10];

uniform int numTorchLights;
uniform TorchLight torchLights[36];

uniform int numSpotLights;
uniform SpotLight spotLights[13];

uniform vec3 DIRDir;
uniform vec3 DIRCol;
uniform vec3 DIRAmb;

in SimplePacket {
    vec3 surfaceWorldPos;
    vec3 surfaceNormal;
    vec2 texCoord;
} inputFragment;

layout (location=0) out vec4 fragColour;

void main(void) {
    vec3 N = normalize(inputFragment.surfaceNormal);
    vec4 surfaceColour = texture2D(texture, inputFragment.texCoord);

    // Directional light calculations
    vec3 normalizedDIRDir = normalize(DIRDir);
    float dirL = max(dot(N, normalizedDIRDir), 0.0);
    vec3 directionalDiffuse = surfaceColour.rgb * DIRCol * dirL;
    vec3 directionalAmbient = DIRAmb;

    vec3 totalPointDiffuse = vec3(0.0);
    vec3 totalTorchDiffuse = vec3(0.0);
    vec3 totalSpotDiffuse = vec3(0.0);

    // Point light calculations
    for (int i = 0; i < numPointLights; i++) {
        vec3 surfaceToLightVec = pointLights[i].pntPos - inputFragment.surfaceWorldPos;
        vec3 surfaceToLightNormalised = normalize(surfaceToLightVec);

        float pntL = max(dot(N, surfaceToLightNormalised), 0.0);
        float pntD = length(surfaceToLightVec);

        float maxCalcDistance = 12.0f;

        if (pntD < maxCalcDistance) {
            float kc = pointLights[i].pntAtt.x;
            float kl = pointLights[i].pntAtt.y;
            float kq = pointLights[i].pntAtt.z;

            float atten = 1.0 / (kc + (kl * pntD) + (kq * (pntD * pntD)));
            float edgeSoftness = smoothstep(maxCalcDistance * 0.9, maxCalcDistance, pntD);
            atten *= 1.0 - edgeSoftness;
            totalPointDiffuse += surfaceColour.rgb * pointLights[i].pntCol * pntL * atten;
        }
    }

    // Torch light calculations
    for (int i = 0; i < numTorchLights; i++) {
        vec3 surfaceToLightVec = torchLights[i].torPos - inputFragment.surfaceWorldPos;
        vec3 surfaceToLightNormalised = normalize(surfaceToLightVec);

        float torL = max(dot(N, surfaceToLightNormalised), 0.0);
        float torD = length(surfaceToLightVec);

        float maxCalcDistance = 12.0f;

        if (torD < maxCalcDistance) {
            float kc = torchLights[i].torAtt.x;
            float kl = torchLights[i].torAtt.y;
            float kq = torchLights[i].torAtt.z;

            float atten = 1.0 / (kc + (kl * torD) + (kq * (torD * torD)));
            float edgeSoftness = smoothstep(maxCalcDistance * 0.9, maxCalcDistance, torD);
            atten *= 1.0 - edgeSoftness;
            totalTorchDiffuse += surfaceColour.rgb * torchLights[i].torCol * torL * atten;
        }
    }

    // Spotlight calculations
    for (int i = 0; i < numSpotLights; i++) {
        vec3 surfaceToLightVec = spotLights[i].spotPos - inputFragment.surfaceWorldPos;
        vec3 surfaceToLightNormalised = normalize(surfaceToLightVec);

        float spotL = max(dot(N, surfaceToLightNormalised), 0.0);
        float spotD = length(surfaceToLightVec);

        float maxCalcDistance = 15.0f;

        if (spotD < maxCalcDistance) {
            float kc = spotLights[i].spotAtt.x;
            float kl = spotLights[i].spotAtt.y;
            float kq = spotLights[i].spotAtt.z;

            float atten = 1.0 / (kc + (kl * spotD) + (kq * (spotD * spotD)));

            // Spotlight cone calculations
            float theta = dot(surfaceToLightNormalised, normalize(-spotLights[i].spotDir));
            float epsilon = spotLights[i].spotCutoff - spotLights[i].spotOuterCutoff;
            float intensity = clamp((theta - spotLights[i].spotOuterCutoff) / epsilon, 0.0, 1.0);

            atten *= intensity;

            totalSpotDiffuse += surfaceColour.rgb * spotLights[i].spotCol * spotL * atten;
        }
    }

    // Combine light contributions
    vec3 finalColour = directionalAmbient + directionalDiffuse + totalPointDiffuse + totalTorchDiffuse + totalSpotDiffuse;
    finalColour = clamp(finalColour, 0.0, 1.0);
    fragColour = vec4(finalColour, surfaceColour.a);
    
    //Grayscale Conversion
    // Convert to grayscale
    //float grayscale = 0.299 * finalColour.r + 0.587 * finalColour.g + 0.114 * finalColour.b;

    // Output grayscale color
    //fragColour = vec4(vec3(grayscale), surfaceColour.a);
}