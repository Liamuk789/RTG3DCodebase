#include "TorchLight.h"

TorchLight::TorchLight()
{
	m_type = "TORCH";
	m_pos = vec3(0.0, 0.0, 0.0);
	m_col = vec3(0.0, 0.0, 1.0);
	m_att = vec3(0.0, 0.0, 0.0);
	m_noTorch = 0.0f;
}

TorchLight::~TorchLight()
{

}

void TorchLight::Load(ifstream& _file)
{

}

void TorchLight::Tick(float _dt)
{

}

void TorchLight::SetRenderValues(unsigned int _prog)
{

}
