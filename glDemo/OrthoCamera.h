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
	float				m_theta, m_phi; // spherical coordinates theta (rotation around the x axis) and phi (rotation around the y axis).  <theta, phi> are stored in degrees.  Zero degree rotation on <theta, phi> places the camera on the +z axis.  A positive phi represents counter-clockwise rotation around the y axis in a right-hand coordinate system.  A positive theta represents a counter-clockwise rotation around the x axis in a right-handed coordinate system
	float				m_radius; // radius of the camera's spherical coordinate model.  This lies in the interval [0, +inf]
	float				m_fovY, m_aspect, m_nearPlane, m_farPlane;

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
	void Move(glm::vec3 _d);

	void setAspect(float _aspect);

	glm::mat4 viewTransform();
	glm::mat4 projectionTransform();

protected:



};