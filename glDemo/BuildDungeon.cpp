#include "BuildDungeon.h"

struct Position {
    float x, y, z;
};

const std::vector<Position> wallPositions = {
    {0.0f, 0.0f, 5.0f},
    {2.0f, 0.0f, 5.0f},
    {4.0f, 0.0f, 5.0f},
    {6.0f, 0.0f, 5.0f},
    {8.0f, 0.0f, 5.0f}
};

BuildDungeon::BuildDungeon(Scene* scene)
{
    Init(scene);
    Render();
}

BuildDungeon::~BuildDungeon()
{
   
}

void BuildDungeon::Render()
{
    for (const auto& position : wallPositions)
    {
        // Create modelMatrix for position
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
        m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(1.0, 1.5, 1.0));

        std::cout << "Position X : " << position.x << "  Position Y : " << position.y << "  Position Z : " << position.z << std::endl;

        GameObject::PreRender();

        ExampleGO::Render();
        // Render model
        // Assuming you have a method to render the model
        // renderModel(m_ModelName, m_TexName, m_ShaderName);
    }

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

    if (!m_model) {
        std::cerr << "Error: Failed to load model " << m_ModelName << std::endl;
    }
}

