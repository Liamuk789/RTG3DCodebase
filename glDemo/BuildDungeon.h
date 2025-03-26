#pragma once
#include "ExampleGO.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"


class BuildDungeon : public ExampleGO
{
private:

	Scene* scene;
	Shader* shader;


public:
	BuildDungeon();
	~BuildDungeon();

	void Init(Scene* _scene);

protected:

	string m_ShaderName = "TEXDIR";
	string m_TexName = "WALL";
	string m_ModelName = "CUBEHIGH";

};