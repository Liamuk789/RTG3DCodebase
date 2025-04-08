#include "BuildDungeon.h"
#include "PlaceLights.h"

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

BuildDungeon::BuildDungeon()
{
   
    m_noWalls = 0.0f;
    m_noOrigin = 0.0f;
    
}

BuildDungeon::~BuildDungeon()
{
   
}

std::vector<glm::vec3> Origins =
{

};

std::vector<glm::vec3> ObjLocation =
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
            // Read all wall locations
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;


                // Add the wall location to the vector
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
            // Read all wall locations
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;


                // Add the wall location to the vector
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
            // Read all wall locations
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;

                // Add the wall location to the vector
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
            // Read all wall locations
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;

                // Add the wall location to the vector
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
            // Read all wall locations
            for (vec3 wall : ObjLocation)
            {
                vec3 newOrigin = wall + origin;

                // Add the wall location to the vector
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
            // Read all wall locations
            for (vec3 torch : ObjLocation)
            {
                vec3 newOrigin = torch + origin;

                // Add the wall location to the vector
                finalTorchLocations.push_back(newOrigin);

                vec3 lightOffset = newOrigin + glm::vec3(0.0, 1.0, 0.0);
                PlaceLights* light = new PlaceLights(lightOffset, m_name);

                
                std::cout << glm::to_string(lightOffset) << std::endl;
            }
        }
        Origins.clear();
        ObjLocation.clear();
    }

}

void BuildDungeon::Render()
{
    for (const auto& position : finalObjLocations)
    {
        
        // Create modelMatrix for position
        m_worldMatrix = glm::translate(glm::mat4(1.0f), (position));
        m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(m_scale));

        GameObject::PreRender();
        ExampleGO::Render();
    
    }

    for (const auto& position : finalTorchLocations)
    {

        // Create modelMatrix for position
        m_worldMatrix = glm::translate(glm::mat4(1.0f), (position));
        m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(m_scale));

        GameObject::PreRender();
        ExampleGO::Render();

    }

    //for (const auto& position : finalTorchLocations)
    //{
    //    
    //    // Create modelMatrix for position
    //    m_worldMatrix = glm::translate(glm::mat4(1.0f), (position));
    //    m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(m_scale));

    //    GameObject::PreRender();
    //    ExampleGO::Render();

    //}

    /*vec3* m_walls = new vec3[m_noWalls];

    for (int i = 0; i < m_noWalls; i++)
    {
        
        m_walls[i].x;
        m_walls[i].y;
        m_walls[i].z;

    }
    m_worldMatrix = glm::translate(glm::mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

    m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(1.0, 1.5, 1.0));*/


    /*m_rot += m_rot_incr;

    m_worldMatrix = glm::translate(mat4(1.0), vec3(m_pos));
    m_worldMatrix = glm::rotate(m_worldMatrix, glm::radians(m_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
    m_worldMatrix = glm::rotate(m_worldMatrix, glm::radians(m_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
    m_worldMatrix = glm::rotate(m_worldMatrix, glm::radians(m_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
    m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(m_scale));*/
}
