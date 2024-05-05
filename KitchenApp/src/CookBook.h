#pragma once
#include "Recipe.h"

namespace Organizer
{
	class CookBook
	{
	public:
		CookBook();
		~CookBook();

		void Load();

		bool Add(Recipe aNewRecipe);
		bool RemoveByName(const std::string aName);
		bool RemoveByID(const int anID);
		Recipe* Search(const std::string aName);
		Recipe* Search(const int anID);

	private:
		std::vector<Recipe> myRecipes;
	};

	
}