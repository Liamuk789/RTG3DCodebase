#pragma once
#include "ExampleGO.h"


class AIModel;


class Wandering :
	public ExampleGO
{

public:

	Wandering();
	~Wandering();

	void Load(ifstream& _file);

	//update _window allows for Keyboard access
	void Tick(float _dt);

	void moveDirection();

	void turnPlace();


private:

	glm::vec3 m_speed;

	enum class MovementDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	MovementDirection m_state;
};
