#include "PlaceLights.h"
#include "PointLight.h"

PlaceLights::PlaceLights(vec3 _loc, string _name)
{
	m_pos = _loc;
	m_name = _name;

	if (m_name == "POINT")
	{
		//PointLight* light = new PointLight();
		//m_col = vec3(0.0, 1.0, 0.0);

		//Light* newLight = LightFactory::makeNewLight(type);

		/*Light* newLight = LightFactory::makeNewLight("POINT");
		PointLight* pointLight = dynamic_cast<PointLight*>(newLight);
		if (pointLight)
		{
			newLight->SetCol(glm::vec3(0.0, 0.0, 1.0));
			newLight->SetAmb(glm::vec3(0.1, 0.1, 0.1));
			newLight->SetPos(_loc);
			pointLight->SetAtt(glm::vec3(1.0, 0.1, 0.01));
		}*/
		/*else
		{
			std::cerr << "Error: newLight is not a PointLight!" << std::endl;
		}*/
		std::cout << "Light created at position: " << _loc.x << ", " << _loc.y << ", " << _loc.z << std::endl;
	}
}

PlaceLights::~PlaceLights()
{

}

//void PlaceLights::Load(ifstream& _file)
//{
//
//}
//
//void PlaceLights::Render()
//{
//
//}

//std::vector<vec3> PlaceLights::getTorchLoc()
//{
//	return dungeon->finalTorchLocations;
//}
