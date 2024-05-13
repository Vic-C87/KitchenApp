#pragma once
#include "Utilities.h";
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
		void StorageScreen(ImGuiIO& anIO, int& aSelectedStorageIndex);
		void ProductScreen(ImGuiIO& anIO, int& aSelectedProductIndex);
		void CreateProductScreen(ImGuiIO& anIO);
		void ProductDetailsScreen(ImGuiIO& anIO, Utilities::Product& aProduct);

	private:
		int myWidth;
		int myHeight;

		ProductFactory* myProductFactory;
		GLFWwindow* myWindow;

		Utilities::EAppSecondState mySecondState;
		Utilities::EAppThirdState myThirdState;
	
	private:
		static void CBKeyInput(GLFWwindow* aWindow, int aKey, int aScancode, int anAction, int aMode);
		static void CBWindowResize(GLFWwindow* aWindow, int aWidth, int aHeight);
		static void CBDropFile(GLFWwindow* aWindow, int aCount, const char** somePaths);
	};
}