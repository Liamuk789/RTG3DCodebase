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

	//string m_ShaderName = "TEXDIR";
	//string m_TexName = "WALL";
	//string m_ModelName = "CUBELOW";

	float		m_noWalls;
	float		m_noOrigin;

	std::vector<vec3>finalRoomWallLocations;
	std::vector<vec3>finalTorchLocations;
	vec3		origin;
	vec3		objLocs;
	

};