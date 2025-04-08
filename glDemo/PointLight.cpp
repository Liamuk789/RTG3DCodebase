#include "core.h"
#include "PointLight.h"
#include "helper.h"
#include "stringHelp.h"

PointLight::PointLight()
{
	m_type = "POINT";
	m_pos = vec3(0.0, 0.0, 0.0);
	m_att = vec3(0.0, 0.0, 0.0);
}

PointLight::~PointLight()
{

}

void PointLight::Load(ifstream& _file)
{
	Light::Load(_file);
	StringHelp::Float3(_file, "ATT", m_att.x, m_att.y, m_att.z);

}

void PointLight::SetRenderValues(unsigned int _prog)
{
    Light::SetRenderValues(_prog);

    GLint loc;

    // Set position
    string posString = m_name + "Pos";
    if (Helper::SetUniformLocation(_prog, posString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_pos));

    // Set color
    string colString = m_name + "Col";
    if (Helper::SetUniformLocation(_prog, colString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_col));

    // Set attenuation
    string attString = m_name + "Att";
    if (Helper::SetUniformLocation(_prog, attString.c_str(), &loc))
        glUniform3fv(loc, 1, glm::value_ptr(m_att));
}
