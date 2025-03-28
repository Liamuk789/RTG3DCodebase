#pragma once
#include "ExampleGO.h"
#include "Scene.h"
#include "Shader.h"
#include "Texture.h"


class BuildDungeon : public ExampleGO
{
private:
    

    Scene* scene;


	

public:

	BuildDungeon();
	~BuildDungeon();

	void Load(ifstream& _file);


    void Render();

	void Init(Scene* _scene);



protected:

	string m_ShaderName = "TEXDIR";
	string m_TexName = "WALL";
	string m_ModelName = "CUBEHIGH";

	vec3		m_loc;
	vec3		m_walls;
	float		m_noWalls;

	std::vector<vec3>roomWallLocations;
	

};