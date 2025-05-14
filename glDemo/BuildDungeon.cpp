#include "BuildDungeon.h"


#include <glm/gtx/string_cast.hpp>

//previous hard coded wall postions
//const std::vector<glm::vec3> bigRoomBP = 
//{
//    //bottom
//    glm::vec3(-8.0f, 0.0f, -8.0f),
//    glm::vec3(-6.0f, 0.0f, -8.0f),
//    glm::vec3(-4.0f, 0.0f, -8.0f),
//    glm::vec3(-2.0f, 0.0f, -8.0f),
//    glm::vec3(2.0f, 0.0f, -8.0f),
//    glm::vec3(4.0f, 0.0f, -8.0f),
//    glm::vec3(6.0f, 0.0f, -8.0f),
//    glm::vec3(8.0f, 0.0f, -8.0f),
//    //left
//    glm::vec3(8.0f, 0.0f, -6.0f),
//    glm::vec3(8.0f, 0.0f, -4.0f),
//    glm::vec3(8.0f, 0.0f, -2.0f),
//    glm::vec3(8.0f, 0.0f, 2.0f),
//    glm::vec3(8.0f, 0.0f, 4.0f),
//    glm::vec3(8.0f, 0.0f, 6.0f),
//    glm::vec3(8.0f, 0.0f, 8.0f),
//    //top
//    glm::vec3(6.0f, 0.0f, 8.0f),
//    glm::vec3(4.0f, 0.0f, 8.0f),
//    glm::vec3(2.0f, 0.0f, 8.0f),
//    glm::vec3(-2.0f, 0.0f, 8.0f),
//    glm::vec3(-4.0f, 0.0f, 8.0f),
//    glm::vec3(-6.0f, 0.0f, 8.0f),
//    glm::vec3(-8.0f, 0.0f, 8.0f),
//    //right
//    glm::vec3(-8.0f, 0.0f, 6.0f),
//    glm::vec3(-8.0f, 0.0f, 4.0f),
//    glm::vec3(-8.0f, 0.0f, 2.0f),
//    glm::vec3(-8.0f, 0.0f, -2.0f),
//    glm::vec3(-8.0f, 0.0f, -4.0f),
//    glm::vec3(-8.0f, 0.0f, -6.0f),
//
//};

class TorchLight;

BuildDungeon::BuildDungeon()
{

    m_noWalls = 0.0f;
    m_noOrigin = 0.0f;

}

BuildDungeon::~BuildDungeon()
{
   
}
//origin to build from list
std::vector<glm::vec3> Origins =
{

};
//wall list
std::vector<glm::vec3> ObjLocation =
{

};

//glass list
std::vector<glm::vec3> GlassLocation =
{

};

//torch object list
std::vector<glm::vec3> TorchLocation =
{

};

void BuildDungeon::Load(ifstream& _file)
{

    ExampleGO::Load(_file);
    StringHelp::Float(_file, "NOORIGINS", m_noOrigin);
    for (int i = 0; i < m_noOrigin; ++i)
    {
        StringHelp::Float3(_file, "ORIGINS", origin.x, origin.y, origin.z);
        Origins.push_back(origin);
    }

    StringHelp::Float(_file, "NOOBJ", m_noWalls);
    for (int i = 0; i < m_noWalls; ++i)
    {
        StringHelp::Float3(_file, "OBJLOC", objLocs.x, objLocs.y, objLocs.z);
        ObjLocation.push_back(objLocs);
    }
	

    if (m_name == "DUNGEONMAIN")
    {
        for (vec3 origin : Origins)
        {
            //read wall lsit
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;


                //add walls to locations
                finalObjLocations.push_back(newOrigin);
            }
        }
        Origins.clear();
        ObjLocation.clear();
    }

    if (m_name == "DUNGEONHCORRIDOR")
    {
        for (vec3 origin : Origins)
        {
            
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;


                
                finalObjLocations.push_back(newOrigin);
            }
        }
        Origins.clear();
        ObjLocation.clear();
    }


    if (m_name == "DUNGEONVCORRIDOR")
    {
        for (vec3 origin : Origins)
        {
            
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;

                
                finalObjLocations.push_back(newOrigin);
            }
        }
        Origins.clear();
        ObjLocation.clear();
    }

    if (m_name == "DUNGEONGLASSH")
    {
        for (vec3 origin : Origins)
        {
            
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;

                
                finalObjLocations.push_back(newOrigin);
            }
        }
        Origins.clear();
        ObjLocation.clear();
    }
    if (m_name == "DUNGEONGLASSV")
    {
        for (vec3 origin : Origins)
        {
            
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;

                
                finalObjLocations.push_back(newOrigin);
            }
        }
        Origins.clear();
        ObjLocation.clear();
    }

    if (m_name == "TORCH")
    {
        for (vec3 origin : Origins)
        {
            //read torch list
            for (vec3 torch : ObjLocation)
            {

                vec3 newOrigin = torch + origin;

                //place torches at locations
                finalTorchLocations.push_back(newOrigin);

                torchLight->getTorchObjLoc(newOrigin);
                

            }
        }
        Origins.clear();
        ObjLocation.clear();
    }
}

void BuildDungeon::Render()
{
    //render of walls
    for (const auto& position : finalObjLocations)
    {
        
        // Create modelMatrix for position
        m_worldMatrix = glm::translate(glm::mat4(1.0f), (position));
        m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(m_scale));

        GameObject::PreRender();
        ExampleGO::Render();
    
    }
    //render of torches
    for (const auto& position : finalTorchLocations)
    {

        // Create modelMatrix for position
        m_worldMatrix = glm::translate(glm::mat4(1.0f), (position));
        m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(m_scale));

        GameObject::PreRender();
        ExampleGO::Render();

    }

}
//old VVVVVVVVVVVVVVVVVVVVVVVVVVV
//Storing wall locations to send to wandering objects
vector<vec3> BuildDungeon::storeWallLocs()
{
    for (const auto& loc : finalObjLocations)
    {
        std::cout << "x: " << loc.x << ", y: " << loc.y << ", z: " << loc.z << std::endl;
    }
    return finalObjLocations;
}

//pointer kept being sent over as null and couldnt work out how to fix
// so just commented out for now
//BuildDungeon* BuildDungeon::GetPointer()
//{
//	if (this == nullptr)
//	{
//		std::cerr << "BuildDungeon pointer is null!" << std::endl;
//		return nullptr;
//	}
//    return this;
//}





