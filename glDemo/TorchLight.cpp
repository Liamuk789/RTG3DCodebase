#include "core.h"
#include "TorchLight.h"
#include "helper.h"
#include "stringHelp.h"
#include <iostream>
#include <algorithm>

unsigned int m_prog = 0;

//shared ptr to hold information of torchlightobj postions
//so it can be used to place torch lights at those postions
std::shared_ptr<std::vector<torchLight>> TorchLight::globalTorchLightPos = std::make_shared<std::vector<torchLight>>();

TorchLight::TorchLight()
{
	
	m_type = "TORCH";
	//m_name = "TOR";
	m_pos = vec3(0.0, 0.0, 0.0);
	m_col = vec3(1.0, 0.6, 0.0);
	m_att = vec3(0.1, 0.1, 0.01);
}

TorchLight::~TorchLight()
{

}

void TorchLight::Load(ifstream& _file)
{
  
   StringHelp::String(_file, "NAME", m_name);
   StringHelp::Float3(_file, "POS", m_pos.x, m_pos.y, m_pos.z);
   StringHelp::Float3(_file, "COL", m_col.x, m_col.y, m_col.z);
   StringHelp::Float3(_file, "ATT", m_att.x, m_att.y, m_att.z);

  
}

void TorchLight::Tick(float _dt)  
{  
   static std::vector<float> timeAccumulators(globalTorchLightPos->size(), 0.0f);

   for (size_t i = 0; i < globalTorchLightPos->size(); ++i)
   {
	   // Update the time accumulator for the current torch
	   timeAccumulators[i] += _dt;

	   // Smooth sine wave oscillation for a natural flicker
	   float sineWave = sin(timeAccumulators[i] * 2.0f) * 0.1f; // Frequency and amplitude

	   // Random noise for abrupt flicker
	   float randomFlicker = (static_cast<float>(rand()) / RAND_MAX) * 0.2f - 0.1f;

	   // Combine sine wave and random flicker
	   float flickerEffect = sineWave + randomFlicker;

	   // Apply the flicker effect to the torchlight's color
	   (*globalTorchLightPos)[i].m_col.x = clamp((*globalTorchLightPos)[i].m_col.x + flickerEffect, 0.8f, 1.0f); // Red channel
	   (*globalTorchLightPos)[i].m_col.y = clamp((*globalTorchLightPos)[i].m_col.y + flickerEffect, 0.4f, 0.6f); // Green channel
	   (*globalTorchLightPos)[i].m_col.z = 0.0f; // Blue channel remains 0 for a fiery look
   }  
}

void TorchLight::SetLights(unsigned int _prog, const std::vector<torchLight> torchLights)
{
	glUseProgram(_prog);
	//Pass the number of lights
	GLint numLightsLoc = glGetUniformLocation(_prog, "numTorchLights");
	glUniform1i(numLightsLoc, static_cast<GLint>(torchLights.size()));
	//pass light info
	for (size_t i = 0; i < torchLights.size(); ++i)
	{
		std::string basename = "torchLights[" + std::to_string(i) + "].";
		GLint posLoc = glGetUniformLocation(_prog, (basename + "torPos").c_str());
		GLint colLoc = glGetUniformLocation(_prog, (basename + "torCol").c_str());
		GLint attLoc = glGetUniformLocation(_prog, (basename + "torAtt").c_str());
		glUniform3fv(posLoc, 1, &torchLights[i].m_pos[0]);
		glUniform3fv(colLoc, 1, &torchLights[i].m_col[0]);
		glUniform3fv(attLoc, 1, &torchLights[i].m_att[0]);
	}

}

void TorchLight::SetRenderValues(unsigned int _prog)  
{  
   //Pass in the shared pointer
	SetLights(_prog, *globalTorchLightPos);

}

void TorchLight::getTorchObjLoc(vec3 torchPos)
{
	torchLight light;
	vec3 liftLight = torchPos + vec3(-1.0, 2.0, 0.0);

	light.m_pos = torchPos;
	light.m_col = m_col;
	light.m_att = m_att;

	globalTorchLightPos->emplace_back(light);

}
