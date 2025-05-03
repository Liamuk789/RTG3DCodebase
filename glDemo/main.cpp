
#include "core.h"
#include "TextureLoader.h"
#include "ArcballCamera.h"
#include "GUClock.h"
#include "PrincipleAxes.h"
#include "shader_setup.h"
#include "helper.h"
#include "AIMesh.h"
#include "Cube.h"
#include "Scene.h"


using namespace std;
using namespace glm;


#pragma region Global variables

GUClock* g_gameClock = nullptr;

// Mouse tracking
bool				g_mouseDown = false;
double				g_prevMouseX, g_prevMouseY;

//Global Game Object
Scene* g_Scene = nullptr;

// Window size
const unsigned int g_initWidth = 1024;
const unsigned int g_initHeight = 1024;

float _initWidth = g_initWidth;
float _initHeight = g_initHeight;

bool wDown = false;
bool aDown = false;
bool sDown = false;
bool dDown = false;

float tDelta = 0.0f;


struct KeyState
{
	bool forward;
	bool backward;
	bool left;
	bool right;
	bool forRight;
	bool forLeft;
	bool backRight;
	bool backLeft;

};

KeyState m_keyState;

#pragma endregion


// Function prototypes
void renderScene();
void updateScene();
void resizeWindow(GLFWwindow* _window, int _width, int _height);
void keyboardHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
void mouseMoveHandler(GLFWwindow* _window, double _xpos, double _ypos);
void mouseButtonHandler(GLFWwindow* _window, int _button, int _action, int _mods);
void mouseScrollHandler(GLFWwindow* _window, double _xoffset, double _yoffset);
void mouseEnterHandler(GLFWwindow* _window, int _entered);

KeyState updateInput(KeyState& keyState);
void getMovement(KeyState key);



int main()
{
	//
	// 1. Initialisation
	//

	g_gameClock = new GUClock();

#pragma region OpenGL and window setup

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(g_initWidth, g_initHeight, "GDV5001", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback
	glfwSetCursorPosCallback(window, mouseMoveHandler);
	glfwSetMouseButtonCallback(window, mouseButtonHandler);
	glfwSetScrollCallback(window, mouseScrollHandler);
	glfwSetCursorEnterCallback(window, mouseEnterHandler);

	// Initialise glew
	glewInit();


	// Setup window's initial size
	resizeWindow(window, g_initWidth, g_initHeight);

#pragma endregion

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black
	glClearDepth(1.0f);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	//
	//Set up Scene class
	//

	g_Scene = new Scene();

	ifstream manifest;
	manifest.open("manifest.txt");

	g_Scene->Load(manifest);
	g_Scene->Init();

	manifest.close();


	//
	// Main loop
	// 

	while (!glfwWindowShouldClose(window))
	{
		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		glfwPollEvents();					// Use this version when animating as fast as possible

		// update window title
		char timingString[256];
		sprintf_s(timingString, 256, "CIS5013: Average fps: %.0f; Average spf: %f", g_gameClock->averageFPS(), g_gameClock->averageSPF() / 1000.0f);
		glfwSetWindowTitle(window, timingString);
	}

	glfwTerminate();

	if (g_gameClock)
	{
		g_gameClock->stop();
		g_gameClock->reportTimingData();
	}

	return 0;
}


// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_Scene->Render();

}


// Function called to animate elements in the scene
void updateScene() 
{
	

	if (g_gameClock) {

		g_gameClock->tick();
		tDelta = (float)g_gameClock->gameTimeDelta();
	}

	g_Scene->Update(tDelta, _initWidth, _initHeight);
	getMovement(m_keyState);
}


#pragma region Event handler functions
//none of this is currently passed to the Game object
//probably a good idea to do that

// Function to call when window resized
void resizeWindow(GLFWwindow* _window, int _width, int _height)
{
	_initWidth = _width;
	_initHeight = _height;

	glViewport(0, 0, _width, _height);		// Draw into entire window
}


// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
	if (_action == GLFW_PRESS) {

		// check which key was pressed...
		switch (_key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(_window, true);
			break;

		case GLFW_KEY_SPACE:


			break;

		case GLFW_KEY_LEFT_SHIFT:
			
			g_Scene->changeCamera();
			break;

		case GLFW_KEY_W:
			wDown = true;
			updateInput(m_keyState);
			getMovement(m_keyState);
			break;

		case GLFW_KEY_A:
			aDown = true;
			updateInput(m_keyState);
			getMovement(m_keyState);
			break;

		case GLFW_KEY_S:
			sDown = true;
			updateInput(m_keyState);
			getMovement(m_keyState);
			break;

		case GLFW_KEY_D:
			dDown = true;
			updateInput(m_keyState);
			getMovement(m_keyState);
			break;

		default:
		{
		}
		}
	}
	else if (_action == GLFW_RELEASE) 
	{
		// handle key release events
		switch (_key)
		{
		case GLFW_KEY_W:
			wDown = false;
			updateInput(m_keyState);
			break;

		case GLFW_KEY_A:
			aDown = false;
			updateInput(m_keyState);
			break;

		case GLFW_KEY_S:
			sDown = false;
			updateInput(m_keyState);
			break;

		case GLFW_KEY_D:
			dDown = false;
			updateInput(m_keyState);
			break;

		default:
		{
		}
		}
	}
}

KeyState updateInput(KeyState& keyState)
{
	keyState.forward = wDown;
	keyState.left = aDown;
	keyState.backward = sDown;
	keyState.right = dDown;

	return keyState;
}

void getMovement(KeyState key)
{
	glm::vec3 movement(0.0f, 0.0f, 0.0f);

	if (key.forward)
	{
		movement += glm::vec3(0.0f, 0.0f, 1.0f);
	}
	if (key.left)
	{
		movement += glm::vec3(-1.0f, 0.0f, 0.0f);
	}
	if (key.backward)
	{
		movement += glm::vec3(0.0f, 0.0f, -1.0f);
	}
	if (key.right)
	{
		movement += glm::vec3(1.0f, 0.0f, 0.0f);
	}
	//normalising here as movement was not moving correctly

	if (glm::length(movement) > 0.0f)
	{
		movement = glm::normalize(movement);
	}

	g_Scene->moveCamera(movement, tDelta);
}




void mouseMoveHandler(GLFWwindow* _window, double _xpos, double _ypos) 
{

	if (g_mouseDown) {

		//float tDelta = gameClock->gameTimeDelta();

		float dx = float(_xpos - g_prevMouseX);// *360.0f * tDelta;
		float dy = float(_ypos - g_prevMouseY);// *360.0f * tDelta;


		g_Scene->mouseMove(-dx, -dy);

		g_prevMouseX = _xpos;
		g_prevMouseY = _ypos;
	}
}

void mouseButtonHandler(GLFWwindow* _window, int _button, int _action, int _mods) 
{
	if (_button == GLFW_MOUSE_BUTTON_LEFT) 
	{
		if (_action == GLFW_PRESS) 
		{
			g_mouseDown = true;
			glfwGetCursorPos(_window, &g_prevMouseX, &g_prevMouseY);
		}
		else if (_action == GLFW_RELEASE) 
		{
			g_mouseDown = false;
		}
	}
}

void mouseScrollHandler(GLFWwindow* _window, double _xoffset, double _yoffset) {


	if (g_Scene)
	{
		if (_yoffset < 0.0)
			g_Scene->scrollZoom(1.1f);
		else if (_yoffset > 0.0)
			g_Scene->scrollZoom(0.9f);
	}
	
}

void mouseEnterHandler(GLFWwindow* _window, int _entered) 
{
}

#pragma endregion