 #pragma once
#include "CookBook.h"

namespace Organizer
{
	class App
	{
	public:
		App();
		~App();

		bool Initialize();
		void Update();

	private:
		void DockSpace(ImGuiIO& anIO);
		void StartScreen(ImGuiIO& anIO);
		void CheckState(ImGuiIO& anIO);
		void ExecuteState(ImGuiIO& anIO, Utilities::EAppStates aStateToExecute);

	private:
		Utilities::WindowDimensions myWindowDimensions;
		std::shared_ptr<ProductFactory> myProductFactory;
		std::unique_ptr<CookBook> myCookBook;
		GLFWwindow* myWindow;

		Utilities::State myState;

		int mySelectedProductIndex = 0;
		int mySelectedRecipeIndex = 0;

	
	private:
		static void CBKeyInput(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
		static void CBWindowResize(GLFWwindow* aWindow, int aWidth, int aHeight);
		static void CBDropFile(GLFWwindow* aWindow, int aCount, const char** somePaths);
	};
}