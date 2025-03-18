#include "FirstPersonCamera.h"




void FirstPersonCamera::calculateDerivedValues()
{
	const float theta_ = glm::radians<float>(m_theta);
	const float phi_ = glm::radians<float>(m_phi);

	// calculate position vector
	//cameraPos = glm::vec4(sinf(phi_) * cosf(-theta_) * radius, sinf(-theta_) * radius, cosf(phi_) * cosf(-theta_) * radius, 1.0f);

	// calculate orientation basis R
	//R = glm::eulerAngleY(phi_) * glm::eulerAngleX(theta_);

	// calculate view and projection transform matrices
	m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -m_radius)) * glm::eulerAngleX(-theta_) * glm::eulerAngleY(-phi_);
	m_projectionMatrix = glm::perspective(glm::radians<float>(m_fovY), m_aspect, m_nearPlane, m_farPlane);
}

FirstPersonCamera::FirstPersonCamera()
{
	m_type = "FIRST";
	m_theta = 0.0f;
	m_phi = 0.0f;
	m_radius = 26.0f;

	m_fovY = 55.0f;
	m_aspect = 1.0f;
	m_nearPlane = 0.1f;
	m_farPlane = 500.0f;

	//F = ViewFrustum(55.0f, 1.0f, 0.1f, 500.0f);

	// calculate derived values
	calculateDerivedValues();
	//F.calculateWorldCoordPlanes(C, R);
}

FirstPersonCamera::FirstPersonCamera(string _name, float _theta, float _phi, float _radius, float _fovY, float _aspect, float _nearPlane, float _farPlane) {

	m_type = "FIRST";
	this->m_name = _name;
	this->m_theta = _theta;
	this->m_phi = _phi;
	this->m_radius = std::max<float>(0.0f, _radius);

	this->m_fovY = _fovY;
	this->m_aspect = _aspect;
	this->m_nearPlane = _nearPlane;
	this->m_farPlane = _farPlane;

	//F = ViewFrustum(init_fovy, init_aspect, init_nearPlane, init_farPlane);

	// calculate derived values
	calculateDerivedValues();
	//F.calculateWorldCoordPlanes(C, R);
}



void FirstPersonCamera::Tick(float _dt, float _width, float _height)
{
	setAspect(_width / _height);
	calculateDerivedValues();
}

void FirstPersonCamera::Load(ifstream& _file)
{
	StringHelp::String(_file, "NAME", m_name);
	StringHelp::Float3(_file, "POS", m_pos.x, m_pos.y, m_pos.z);
	StringHelp::Float3(_file, "LOOKAT", m_lookAt.x, m_lookAt.y, m_lookAt.z);
	StringHelp::Float(_file, "THETA", m_theta);
	StringHelp::Float(_file, "PHI", m_phi);
	StringHelp::Float(_file, "RADIUS", m_radius);
	StringHelp::Float(_file, "FOV", m_fov);
	StringHelp::Float(_file, "NEAR", m_near);
	StringHelp::Float(_file, "FAR", m_far);
}

void FirstPersonCamera::Init(float _screenWidth, float _screenHeight, Scene* _scene)
{
	
}

void FirstPersonCamera::SetRenderValues(unsigned int _prog)
{
	GLint loc;

	//matrix for the view transform
	if (Helper::SetUniformLocation(_prog, "viewMatrix", &loc))
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(viewTransform()));

	//matrix for the projection transform
	if (Helper::SetUniformLocation(_prog, "projMatrix", &loc))
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projectionTransform()));

	//the current camera is at this position
	if (Helper::SetUniformLocation(_prog, "camPos", &loc))
		glUniform3fv(loc, 1, glm::value_ptr(GetPos()));
}

#pragma region Accessor methods for stored values

float FirstPersonCamera::getTheta()
{
	return m_theta;
}

float FirstPersonCamera::getPhi()
{
	return m_phi;
}

void FirstPersonCamera::rotateCamera(float _dTheta, float _dPhi)
{
	m_theta += _dTheta;
	m_phi += _dPhi;

	calculateDerivedValues();
}

float FirstPersonCamera::getRadius()
{
	return m_radius;
}

void FirstPersonCamera::scaleRadius(float _s)
{
	m_radius *= _s;
	calculateDerivedValues();
}

void FirstPersonCamera::incrementRadius(float _i)
{
	m_radius = std::max<float>(m_radius + _i, 0.0f);
	calculateDerivedValues();
}

float FirstPersonCamera::getFovY()
{
	return m_fovY;
}

void FirstPersonCamera::setFovY(float _fovY)
{
	this->m_fovY = _fovY;
	calculateDerivedValues();
}

float FirstPersonCamera::getAspect()
{
	return m_aspect;
}

void FirstPersonCamera::setAspect(float _aspect)
{
	this->m_aspect = _aspect;
	calculateDerivedValues();
}

float FirstPersonCamera::getNearPlaneDistance()
{
	return m_nearPlane;
}

void FirstPersonCamera::setNearPlaneDistance(float _nearPlaneDistance)
{
	this->m_nearPlane = _nearPlaneDistance;
	calculateDerivedValues();
}

float FirstPersonCamera::getFarPlaneDistance()
{
	return m_farPlane;
}

void FirstPersonCamera::setFarPlaneDistance(float _farPlaneDistance)
{
	this->m_farPlane = _farPlaneDistance;
	calculateDerivedValues();
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