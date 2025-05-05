#pragma once
#include "Light.h"
#include <vector>

struct pointLight 
{
    vec3 m_pos;
    vec3 m_col;
    vec3 m_att;
};

class PointLight :
	public Light
{
public:
	PointLight();
	~PointLight();

	//load from manifest
	virtual void Load(ifstream& _file);

	void Tick(float _dt);

	void SetPointLights(unsigned int _prog, const std::vector<pointLight> _lights);

	//set render values
	virtual void SetRenderValues(unsigned int _prog);

	vec3 GetAtt() { return m_pos; }

	vec3 SetAtt(vec3 _att) { return m_att = _att; }
	

protected:
	
	vec3 m_att;
	float m_noLights;
	std::vector<pointLight> lights;
};