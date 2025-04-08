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

	vec3 GetAtt() { return m_pos; }

	vec3 SetAtt(vec3 _att) { return m_att = _att; }
	

protected:
	
	vec3 m_att;

};