#include "Storage.h"

namespace Organizer
{
	Storage::Storage()
	{
	}

	Storage::~Storage()
	{
	}
	void Storage::Load()
	{
	}
	bool Storage::Add(Utilities::Ingredient aNewIngredient)
	{
		return false;
	}
	Utilities::Ingredient* Storage::Search(const Utilities::Product aProduct)
	{
		return nullptr;
	}
	Utilities::Ingredient* Storage::Search(const std::string aName)
	{
		return nullptr;
	}
	Utilities::Ingredient* Storage::Search(const unsigned int anID)
	{
		return nullptr;
	}
	bool Storage::Modify(Utilities::Ingredient& anIngredientToChange)
	{
		return false;
	}
}