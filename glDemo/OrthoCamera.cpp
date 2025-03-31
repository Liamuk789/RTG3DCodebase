#include "OrthoCamera.h"


void OrthoCamera::calculateDerivedValues()
{
	//locked the theta at 45 degrees
	const float theta_ = 45.0f;
	const float phi_ = glm::radians(m_phi);

	//Work out Lookat but with locked theta
	//kinda fudged
	m_pos.x = m_lookAt.x + m_radius * sinf(phi_) * cosf(theta_);
	m_pos.y = m_lookAt.y + m_radius * sinf(theta_);
	m_pos.z = m_lookAt.z + m_radius * cosf(phi_) * cosf(theta_);

	m_viewMatrix = glm::lookAt(m_pos, m_lookAt, glm::vec3(0, 1, 0));

	m_height = m_width / m_aspect;
	m_projectionMatrix = glm::ortho(-m_width, m_width,-m_height, m_height,m_nearPlane, m_farPlane);
}

OrthoCamera::OrthoCamera()
{
	m_type = "ORTHO";

	m_width = 10.0f;

	m_theta = 0.0f;
	m_phi = 0.0f;
	m_radius = 15.0f;

	m_fovY = 45.0f;
	m_aspect = 1.0f;
	m_nearPlane = 0.1f;
	m_farPlane = 500.0f;
	//added speed here as Ortho was movin too slow
	cam_Speed = 3.0f;

	calculateDerivedValues();
}

OrthoCamera::OrthoCamera(string _name, float _width, float _theta, float _phi, float _radius, float _fovY, float _aspect, float _nearPlane, float _farPlane) {

	m_type = "ORTHO";
	this->m_name = _name;

	this->m_width = _width;
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

void OrthoCamera::Tick(float _dt, float _width, float _height)
{
	setAspect(_width / _height);
}

void OrthoCamera::Load(ifstream& _file)
{
	StringHelp::String(_file, "NAME", m_name);
	StringHelp::Float3(_file, "POS", m_pos.x, m_pos.y, m_pos.z);
	StringHelp::Float3(_file, "LOOKAT", m_lookAt.x, m_lookAt.y, m_lookAt.z);
	StringHelp::Float(_file, "WIDTH", m_width);
	StringHelp::Float(_file, "THETA", m_theta);
	StringHelp::Float(_file, "PHI", m_phi);
	StringHelp::Float(_file, "RADIUS", m_radius);
	StringHelp::Float(_file, "FOV", m_fov);
	StringHelp::Float(_file, "NEAR", m_nearPlane);
	StringHelp::Float(_file, "FAR", m_farPlane);
}

void OrthoCamera::Init(float _screenWidth, float _screenHeight, Scene* _scene)
{

}



void OrthoCamera::rotateCamera(float _dTheta, float _dPhi)
{
	
	m_theta += _dTheta;
	m_phi += _dPhi;

	calculateDerivedValues();

}

void OrthoCamera::Move(glm::vec3 _d)
{
	//Work out right and forward directions
	glm::vec3 forward = glm::normalize(m_lookAt - m_pos);
	//stop movement along the Y
	forward.y = 0.0f; 
	forward = glm::normalize(forward);

	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

	// Move both the position and the lookAt point
	m_pos += (forward * _d.z + right * _d.x) * cam_Speed;
	m_lookAt += (forward * _d.z + right * _d.x) * cam_Speed;

	calculateDerivedValues();
}

void OrthoCamera::setAspect(float _aspect) {

	this->m_aspect = _aspect;
	calculateDerivedValues();
}


#pragma region Accessor methods for derived values

glm::mat4 OrthoCamera::viewTransform()
{
	return m_viewMatrix;
}


glm::mat4 OrthoCamera::projectionTransform()
{
	return m_projectionMatrix;
}
#pragma endregion