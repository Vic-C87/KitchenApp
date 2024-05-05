#include "WindowManager.h"

namespace Organizer
{
	WindowManager::WindowManager(const int aWidth, const int aHeight)
		: myWidth(aWidth), myHeight(aHeight), myWindow(nullptr)
	{
	
	}

	WindowManager::~WindowManager()
	{
		myWindow = nullptr;
	}

	bool WindowManager::Initialize()
	{

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		myWindow = glfwCreateWindow(myWidth, myHeight, "SPEL", NULL, NULL);
		glfwMakeContextCurrent(myWindow);

		if (myWindow == NULL)
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			glfwTerminate();
			return false;
		}

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (status == 0)
		{
			std::cout << "Failed to initialize glad!" << std::endl;
			return false;

		}

		glViewport(0, 0, myWidth, myHeight);
		return true;
	}

	GLFWwindow* WindowManager::GetWindow() const
	{
		return myWindow;
	}
}

