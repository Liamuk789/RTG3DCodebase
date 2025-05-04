#pragma once
#include "PointLight.h"


class TorchLight :
	public PointLight
{
public:

	TorchLight();
	~TorchLight();

	void Load(ifstream& _file);

	void Tick(float _dt);


	void SetRenderValues(unsigned int _prog);


protected:


};
