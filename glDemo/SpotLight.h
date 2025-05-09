#pragma once
#include "Light.h"

struct spotLight
{
	vec3 m_spotPos;
	vec3 m_spotCol;
	vec3 m_spotDirection;
	vec3 m_spotAtt;
	float m_cutoff;
	float m_outerCutoff;

};


class SpotLight : public Light
{


public:

	SpotLight();
	~SpotLight();

	void Load(ifstream& _file) override;
	void Tick(float _dt) override;
	void SetLights(unsigned int _prog, const std::vector<spotLight> _lights);
	void SetRenderValues(unsigned int _prog) override;




protected:
	float m_numLights;
	std::vector<spotLight> lights;

};
