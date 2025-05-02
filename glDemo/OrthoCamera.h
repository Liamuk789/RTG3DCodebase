#pragma once

#include "glm/glm.hpp"  
#include "core.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "helper.h"
#include <fstream>
#include <iostream>
#include "stringHelp.h"
#include "Camera.h"

class OrthoCamera : public Camera
{

private:

	float				m_height, m_width;
	float				m_theta, m_phi;
	float				m_radius;
	float				m_fovY, m_aspect, m_nearPlane, m_farPlane;
	float				cam_Speed;

public:
	
	string m_name;

	OrthoCamera();

	OrthoCamera(string _name, float _width, float _theta, float _phi, float _radius, float _fovY, float _aspect, float _nearPlane, float _farPlane);

	void calculateDerivedValues();

	void Tick(float _dt, float _width, float _height);
	void Load(ifstream& _file) override;
	void Init(float _screenWidth, float _screenHeight, Scene* _scene)override;
	//void SetRenderValues(unsigned int _prog) override;

	void rotateCamera(float _dTheta, float _dPhi);
	void Move(glm::vec3 _d, float _dt);

	void setAspect(float _aspect);

	glm::mat4 viewTransform();
	glm::mat4 projectionTransform();

protected:



};