#include "Model.h"
#include "stringHelp.h"

Model::Model()
{
	m_type = "MODEL";
}

Model::~Model()
{
}

void Model::Load(ifstream& _file)
{
	StringHelp::String(_file, "NAME", m_name);
}

void Model::Render()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_LINES, m_numFaces * 3, GL_UNSIGNED_INT, (const GLvoid*)0);
}
