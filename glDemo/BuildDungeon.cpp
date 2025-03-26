#include "BuildDungeon.h"



BuildDungeon::BuildDungeon()
{
	
}

BuildDungeon::~BuildDungeon()
{
	
}



void BuildDungeon::Init(Scene* _scene)
{
	m_ShaderProg = scene->GetShader(m_ShaderName)->GetProg();
	m_texture = scene->GetTexture(m_TexName)->GetTexID();
	m_model = scene->GetModel(m_ModelName);
}
