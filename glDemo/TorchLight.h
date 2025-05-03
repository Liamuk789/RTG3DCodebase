#pragma once
#include "PointLight.h"


class TorchLight :
	public PointLight
{
public:
	TorchLight();
	~TorchLight();

	//load from manifest
	virtual void Load(ifstream& _file);
	void Tick(float _dt);
	

protected:


};
