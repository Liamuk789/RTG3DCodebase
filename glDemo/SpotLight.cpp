#include "core.h"
#include "SpotLight.h"
#include "helper.h"
#include "stringHelp.h"


std::vector<spotLight> lights =
{

};




SpotLight::SpotLight()
{
	m_type = "SPOT";

}

SpotLight::~SpotLight()
{

}

void SpotLight::Load(ifstream& _file)
{
	StringHelp::String(_file, "NAME", m_name);
	StringHelp::Float(_file, "NOLIGHTS", m_numLights);
	for (int i = 0; i < m_numLights; ++i)
	{
		spotLight light;
		StringHelp::Float3(_file, "LIGHTPOS", light.m_spotPos.x, light.m_spotPos.y, light.m_spotPos.z);
		StringHelp::Float3(_file, "COL", light.m_spotCol.x, light.m_spotCol.y, light.m_spotCol.z);
		StringHelp::Float3(_file, "DIR", light.m_spotDirection.x, light.m_spotDirection.y, light.m_spotDirection.z);
		StringHelp::Float3(_file, "ATT", light.m_spotAtt.x, light.m_spotAtt.y, light.m_spotAtt.z);
		StringHelp::Float(_file, "CUTOFF", light.m_cutoff);
		StringHelp::Float(_file, "OUTERCUTOFF", light.m_outerCutoff);
		light.m_spotDirection = glm::normalize(light.m_spotDirection);
		light.m_cutoff = glm::cos(glm::radians(light.m_cutoff));
		light.m_outerCutoff = glm::cos(glm::radians(light.m_outerCutoff));

		lights.push_back(light);
	}
	
	

}

void SpotLight::Tick(float _dt)
{

}

void SpotLight::SetLights(unsigned int _prog, const std::vector<spotLight> _lights)
{
	glUseProgram(_prog);
	//Pass the number of lights
	GLint numLightsLoc = glGetUniformLocation(_prog, "numSpotLights");
	glUniform1i(numLightsLoc, static_cast<GLint>(_lights.size()));
	//pass light info
	for (size_t i = 0; i < _lights.size(); ++i)
	{
		std::string basename = "spotLights[" + std::to_string(i) + "].";
		GLint posLoc = glGetUniformLocation(_prog, (basename + "spotPos").c_str());
		GLint colLoc = glGetUniformLocation(_prog, (basename + "spotCol").c_str());
		GLint attLoc = glGetUniformLocation(_prog, (basename + "spotAtt").c_str());
		GLint dirLoc = glGetUniformLocation(_prog, (basename + "spotDir").c_str());
		GLint cutoffLoc = glGetUniformLocation(_prog, (basename + "spotCutoff").c_str());
		GLint outerCutoffLoc = glGetUniformLocation(_prog, (basename + "spotOuterCutoff").c_str());
		glUniform3fv(posLoc, 1, &_lights[i].m_spotPos[0]);
		glUniform3fv(colLoc, 1, &_lights[i].m_spotCol[0]);
		glUniform3fv(dirLoc, 1, &_lights[i].m_spotDirection[0]);
		glUniform3fv(attLoc, 1, &_lights[i].m_spotAtt[0]);
		glUniform1f(cutoffLoc, _lights[i].m_cutoff);
		glUniform1f(outerCutoffLoc, _lights[i].m_outerCutoff);
	}
}

void SpotLight::SetRenderValues(unsigned int _prog)
{
	SetLights(_prog, lights);
}
