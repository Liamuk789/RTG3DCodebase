#include "FirstPersonCamera.h"




void FirstPersonCamera::calculateDerivedValues()
{

}

FirstPersonCamera::FirstPersonCamera()
{
	m_type = "FIRST";
}




FirstPersonCamera::~FirstPersonCamera()
{

}

void FirstPersonCamera::Tick(float _dt, float _width, float _height)
{
}

void FirstPersonCamera::Load(ifstream& _file)
{
}

void FirstPersonCamera::Init(float _screenWidth, float _screenHeight, Scene* _scene)
{
}

void FirstPersonCamera::SetRenderValues(unsigned int _prog)
{
}

#pragma region Accessor methods for stored values

float FirstPersonCamera::getTheta()
{
	return 0.0f;
}

float FirstPersonCamera::getPhi()
{
	return 0.0f;
}

void FirstPersonCamera::rotateCamera(float _dTheta, float _dPhi)
{
}

float FirstPersonCamera::getRadius()
{
	return 0.0f;
}

void FirstPersonCamera::scaleRadius(float _s)
{
}

void FirstPersonCamera::incrementRadius(float _i)
{
}

float FirstPersonCamera::getFovY()
{
	return 0.0f;
}

void FirstPersonCamera::setFovY(float _fovY)
{
}

float FirstPersonCamera::getAspect()
{
	return 0.0f;
}

void FirstPersonCamera::setAspect(float _aspect)
{
}

float FirstPersonCamera::getNearPlaneDistance()
{
	return 0.0f;
}

void FirstPersonCamera::setNearPlaneDistance(float _nearPlaneDistance)
{
}

float FirstPersonCamera::getFarPlaneDistance()
{
	return 0.0f;
}

void FirstPersonCamera::setFarPlaneDistance(float _farPlaneDistance)
{
}

#pragma endregion


#pragma region Accessor methods for derived values

// return the camera location in world coordinate space
//glm::vec4 ArcballCamera::getPosition() {
//
//	return cameraPos;
//}

// return a const reference to the camera's orientation matrix in world coordinate space
//glm::mat4 ArcballCamera::getOrientationBasis() {
//
//	return R;
//}

// return a const reference to the view transform matrix for the camera
glm::mat4 FirstPersonCamera::viewTransform() {

	return m_viewMatrix;
}

// return a const reference the projection transform for the camera
glm::mat4 FirstPersonCamera::projectionTransform() {

	return m_projectionMatrix;
}

#pragma endregion