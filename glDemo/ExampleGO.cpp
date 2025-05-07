#include "ExampleGO.h"
#include "AIModel.h"
#include "stringHelp.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"

ExampleGO::ExampleGO()
{
	normalNeeded = false;
}

ExampleGO::~ExampleGO()
{
}

void ExampleGO::Load(ifstream& _file)
{
	GameObject::Load(_file);
	StringHelp::String(_file, "MODEL", m_ModelName);
	StringHelp::String(_file, "TEXTURE", m_TexName);
	StringHelp::String(_file, "SHADER", m_ShaderName);
	
	if (m_ShaderName == "NORM")
	{
		StringHelp::String(_file, "NORMAL", m_NormalName);
		normalNeeded = true;
	}
	else
		normalNeeded = false;

}

void ExampleGO::Tick(float _dt)
{
	GameObject::Tick(_dt);
}

void ExampleGO::PreRender()
{
	GameObject::PreRender();

	//only thing I need to do is tell the shader about my texture

	glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//TODO: this does sort of replicate stuff in the AIMesh class, could we make them more compatible.
	
	//DO NORMAL MAPS
	
	if (normalNeeded)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_normal);
	}

	if (m_RP == RP_TRANSPARENT)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glDisable(GL_BLEND);
	}


}

void ExampleGO::Render()
{
	
	m_model->Render();
	
}

void ExampleGO::Init(Scene* _scene)
{
	m_ShaderProg = _scene->GetShader(m_ShaderName)->GetProg();
	m_texture = _scene->GetTexture(m_TexName)->GetTexID();
	m_model = _scene->GetModel(m_ModelName);

	if (normalNeeded)
	{
		m_normal = _scene->GetTexture(m_NormalName)->GetTexID();
	}
	
	
}

