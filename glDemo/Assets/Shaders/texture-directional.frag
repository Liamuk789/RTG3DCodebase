#version 450 core

// Diffuse texture - directional light

// Texture sampler (for diffuse surface colour)
layout(binding = 0) uniform sampler2D texture;

// Directional light model
uniform vec3 DIRDir;
uniform vec3 DIRCol;
uniform vec3 DIRAmb;

// Point Light Model
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

	//vec3 DIRDir = normalize(vec3(0.0, 1.0, 0.0));
    //vec3 DIRCol = vec3(1.0, 1.0, 1.0);
    //vec3 DIRAmb = vec3(0.1, 0.1, 0.1);

    //vec3 PNTPosition = vec3(0.0, 1.0, 0.0);//only changes pos with this value...
    //vec3 PNTCol = vec3(1.0, 0.0, 0.0);//only changes col here
    //vec3 PNTAtt = vec3(1.0, 0.1, 0.01);//only works when hardcoded here
	
	vec3 N = normalize(inputFragment.surfaceNormal);


	//directional calcs
	float dirL = dot(N, DIRDir);
	vec4 surfaceColour = texture2D(texture, inputFragment.texCoord);
	vec3 directionalDiffuse = surfaceColour.rgb * DIRCol * dirL;
	vec3 directionalAmbient = DIRAmb;
	
	


	//fragColour = vec4(DIRAmb,1.0)+vec4(diffuseColour, 1.0);
	//fragColour = vec4(vec3(l, l, l), 1.0);
//-----------------------------------------------------------

//All seem repeatative but dont know how to calculate for each...
	
//Point light vector from surface to light------
	vec3 surfaceToLightVec = PNTPos - inputFragment.surfaceWorldPos;
	//Normalise that vector and get dot product
	vec3 surfaceToLightNormalised = normalize(surfaceToLightVec);

	//point light calcs
	float pntL = dot(N, surfaceToLightNormalised);
	float d = length(surfaceToLightVec);

	float kc = PNTAtt.x;
	float kl = PNTAtt.y;
	float kq = PNTAtt.z;

	float atten = 1.0 / (kc + (kl * d) + (kq * (d * d)));

    vec3 pointDiffuse = surfaceColour.rgb * PNTCol * pntL * atten;

    //add light information together
    vec3 finalColor = directionalAmbient + directionalDiffuse + pointDiffuse;
    fragColour = vec4(finalColor, surfaceColour.a);
	
}
