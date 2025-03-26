#pragma once
#include "ExampleGO.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"


class BuildDungeon : public ExampleGO
{
private:
    

    Scene* scene;

	struct Position;

	float x, y, z;

	

public:

	BuildDungeon(Scene* scene);
	~BuildDungeon();


    void Render();

	void Init(Scene* _scene);



protected:

	string m_ShaderName = "TEXDIR";
	string m_TexName = "WALL";
	string m_ModelName = "CUBEHIGH";

};