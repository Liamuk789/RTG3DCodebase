#include "BuildDungeon.h"


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
    m_loc = glm::vec3(0.0f,0.0f,0.0f);
    m_noWalls = 0.0f;

}

BuildDungeon::~BuildDungeon()
{
   
}

void BuildDungeon::Load(ifstream& _file)
{
    ExampleGO::Load(_file);
    StringHelp::Float(_file, "NOWALLS", m_noWalls);

    // Allocate memory for wall locations
    vec3* m_walls = new vec3(0.0, 0.0, 0.0);

    // Read all wall locations
    for (int i = 0; i < m_noWalls; ++i)
    {
        vec3 wallLocation;
        StringHelp::Float3(_file, "WALLLOC", wallLocation.x, wallLocation.y, wallLocation.z);

        // Add the wall location to the vector
        roomWallLocations.push_back(wallLocation);
    }

    // Store the wall locations in a member variable if needed
    //this->m_walls = m_walls;


}

void BuildDungeon::Render()
{
    for (const auto& position : roomWallLocations)
    {

        // Create modelMatrix for position
        m_worldMatrix = glm::translate(glm::mat4(1.0f), (position));
        m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(1.0, 1.5, 1.0));

        GameObject::PreRender();
        ExampleGO::Render();
    
    }

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

void BuildDungeon::Init(Scene* _scene)
{
    m_ShaderProg = _scene->GetShader(m_ShaderName)->GetProg();
    m_texture = _scene->GetTexture(m_TexName)->GetTexID();
    m_model = _scene->GetModel(m_ModelName);
}
