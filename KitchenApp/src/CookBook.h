#pragma once
#include "Storage.h"

namespace Organizer
{
	struct CreateRecipeInfo
	{
		char NameField[32] = "";
		int Portions = 1;
		float Amount = .0f;
		const char* Units[9] { "Gram", "Hekto", "Kilo", "Nypa", "Krm", "Tsk", "Msk", "Dl", "liter" };
		char CurrentInstructionString[128] = "";
		char CurrentNoteString[128] = "";

		void Clear()
		{
			memset(NameField, 0, sizeof(NameField));
			Portions = 1;
			Amount = .0f;
			memset(CurrentInstructionString, 0, sizeof(CurrentInstructionString));
			memset(CurrentNoteString, 0, sizeof(CurrentNoteString));
		}

		void ClearEdit(Utilities::Recipe& aRecipe)
		{
			Clear();
			strcpy_s(NameField, 32, aRecipe.Name.c_str());
			Portions = aRecipe.Portions;

		}
	};

	class CookBook
	{
	public:
		CookBook(std::shared_ptr<ProductFactory> aProductFactory);
		~CookBook();

		void Load(const char* aPath);

		bool AddRecipe(Utilities::Recipe aNewRecipe);
		bool RemoveByName(const std::string aName);
		bool RemoveByID(const int anID);
		Utilities::Recipe Search(const std::string aName);
		Utilities::Recipe SearchByIndex(const int anID);

		int GetRecipeCount() const;

		void CookBookStartWindow(ImGuiIO& anIO, Utilities::State& aState);
		void DisplayRecipesWindow(ImGuiIO& anIO, int& aSelectedProductIndex, const Utilities::WindowDimensions& aWindowDimension, Utilities::State& aState);
		void CreateRecipeWindow(ImGuiIO& anIO, const Utilities::WindowDimensions& aWindowDimension, Utilities::State& aState);
		void RecipeDetailsWindow(ImGuiIO& anIO, int& aSelectedRecipeIndex, Utilities::State& aState);
		void EditRecipe(ImGuiIO& anIO, Utilities::State& aState);

		void SaveToFile(const char* aPath);


	private:
		CreateRecipeInfo myCreateRecipeInfo;
		CreateRecipeInfo myEditRecipeInfo;
		std::vector<Utilities::Recipe> myRecipes;
		int myRecipeCount;
		std::shared_ptr<ProductFactory> myProductFactory;

		int myCurrentProductIndex;
		int myCurrentEditProductIndex;
		int myCurrentMessurementIndex;
		int myCurrentEditMessurementIndex;

		int mySelecetedEditRecipeIndex;

		std::vector<Utilities::Ingredient> myCurrentIngredients;
		std::vector<std::string> myCurrentInstructions;
		std::vector<std::string> myCurrentNotes;

		Utilities::Recipe myCurrentBackUp;

	private:
		
		bool VerifyIngrdient(int& aProductIndex, float& anAmount, int& aCurrentMessurementIndex);
		void ClearLastInput();

	};

	
}