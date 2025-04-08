#pragma once
#include "Light.h"
//#include "LightFactory.h"

class PlaceLights : public Light
{
private:

	//BuildDungeon* dungeon;


public:

	PlaceLights(vec3 _loc, string _name);
	~PlaceLights();

	//void Load(ifstream& _file);

	//void Render();

protected:

	//std::vector<vec3> getTorchLoc();


};