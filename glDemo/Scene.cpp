#include "Scene.h"
#include "GameObject.h"
#include "ExampleGO.h"
#include "CameraFactory.h"
#include "Camera.h"
#include "LightFactory.h"
#include "Light.h"
#include "ModelFactory.h"
#include "AIModel.h"
#include "Texture.h"
#include "Shader.h"
#include "GameObjectFactory.h"
#include "ArcballCamera.h"
#include "FPCamera.h"
#include "OrthoCamera.h"
#include "DogCam.h"


#include <assert.h>


Scene::Scene()
{
	
}

Scene::~Scene()
{
	//TODO: We are being really naught and not deleting everything as we finish
	//what shoudl really go here and in similar places throughout the code base?
}

//tick all my Game Objects, lights and cameras
void Scene::Update(float _dt, float _screenWidth, float _screenHeight)
{

	//update all lights
	for (list<Light*>::iterator it = m_Lights.begin(); it != m_Lights.end(); it++)
	{
		(*it)->Tick(_dt);
	}

	//update all cameras
	for (list<Camera*>::iterator it = m_Cameras.begin(); it != m_Cameras.end(); it++)
	{
		(*it)->Tick(_dt, _screenWidth, _screenHeight);
		if ((*it)->GetType() == "DOGCAM")
		{
			DogCam* dogCam = dynamic_cast<DogCam*>(*it);
			ExampleGO* exampleGO = dynamic_cast<ExampleGO*>(GetGameObject("P_ALIEN"));
			if (dogCam && exampleGO)
			{
				dogCam->SetExampleGO(*exampleGO);
				dogCam->Tick(_dt, _screenWidth, _screenHeight);
			}
		}
		
	}

	//update all GameObjects
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Tick(_dt);
	}
}


void Scene::AddGameObject(GameObject* _new)
{
	m_GameObjects.push_back(_new);
}




//I want THAT Game Object by name
GameObject* Scene::GetGameObject(string _GOName)
{
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it)->GetName() == _GOName)
		{
			return (*it);
		}
	}
	printf("Unknown Game Object NAME : %s \n", _GOName.c_str());
	assert(0);
	return nullptr;
}

Camera* Scene::GetCamera(string _camName)
{
	for (list<Camera*>::iterator it = m_Cameras.begin(); it != m_Cameras.end(); it++)
	{
		if ((*it)->GetName() == _camName)
		{
			return (*it);
		}
	}
	printf("Unknown Camera NAME : %s \n", _camName.c_str());
	assert(0);
	return nullptr;
}

Light* Scene::GetLight(string _lightName)
{
	for (list<Light*>::iterator it = m_Lights.begin(); it != m_Lights.end(); it++)
	{
		if ((*it)->GetName() == _lightName)
		{
			return (*it);
		}
	}
	printf("Unknown Light NAME : %s \n", _lightName.c_str());
	assert(0);
	return nullptr;
}

Texture* Scene::GetTexture(string _texName)
{
	for (list<Texture*>::iterator it = m_Textures.begin(); it != m_Textures.end(); it++)
	{
		if ((*it)->GetName() == _texName)
		{
			return (*it);
		}
	}
	printf("Unknown Texture NAME : %s \n", _texName.c_str());
	assert(0);
	return nullptr;
}

AIModel* Scene::GetModel(string _modelName)
{
	for (list<AIModel*>::iterator it = m_Models.begin(); it != m_Models.end(); it++)
	{
		if ((*it)->GetName() == _modelName)
		{
			return (*it);
		}
	}
	printf("Unknown Model NAME : %s \n", _modelName.c_str());
	assert(0);
	return nullptr;
}

Shader* Scene::GetShader(string _shaderName)
{
	for (list<Shader*>::iterator it = m_Shaders.begin(); it != m_Shaders.end(); it++)
	{
		if ((*it)->GetName() == _shaderName)
		{
			return (*it);
		}
	}
	printf("Unknown Shader NAME : %s \n", _shaderName.c_str());
	assert(0);
	return nullptr;
}


void Scene::Render() {

	static float elaspedTime = 0.0f;
	elaspedTime += 0.01f;


	//Render of opaque objects first
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++) 
	{
		if ((*it)->GetRP() & RP_OPAQUE) 
		{
			GLuint SP = (*it)->GetShaderProg();
			glUseProgram(SP);

			GLint timeLoc;
			Helper::SetUniformLocation(SP, "time", &timeLoc);
			glUniform1f(timeLoc, elaspedTime);


			m_useCamera->SetRenderValues(SP);
			SetShaderUniforms(SP);

			(*it)->PreRender();
			(*it)->Render();
		}
	}

	//put all transparent objects in a vector ready to sort
	std::vector<GameObject*> transparentObjects;
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++) 
	{
		if ((*it)->GetRP() & RP_TRANSPARENT) 
		{
			transparentObjects.push_back(*it);
		}
	}

	//sort all objects from furthest to closest so they render through eachother
	std::sort(transparentObjects.begin(), transparentObjects.end(), [this](GameObject* a, GameObject* b) 
		{
		glm::vec3 camPos = m_useCamera->GetPos();
		float distA = glm::length(a->GetPosition() - camPos);
		float distB = glm::length(b->GetPosition() - camPos);
		return distA > distB;
		});

	//Render of transparent objects last
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	for (GameObject* obj : transparentObjects) {
		GLuint SP = obj->GetShaderProg();
		glUseProgram(SP);

		GLint timeLoc;
		Helper::SetUniformLocation(SP, "time", &timeLoc);
		glUniform1f(timeLoc, elaspedTime);

		m_useCamera->SetRenderValues(SP);
		SetShaderUniforms(SP);

		obj->PreRender();
		obj->Render();
	}

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);
}

// Existing code...


void Scene::SetShaderUniforms(GLuint _shaderprog)
{
	//everything needs to know about all the lights
	for (list<Light*>::iterator it = m_Lights.begin(); it != m_Lights.end(); it++)
	{

		if ((*it)->GetType() == "POINT")
		{
			(*it)->SetRenderValues(_shaderprog);
		}
		else if ((*it)->GetType() == "TORCH")
		{
			(*it)->SetRenderValues(_shaderprog);
		}
		else if ((*it)->GetType() == "DIRECTIONAL")
		{
			(*it)->SetRenderValues(_shaderprog);
		}
		else if ((*it)->GetType() == "SPOT")
		{
			(*it)->SetRenderValues(_shaderprog);
		}
		else
			(*it)->SetRenderValues(_shaderprog);
	}

}

void Scene::Load(ifstream& _file)
{
	string dummy;

	//load Cameras
	_file >> dummy >> m_numCameras; _file.ignore(256, '\n');
	cout << "CAMERAS : " << m_numCameras << endl;
	for (int i = 0; i < m_numCameras; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		Camera* newCam = CameraFactory::makeNewCam(type);
		newCam->Load(_file);

		m_Cameras.push_back(newCam);

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load Lights
	_file >> dummy >> m_numLights; _file.ignore(256, '\n');
	cout << "LIGHTS : " << m_numLights << endl;
	for (int i = 0; i < m_numLights; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		Light* newLight = LightFactory::makeNewLight(type);
		newLight->Load(_file);

		m_Lights.push_back(newLight);

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load Models
	_file >> dummy >> m_numModels; _file.ignore(256, '\n');
	cout << "MODELS : " << m_numModels << endl;
	for (int i = 0; i < m_numModels; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		AIModel* newModel = ModelFactory::makeNewModel(type);
		newModel->Load(_file);

		m_Models.push_back(newModel);

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load Textures
	_file >> dummy >> m_numTextures; _file.ignore(256, '\n');
	cout << "TEXTURES : " << m_numTextures << endl;
	for (int i = 0; i < m_numTextures; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		m_Textures.push_back(new Texture(_file));

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load Shaders
	_file >> dummy >> m_numShaders; _file.ignore(256, '\n');
	cout << "SHADERS : " << m_numShaders << endl;
	for (int i = 0; i < m_numShaders; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		m_Shaders.push_back(new Shader(_file));

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}

	cout << endl << endl;

	//load GameObjects
	_file >> dummy >> m_numGameObjects; _file.ignore(256, '\n');
	cout << "GAMEOBJECTS : " << m_numGameObjects << endl;
	for (int i = 0; i < m_numGameObjects; i++)
	{
		//skip {
		_file.ignore(256, '\n');
		cout << "{\n";

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		GameObject* newGO = GameObjectFactory::makeNewGO(type);
		newGO->Load(_file);
	

		m_GameObjects.push_back(newGO);

		//skip }
		_file.ignore(256, '\n');
		cout << "}\n";
	}


	//Attempt to use the same pointer used for setting the wall locations
	//to give to the wandering objects so they would know where the walls were
	//however this is not working

	/*if (_file.eof())
	{
		wandering->setDungeonPointer(buildDungeon->GetPointer());

		
	}*/

}

void Scene::Init()
{
	//initialise all cameras
	//scene is passed down here to allow for linking of cameras to game objects
	int count = 0;
	for (list<Camera*>::iterator it = m_Cameras.begin(); it != m_Cameras.end(); ++it)
	{
		(*it)->Init(100, 100, this);// TODO: set correct screen sizes here

		//if a camera is called MAIN
		//this will be the starting camera used
		if ((*it)->GetName() == "MAIN")
		{
			m_useCamera = (*it);
			m_useCameraIndex = count;
		}
		count++;
	}

	//if no MAIN camera just use the first one
	if (!m_useCamera)
	{
		m_useCamera = (*m_Cameras.begin());
		m_useCameraIndex = 0;
	}

	//buildDungeon = new BuildDungeon(this);

	//set up links between everything and GameObjects
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Init(this);
	}
}

//also part of trying to getbuild dungeon pointer to send to wandering
//void Scene::getDungeonPtr()
//{
//	buildDungeon->GetPointer();
//}



void Scene::changeCamera()
{
	m_useCameraIndex++;
	m_useCameraIndex = m_useCameraIndex % m_numCameras;

	auto it = m_Cameras.begin();
	std::advance(it, m_useCameraIndex);

	m_useCamera = *it;
	cout << "Camera changed to: " << m_useCamera->GetName() << endl;
}

// Modify the Scene::mouseMove method to use the window member variable
void Scene::mouseMove(float dx, float dy)
{
	if (m_useCamera)
	{
		ArcballCamera* arcballCam = dynamic_cast<ArcballCamera*>(m_useCamera);
		FPCamera* fpCam = dynamic_cast<FPCamera*>(m_useCamera);
		OrthoCamera* orthoCam = dynamic_cast<OrthoCamera*>(m_useCamera);
		if (arcballCam)
		{
			arcballCam->rotateCamera(dy, dx);
		}
		if (fpCam)
		{
			fpCam->rotateCamera(dy, dx);
		}
		if (orthoCam)
		{
			orthoCam->rotateCamera(dy, dx);
		}

	}
}

void Scene::scrollZoom(float _s)
{
	if (m_useCamera)
	{
		ArcballCamera* arcballCam = dynamic_cast<ArcballCamera*>(m_useCamera);
		OrthoCamera* orthoCam = dynamic_cast<OrthoCamera*>(m_useCamera);
		if (arcballCam)
		{
			arcballCam->scaleRadius(_s);
		}
	}
}

void Scene::moveCamera(glm::vec3 direction, float _dt)
{

	
	if (m_useCamera)
	{
		FPCamera* fpCam = dynamic_cast<FPCamera*>(m_useCamera);
		OrthoCamera* orthoCam = dynamic_cast<OrthoCamera*>(m_useCamera);
		DogCam* dogCam = dynamic_cast<DogCam*>(m_useCamera);
		if (fpCam)
		{
			fpCam->Move(direction, _dt);
		}
		if (orthoCam)
		{
			orthoCam->Move(direction, _dt);
		}
		if (dogCam)
		{
			dogCam->Move(direction, _dt);
		}
	}

}

