#include "core.h"
#include "TorchLight.h"
#include "helper.h"
#include "stringHelp.h"

std::vector<torchLight> torchLights =
{

};


TorchLight::TorchLight()
{
	m_type = "TORCH";
	m_pos = vec3(0.0, 0.0, 0.0);
	m_col = vec3(0.0, 0.0, 1.0);
	m_att = vec3(0.0, 0.0, 0.0);
}

TorchLight::~TorchLight()
{

}

void TorchLight::Load(ifstream& _file)
{
	StringHelp::String(_file, "NAME", m_name);
	StringHelp::Float(_file, "NOLIGHTS", m_noLights);

	torchLight light;

	for (int i = 0; i < m_noLights; ++i)
	{

		StringHelp::Float3(_file, "POS", light.m_pos.x, light.m_pos.y, light.m_pos.z);
		StringHelp::Float3(_file, "COL", light.m_col.x, light.m_col.y, light.m_col.z);
		StringHelp::Float3(_file, "ATT", light.m_att.x, light.m_att.y, light.m_att.z);

		torchLights.push_back(light);
	}
}

void TorchLight::Tick(float _dt)
{

}

void TorchLight::SetPointLights(unsigned int _prog, const std::vector<torchLight> torchLights)
{
	glUseProgram(_prog);
	//Pass the number of lights
	GLint numLightsLoc = glGetUniformLocation(_prog, "numTorchLights");
	glUniform1i(numLightsLoc, static_cast<GLint>(torchLights.size()));
	//pass light info
	for (size_t i = 0; i < torchLights.size(); ++i)
	{
		std::string basename = "torchLights[" + std::to_string(i) + "].";
		GLint posLoc = glGetUniformLocation(_prog, (basename + "pntPos").c_str());
		GLint colLoc = glGetUniformLocation(_prog, (basename + "pntCol").c_str());
		GLint attLoc = glGetUniformLocation(_prog, (basename + "pntAtt").c_str());
		glUniform3fv(posLoc, 1, &torchLights[i].m_pos[0]);
		glUniform3fv(colLoc, 1, &torchLights[i].m_col[0]);
		glUniform3fv(attLoc, 1, &torchLights[i].m_att[0]);
	}

}

void TorchLight::SetRenderValues(unsigned int _prog)
{
	SetPointLights(_prog, torchLights);
}
