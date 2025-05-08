#pragma once
#include "ExampleGO.h"


class AIModel;
enum class MovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Wandering :
	public ExampleGO
{

public:

	Wandering();
	~Wandering();

	void Load(ifstream& _file);

	//update _window allows for Keyboard access
	void Tick(float _dt);

	void moveDirection(std::vector<MovementDirection> allowedDirections);


	void turnPlace();



private:

	glm::vec3 movementDir;
	float m_speed;
	MovementDirection m_MoveDir;
	
};
