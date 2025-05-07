#include "Wandering.h"

struct turningPoints
{
	glm::vec3 positions[9];
};

turningPoints tp;



Wandering::Wandering()
{
	m_type = "WANDER";
	m_speed = vec3(0.0f, 0.0f, 10.0f);
	m_rot = vec3(0.0f, 0.0f, 0.0f);
	moveDirection();

	//adding this->m_pos.y as each gameobject has a different y position
	//due to their size.
	tp.positions[0] = vec3(-36.0f, this->m_pos.y, -36.0f);
	tp.positions[1] = vec3(0.0f, this->m_pos.y, -36.0f);
	tp.positions[2] = vec3(36.0f, this->m_pos.y, -36.0f);
	tp.positions[3] = vec3(-36.0f, this->m_pos.y, 0.0f);
	tp.positions[4] = vec3(0.0f, this->m_pos.y, 0.0f);
	tp.positions[5] = vec3(36.0f, this->m_pos.y, 0.0f);
	tp.positions[6] = vec3(-36.0f, this->m_pos.y, 36.0f);
	tp.positions[7] = vec3(0.0f, this->m_pos.y, 36.0f);
	tp.positions[8] = vec3(36.0f, this->m_pos.y, 36.0f);

}

Wandering::~Wandering()
{

}

void Wandering::Load(ifstream& _file)
{
	ExampleGO::Load(_file);
}


void Wandering::Tick(float _dt)
{
	//Move objects
	m_pos += m_speed * _dt;

	//Face the direction they are travelling
	if (m_speed.x != 0.0f || m_speed.z != 0.0f)
	{
		m_rot.y = glm::degrees(atan2(m_speed.x, m_speed.z));
	}

	ExampleGO::Tick(_dt);

	//check for turning points
	turnPlace();
	
}

void Wandering::moveDirection()
{
	//randomly choose a direction to move in
	int randomDirection = rand() % 4;
	//show the random direction
	cout << "Random Direction: " << randomDirection << endl;
	switch (randomDirection)
	{
	case 0:
		m_state = MovementDirection::UP;
		m_speed = vec3(0.0f, 0.0f, -2.5f);
		break;
	case 1:
		m_state = MovementDirection::DOWN;
		m_speed = vec3(0.0f, 0.0f, 2.5f);
		break;
	case 2:
		m_state = MovementDirection::LEFT;
		m_speed = vec3(-2.5f, 0.0f, 0.0f);
		break;
	case 3:
		m_state = MovementDirection::RIGHT;
		m_speed = vec3(2.5f, 0.0f, 0.0f);
		break;
	}
}

void Wandering::turnPlace()
{
	//threshold for checking distance
	float threshold = 0.1f;

	for (int i = 0; i < 9; ++i)
	{
		//check object postion against struct
		if (glm::distance(glm::vec2(m_pos.x, m_pos.z), glm::vec2(tp.positions[i].x, tp.positions[i].z)) < threshold)
		{	
			//get new move direction
			moveDirection();

			//Break here to try and avoid multiple direction changes at once
			break;
		}
	}
}