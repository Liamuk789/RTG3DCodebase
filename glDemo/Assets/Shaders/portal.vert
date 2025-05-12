#version 450 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float time;

layout (location=0) in vec3 vertexPos;
layout (location=2) in vec2 vertexTexCoord;
layout (location=3) in vec3 vertexNormal;

out SimplePacket {
    vec3 surfaceWorldPos;
    vec3 surfaceNormal;
    vec2 texCoord;
} outputVertex;

void main(void) {

    //use glRotatef, glTranslatef, glScalef

    // Pass texture coordinates
    outputVertex.texCoord = vertexTexCoord;

    // Transform normal vector by the inverse-transpose of the model matrix
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
    outputVertex.surfaceNormal = normalize(normalMatrix * vertexNormal);

    // Transform vertex position to world coordinates
    vec4 worldCoord = modelMatrix * vec4(vertexPos, 1.0);
    outputVertex.surfaceWorldPos = worldCoord.xyz;

    // Apply a sine wave based on world-space x, z coordinates and time
    float wave = sin(worldCoord.x * 5.0 + worldCoord.z * 10.0 + time) * 0.15;

    // Adjust the vertex position with the wave effect
    vec3 wavyPos = vertexPos + vec3(0.0, wave, 0.0);

    // Transform the adjusted position to world coordinates
    worldCoord = modelMatrix * vec4(wavyPos, 1.0);
    
    
    // Transform to clip space
    gl_Position = projMatrix * viewMatrix * worldCoord;
}