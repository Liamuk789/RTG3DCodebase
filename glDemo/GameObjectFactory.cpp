#include "GameObjectFactory.h"
#include "GameObject.h"
#include "ExampleGO.h"
#include "Wandering.h"
#include "BuildDungeon.h"
#include <assert.h>

using std::string;

GameObject* GameObjectFactory::makeNewGO(string _type)
{
	printf("GAME OBJECT TYPE: %s \n", _type.c_str());
	if (_type == "GAME_OBJECT")
	{
		return new GameObject();
	}
	else if (_type == "EXAMPLE")
	{
		return new ExampleGO();
	}
	else if (_type == "WANDER")
	{
		return new Wandering();
	}
	else if (_type == "DUNGEON")
	{
		return new BuildDungeon();
	}
	else
	{
		printf("UNKNOWN GAME OBJECT TYPE: %s \n", _type.c_str());
		assert(0);
		return nullptr;
	}
}
