#include "core.h"
#include "PointLight.h"
#include "helper.h"
#include "stringHelp.h"




std::vector<pointLight> lights =
{
    
};



PointLight::PointLight()
{
	m_type = "POINT";
	m_pos = vec3(0.0, 0.0, 0.0);
    m_col = vec3(0.0, 0.0, 1.0);
	m_att = vec3(0.0, 0.0, 0.0);
	m_noLights = 0.0f;
}

PointLight::~PointLight()
{
    
}

void PointLight::Load(ifstream& _file)
{
    StringHelp::String(_file, "NAME", m_name);
	StringHelp::Float(_file, "NOLIGHTS", m_noLights);

    pointLight light;

    for (int i = 0; i < m_noLights; ++i)
    {

        StringHelp::Float3(_file, "POS", light.m_pos.x, light.m_pos.y, light.m_pos.z);
        StringHelp::Float3(_file, "COL", light.m_col.x, light.m_col.y, light.m_col.z);
        StringHelp::Float3(_file, "ATT", light.m_att.x, light.m_att.y, light.m_att.z);

        lights.push_back(light);
    }

}


void PointLight::Tick(float _dt)
{
    static std::vector<int> directions(lights.size(), 1);
	
    for (size_t i = 0; i < lights.size(); ++i)
    {
        bool movelights = false; // Set to true to move lights
        //movelights code
        if (movelights == true)
        {
            //// Update position based on direction
            lights[i].m_pos.z += directions[i] * 0.1f;

            // Reverse direction if boundaries are reached
            if (lights[i].m_pos.z >= 50.0f)
            {
                directions[i] = -1; // Move backward
            }
            else if (lights[i].m_pos.z <= -50.0f)
            {
                directions[i] = 1; // Move forward
            }

            // Gradually increase attenuation over time
            //lights[i].m_att.x += _dt * 0.02f; // Adjust growth rate as needed
            //lights[i].m_att.y += _dt * 0.02f;
            //lights[i].m_att.z += _dt * 0.02f;
        }
        
    }
}

void PointLight::SetLights(unsigned int _prog, const std::vector<pointLight> _lights)
{
	glUseProgram(_prog);

	//Pass the number of lights
	GLint numLightsLoc = glGetUniformLocation(_prog, "numPointLights");
	glUniform1i(numLightsLoc, static_cast<GLint>(_lights.size()));

    //pass light info
    for (size_t i = 0; i < _lights.size(); ++i)
    {
		std::string basename = "pointLights[" + std::to_string(i) + "].";

		GLint posLoc = glGetUniformLocation(_prog, (basename + "pntPos").c_str());
		GLint colLoc = glGetUniformLocation(_prog, (basename + "pntCol").c_str());
		GLint attLoc = glGetUniformLocation(_prog, (basename + "pntAtt").c_str());

		glUniform3fv(posLoc, 1, &_lights[i].m_pos[0]);
		glUniform3fv(colLoc, 1, &_lights[i].m_col[0]);
		glUniform3fv(attLoc, 1, &_lights[i].m_att[0]);
    }
	
}


void PointLight::SetRenderValues(unsigned int _prog)
{
    //GLint loc;

    //// Pass the number of lights
    //if (Helper::SetUniformLocation(_prog, "numPointLights", &loc))
    //    glUniform1i(loc, static_cast<GLint>(lights.size()));

    //// Pass each light's properties
    //for (size_t i = 0; i < lights.size(); ++i)
    //{
    //    const pointLight& light = lights[i];

    //    // Set position
    //    string posString = "pointLights[" + std::to_string(i) + "].position";
    //    if (Helper::SetUniformLocation(_prog, posString.c_str(), &loc))
    //        glUniform3fv(loc, 1, glm::value_ptr(light.m_pos));

    //    // Set color
    //    string colString = "pointLights[" + std::to_string(i) + "].color";
    //    if (Helper::SetUniformLocation(_prog, colString.c_str(), &loc))
    //        glUniform3fv(loc, 1, glm::value_ptr(light.m_col));

    //    // Set attenuation
    //    string attString = "pointLights[" + std::to_string(i) + "].attenuation";
    //    if (Helper::SetUniformLocation(_prog, attString.c_str(), &loc))
    //        glUniform3fv(loc, 1, glm::value_ptr(light.m_att));
    //}

    SetLights(_prog, lights);
}
