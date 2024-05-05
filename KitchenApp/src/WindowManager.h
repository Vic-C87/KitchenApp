#pragma once
#include "Utilities.h"
#include <iostream>


class WindowManager
{
public:
	WindowManager(const int aWidth, const int aHeight);
	~WindowManager();

	bool Initialize();

	GLFWwindow* GetWindow() const;

private:
	int myWidth;
	int myHeight;

	GLFWwindow* myWindow;
};


