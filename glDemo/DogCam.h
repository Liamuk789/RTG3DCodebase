#pragma once
#include "FPCamera.h"
#include "ExampleGO.h"

class ExampleGO;

class DogCam : public FPCamera
{

	float				m_theta, m_phi; // spherical coordinates theta (rotation around the x axis) and phi (rotation around the y axis).  <theta, phi> are stored in degrees.  Zero degree rotation on <theta, phi> places the camera on the +z axis.  A positive phi represents counter-clockwise rotation around the y axis in a right-hand coordinate system.  A positive theta represents a counter-clockwise rotation around the x axis in a right-handed coordinate system
	float				m_radius; // radius of the camera's spherical coordinate model.  This lies in the interval [0, +inf]

	// Projection / frustum values
	float				m_fovY, m_aspect, m_nearPlane, m_farPlane;
	float				cam_Speed;
	

	ExampleGO m_ExampleGO;

public:

	DogCam();
	~DogCam();

	void Init(float _screenWidth, float _screenHeight, Scene* _scene)override;

	void calculateDerivedValues();

	void Tick(float _dt, float _width, float _height)override;

	void SetExampleGO(ExampleGO _exampleGO);

	void Move(glm::vec3 _d, float _dt);
	

protected:



};