#include "core.h"
#include "PointLight.h"
#include "helper.h"
#include "stringHelp.h"

PointLight::PointLight()
{
	m_type = "POINT";
	m_pos = vec3(0.0, 1.0, 0.0);
	m_direction = vec3(0.0, 1.0, 0.0);
	m_constant = 1.0f;
	m_linear = 0.09f;
	m_quadratic = 0.032f;
}

PointLight::~PointLight()
{

}

void PointLight::Load(ifstream& _file)
{
	Light::Load(_file);
	StringHelp::Float3(_file, "DIR", m_direction.x, m_direction.y, m_direction.z);
	StringHelp::Float(_file, "CONS", m_constant);
	StringHelp::Float(_file, "LIN", m_linear);
	StringHelp::Float(_file, "QUAD", m_quadratic);
}

void PointLight::SetRenderValues(unsigned int _prog)
{
	Light::SetRenderValues(_prog);

	GLint loc;
	string pntString = m_name + "Pnt";//only thing I add is a direction

 	if (Helper::SetUniformLocation(_prog, pntString.c_str(), &loc))
		glUniform3fv(loc, 1, glm::value_ptr(m_direction));

	string constStr = m_name + "AttenuationConstant";
	string linearStr = m_name + "AttenuationLinear";
	string quadStr = m_name + "AttenuationQuadratic";

	if (Helper::SetUniformLocation(_prog, constStr.c_str(), &loc))
		glUniform1f(loc, m_constant);

	if (Helper::SetUniformLocation(_prog, linearStr.c_str(), &loc))
		glUniform1f(loc, m_linear);

	if (Helper::SetUniformLocation(_prog, quadStr.c_str(), &loc))
		glUniform1f(loc, m_quadratic);

}
