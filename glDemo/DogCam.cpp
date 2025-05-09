#include "DogCam.h"


DogCam::DogCam()
{
	m_type = "DOGCAM";
	m_theta = 0.0f;
	m_phi = 0.0f;
	m_radius = 26.0f;

	m_fovY = 55.0f;
	m_aspect = 1.0f;
	m_nearPlane = 0.1f;
	m_farPlane = 500.0f;
	cam_Speed = 5.0f;
	
	
}

DogCam::~DogCam()
{

}

void DogCam::Init(float _screenWidth, float _screenHeight, Scene* _scene)
{
	
}


void DogCam::calculateDerivedValues()
{

}

void DogCam::Tick(float _dt, float _width, float _height)
{
    
	FPCamera::Tick(_dt, _width, _height);

    
    //m_pos = m_ExampleGO.GetPosition() + glm::vec3(0.0f, 1.0f, 0.0f);
}

void DogCam::SetExampleGO(ExampleGO _exampleGO)
{
	m_ExampleGO = _exampleGO;
}

void DogCam::Move(glm::vec3 _d, float _dt)
{
	FPCamera::Move(_d, _dt);
}