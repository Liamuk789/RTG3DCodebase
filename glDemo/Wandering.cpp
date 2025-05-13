#include "Wandering.h"

struct turningPoints
{
	glm::vec3 positions[9];
};

turningPoints tp;



Wandering::Wandering()
{
	m_type = "WANDER";
	movementDir = vec3(0.0f, 0.0f, 0.0f);
	m_rot = vec3(0.0f, 0.0f, 0.0f);
	

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
	StringHelp::Float(_file, "SPEED", m_speed);
}


void Wandering::Tick(float _dt)
{
	//Move objects
	m_pos += movementDir * _dt;

	//Face the direction they are travelling
	if (movementDir.x != 0.0f || movementDir.z != 0.0f)
	{
		m_rot.y = glm::degrees(atan2(movementDir.x, movementDir.z));
	}

	ExampleGO::Tick(_dt);

	//check for turning points
	turnPlace();
	
}

void Wandering::moveDirection(std::vector<MovementDirection> allowedDirections)
{
	int randomIndex = rand() % allowedDirections.size();
	MovementDirection chosenDirection = allowedDirections[randomIndex];
	string name = GetName();
	//show the random direction
	cout << name << " has chosen random Direction: " << randomIndex << endl;
	switch (chosenDirection)
	{
	case MovementDirection::UP:
		m_MoveDir = MovementDirection::UP;
		movementDir = vec3(0.0f, 0.0f, -m_speed);
		break;
	case MovementDirection::DOWN:
		m_MoveDir = MovementDirection::DOWN;
		movementDir = vec3(0.0f, 0.0f, m_speed);
		break;
	case MovementDirection::LEFT:
		m_MoveDir = MovementDirection::LEFT;
		movementDir = vec3(-m_speed, 0.0f, 0.0f);
		break;
	case MovementDirection::RIGHT:
		m_MoveDir = MovementDirection::RIGHT;
		movementDir = vec3(m_speed, 0.0f, 0.0f);
		break;
	default:
		std::cerr << "Invalid direction chosen!" << std::endl;
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
			//Switch would be better+++++++++++++++++++++++++++++++++++++++++++++++
			//depending on which location they are at, give available directions
			//to stop them moving out of the map.
			std::vector<MovementDirection> allowedDirections;
			if (i == 0)
			{
				allowedDirections = { MovementDirection::DOWN, MovementDirection::RIGHT };
			}
			else if (i == 1)
			{
				allowedDirections = { MovementDirection::DOWN, MovementDirection::RIGHT, MovementDirection::LEFT };
			}
			else if (i == 2)
			{
				allowedDirections = { MovementDirection::DOWN, MovementDirection::LEFT };
			}
			else if (i == 3)
			{
				allowedDirections = { MovementDirection::UP, MovementDirection::DOWN, MovementDirection::RIGHT };
			}
			else if (i == 4)
			{
				allowedDirections = { MovementDirection::UP, MovementDirection::DOWN, MovementDirection::LEFT, MovementDirection::RIGHT };
			}
			else if (i == 5)
			{
				allowedDirections = { MovementDirection::UP, MovementDirection::DOWN, MovementDirection::LEFT };
			}
			else if (i == 6)
			{
				allowedDirections = { MovementDirection::UP, MovementDirection::RIGHT };
			}
			else if (i == 7)
			{
				allowedDirections = { MovementDirection::UP, MovementDirection::LEFT, MovementDirection::RIGHT };
			}
			else if (i == 8)
			{
				allowedDirections = { MovementDirection::UP, MovementDirection::LEFT };
			}

			//get new move direction
			moveDirection(allowedDirections);

			//Break here to try and avoid multiple direction changes at once
			break;
		}
	}
}