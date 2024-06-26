#pragma once
#include "ProductFactory.h"

namespace Organizer
{
	class Storage
	{
	public:
		Storage();
		~Storage();
		
		void Load(const char* aPath);
		bool Add(Utilities::Ingredient aNewIngredient);
		Utilities::Ingredient* SearchByIndex(const int anIndex);
		Utilities::Ingredient* Search(const std::string aName);
		Utilities::Ingredient* Search(const unsigned int anID);
		bool Modify(Utilities::Ingredient& anIngredientToChange);

		void SaveToFile(const char* aPath);
	private:
		std::vector<Utilities::Ingredient> myStock;
		int myStorageCount;
	};


}
