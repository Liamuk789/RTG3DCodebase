#version 450 core

// Diffuse texture - directional light

// Texture sampler (for diffuse surface colour)
layout(binding = 0) uniform sampler2D texture;

// Directional light model
uniform vec3 DIRDir;
uniform vec3 DIRCol;
uniform vec3 DIRAmb;

// Point Light Model
uniform vec3 PNTPosition;
uniform vec3 PNTColour;
uniform vec3 lightAttenuation;


in SimplePacket {
	
	vec3 surfaceWorldPos;
	vec3 surfaceNormal;
	vec2 texCoord;

} inputFragment;


layout (location=0) out vec4 fragColour;

void main(void) {

	// calculate lambertian (l) Direction Light------
	vec3 N = normalize(inputFragment.surfaceNormal);
	float l = dot(N, DIRDir);

	// Calculate directional diffuse brightness / colour for fragment
	vec4 surfaceColour = texture2D(texture, inputFragment.texCoord);
	vec3 diffuseColour = surfaceColour.rgb * DIRCol * l;


	fragColour = vec4(DIRAmb,1.0)+vec4(diffuseColour, 1.0);
	//fragColour = vec4(vec3(l, l, l), 1.0);
//-----------------------------------------------------------

//All seem repeatative but dont know how to calculate for each...
	//Point light vector from surface to light------
	vec3 surfaceToLightVec = PNTPosition - inputFragment.surfaceWorldPos;
	//Normalise that vector and get dot product
	vec3 surfaceToLightNormalised = normalize(surfaceToLightVec);
	float pntL = dot(N, surfaceToLightNormalised);

	float d = length(surfaceToLightVec);

	float kc = lightAttenuation.x;
	float kl = lightAttenuation.y;
	float kq = lightAttenuation.z;

	float atten = 1.0 / (kc + (kl * d) + (kq * d *d));

	vec4 pointSurfaceColour = texture2D(texture, inputFragment.texCoord);
    vec3 pointDiffuseColour = pointSurfaceColour.rgb * PNTColour * pntL * atten;

    //fragColour = vec4(diffuseColour, surfaceColour.a);
	
}
