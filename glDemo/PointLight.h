#pragma once
#include "PointLight.h"
#include "DirectionLight.h"


class PointLight : public DirectionLight
{


public:
	
	PointLight();
	~PointLight();

	void Load(ifstream& _file);
	
	void SetRenderValues(unsigned int _prog);


protected:

	vec3 position;

	float distance;

	float attenuation;

};