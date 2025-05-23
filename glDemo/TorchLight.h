#pragma once
#include "PointLight.h"


struct torchLight
{
	vec3 m_pos;
	vec3 m_col;
	vec3 m_att;
};

class TorchLight :
	public PointLight
{

	static std::shared_ptr<std::vector<torchLight>> globalTorchLightPos;

public:

	TorchLight();
	~TorchLight();

	void Load(ifstream& _file);

	void Tick(float _dt);

	void SetLights(unsigned int _prog, const std::vector<torchLight> _lights);

	void SetRenderValues(unsigned int _prog);

	void getTorchObjLoc(vec3 torchPos);


protected:

	
};
