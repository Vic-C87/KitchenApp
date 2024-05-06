#pragma once
#include "ProductFactory.h"

namespace Organizer
{
	class Storage
	{
	public:
		Storage();
		~Storage();
		
		void Load();
		bool Add(Utilities::Ingredient aNewIngredient);
		Utilities::Ingredient* Search(const Utilities::Product aProduct);
		Utilities::Ingredient* Search(const std::string aName);
		Utilities::Ingredient* Search(const unsigned int anID);
		bool Modify(Utilities::Ingredient& anIngredientToChange);

	private:
		std::vector<Utilities::Ingredient> myStock;
	};


}
