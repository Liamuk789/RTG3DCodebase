#version 450 core

//Diffuse texture - directional light

//Texture sampler (for diffuse surface colour)
layout(binding = 0) uniform sampler2D texture;

//Directional light model
uniform vec3 DIRDir;
uniform vec3 DIRCol;
uniform vec3 DIRAmb;

//Point Light Model
uniform vec3 PNTPos;
uniform vec3 PNTCol;
uniform vec3 PNTAtt;


in SimplePacket {
	
	vec3 surfaceWorldPos;
	vec3 surfaceNormal;
	vec2 texCoord;

} inputFragment;

layout (location=0) out vec4 fragColour;

void main(void) {
    vec3 N = normalize(inputFragment.surfaceNormal);

    //Directional light calculations
    float dirL = max(dot(N, DIRDir), 0.0);
    vec4 surfaceColour = texture2D(texture, inputFragment.texCoord);
    vec3 directionalDiffuse = surfaceColour.rgb * DIRCol * dirL;
    vec3 directionalAmbient = DIRAmb;

    //Point light vector from surface to light
    vec3 surfaceToLightVec = PNTPos - inputFragment.surfaceWorldPos;
    vec3 surfaceToLightNormalised = normalize(surfaceToLightVec);

    //Point light calculations
    float pntL = max(dot(N, surfaceToLightNormalised), 0.0);
    float pntD = length(surfaceToLightVec);

    //If the distance to an object is over the maxCalcDistance
    //the light will not shine onto it.
    vec3 pointDiffuse = vec3(0.0);
    float maxCalcDistance = 6.0f;

    if (pntD < maxCalcDistance) {
        float kc = PNTAtt.x;
        float kl = PNTAtt.y;
        float kq = PNTAtt.z;

        //Attenuation
        float atten = 1.0 / (kc + (kl * pntD) + (kq * (pntD * pntD)));

        //use of smoothstep to soften edges
        float edgeSoftness = smoothstep(maxCalcDistance * 0.9, maxCalcDistance, pntD);
        //reduce atten closer to the edge
        atten *= 1.0 - edgeSoftness; 

        pointDiffuse = surfaceColour.rgb * PNTCol * pntL * atten;
    }

    //add light information together
    vec3 finalColor = directionalAmbient + directionalDiffuse + pointDiffuse;
    fragColour = vec4(finalColor, surfaceColour.a);
}
