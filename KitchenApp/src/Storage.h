#pragma once
#include "Ingredient.h"

namespace Organizer
{
	class Storage
	{
	public:
		Storage();
		~Storage();
		
		void Load();
		bool Add(Ingredient aNewIngredient);
		Ingredient* Search(const Product aProduct);
		Ingredient* Search(const std::string aName);
		Ingredient* Search(const unsigned int anID);
		bool Modify(Ingredient& anIngredientToChange);

	private:
		std::vector<Ingredient> myStock;
	};


}
