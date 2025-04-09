#version 450 core

layout(binding = 0) uniform sampler2D texture;

struct PointLight {
    vec3 pntPos;
    vec3 pntCol;
    vec3 pntAtt;
};

uniform int numPointLights;
uniform PointLight pointLights[10];

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

    // Combine light contributions
    vec3 finalColour = directionalAmbient + directionalDiffuse + totalPointDiffuse;
    fragColour = vec4(finalColour, surfaceColour.a);
}