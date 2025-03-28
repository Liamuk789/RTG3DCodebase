#include "FPCamera.h"


void FPCamera::calculateDerivedValues()
{
	const float theta_ = glm::radians<float>(m_theta);
	const float phi_ = glm::radians<float>(m_phi);

	// calculate view and projection transform matrices
	m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -m_radius)) * glm::eulerAngleX(-theta_) * glm::eulerAngleY(-phi_);
	m_projectionMatrix = glm::perspective(glm::radians<float>(m_fovY), m_aspect, m_nearPlane, m_farPlane);
}

FPCamera::FPCamera()
{
	m_type = "FPC";
	m_theta = 0.0f;
	m_phi = 0.0f;
	m_radius = 26.0f;

	m_fovY = 55.0f;
	m_aspect = 1.0f;
	m_nearPlane = 0.1f;
	m_farPlane = 500.0f;
	
}


void FPCamera::Tick(float _dt, float _width, float _height) 
{
	aspect_ratio = _width / _height;

	const float theta_ = glm::radians<float>(m_theta);
	const float phi_ = glm::radians<float>(m_phi);
	
	m_lookAt = m_pos + glm::vec3(sinf(phi_) * cosf(theta_), sinf(theta_), cosf(phi_) * cosf(theta_));

	m_viewMatrix = glm::lookAt(m_pos, m_lookAt, vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::radians(m_fov), aspect_ratio, m_near, m_far);
	
	
}

void FPCamera::Load(ifstream& _file)
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

void FPCamera::Init(float _screenWidth, float _screenHeight, Scene* _scene)
{

}

void FPCamera::SetRenderValues(unsigned int _prog)
{
	GLint loc;

	//matrix for the view transform
	if (Helper::SetUniformLocation(_prog, "viewMatrix", &loc))
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(GetView()));

	//matrix for the projection transform
	if (Helper::SetUniformLocation(_prog, "projMatrix", &loc))
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(GetProj()));

	//the current camera is at this position
	if (Helper::SetUniformLocation(_prog, "camPos", &loc))
		glUniform3fv(loc, 1, glm::value_ptr(GetPos()));
}


#pragma region

void FPCamera::rotateCamera(float _dTheta, float _dPhi)
{
	m_theta += _dTheta;
	m_phi += _dPhi;

	//THETA IS UP AND DOWN
	//PHI IS LEFT AND RIGHT in simple terms for my brain

	//Restricting camera so it doesnt flip
	if (m_theta > 65.0f)
		m_theta = 65.0f;
	if (m_theta < -65)
		m_theta = -65;

	calculateDerivedValues();

}

void FPCamera::Move(glm::vec3 _d) 
{
	//******Old way that the speed varied when looking up and down.....
	// 
	//Calculate right and forward directions
	//glm::vec3 forward = glm::normalize(m_lookAt - m_pos);
	//lock the y value to disable flying up
	//forward.y = 0.0f;
	

	//Work out right and forward directions
	glm::vec3 forward = glm::normalize(m_lookAt - m_pos);
	//locking the Y so the camera cannot move up or down
	forward.y = 0.0f;
	//had to normalize the forward vector again as it was effecting the camera move
	//speed depending on how high/low you were looking
	forward = glm::normalize(forward);
	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

	//Update the position
	m_pos += forward * _d.z;
	m_pos += right * _d.x;

	//Update the lookat also to keep correct direction
	m_lookAt += forward * _d.z;
	m_lookAt += right * _d.x;

	//Update the view matrix is done in Tick()
	//m_viewMatrix = glm::lookAt(m_pos, m_lookAt, glm::vec3(0, 1, 0));

	//Prints direction vectors every tick, also halves FPS
    //std::cout << "Forward vector: (" << forward.x << ", " << forward.y << ", " << forward.z << ")" << std::endl;
}

// return a const reference to the view transform matrix for the camera
glm::mat4 FPCamera::viewTransform() {

	return m_viewMatrix;
}

// return a const reference the projection transform for the camera
glm::mat4 FPCamera::projectionTransform() {

	return m_projectionMatrix;
}


#pragma endregion