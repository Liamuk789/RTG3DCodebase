#pragma once
#include "Light.h"


class PointLight :
	public Light
{
public:
	PointLight();
	~PointLight();

	//load from manifest
	virtual void Load(ifstream& _file);

	//set render values
	virtual void SetRenderValues(unsigned int _prog);

	

protected:
	
};