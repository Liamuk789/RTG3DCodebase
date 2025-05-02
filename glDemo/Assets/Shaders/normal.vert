#version 450 core

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

layout (location=0) in vec3 vertexPos;
layout (location=2) in vec2 vertexTexCoord;
layout (location=3) in vec3 vertexNormal;
layout (location=4) in vec3 vertexTan;
layout (location=5) in vec3 vertexBiTan;



	out vec3 surfaceWorldPos;
	out vec3 surfaceNormal;
	out vec2 texCoord;
	out mat3 TBN;




void main() 
{

	vec4 worldPos =modelMatrix * vec4(vertexPos, 1.0);
	surfaceWorldPos = worldPos.xyz;
	texCoord = vertexTexCoord;

	vec3 T = normalize(vec3(modelMatrix * vec4(vertexTan, 0.0)));
	vec3 B = normalize(vec3(modelMatrix * vec4(vertexBiTan, 0.0)));
	vec3 N = normalize(vec3(modelMatrix * vec4(vertexNormal, 0.0)));
	TBN = mat3(T,B,N);

	surfaceNormal = normalize(vec3(mat3(modelMatrix) * vertexNormal));

	gl_Position = projMatrix * viewMatrix * worldPos;
	
}