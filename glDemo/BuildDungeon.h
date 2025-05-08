#pragma once
#include "ExampleGO.h"
#include "Shader.h"
#include "Texture.h"
#include "TorchLight.h"


class BuildDungeon : public ExampleGO
{
private:

   //Scene* scene;


public:

	BuildDungeon();
	~BuildDungeon();


	void Load(ifstream& _file);

    void Render();

	//BuildDungeon* GetPointer();

	vector<vec3> storeWallLocs();

	

protected:

	//string m_ShaderName = "TEXDIR";
	//string m_TexName = "WALL";
	//string m_ModelName = "CUBELOW";

	float		m_noWalls;
	float		m_noOrigin;

	std::vector<vec3>finalObjLocations;
	std::vector<vec3>finalTorchLocations;
	std::vector<vec3>finalGlassLocations;
	
	vec3		origin;
	vec3		objLocs;
	vec3		torch;

	TorchLight* torchLight = new TorchLight();

};