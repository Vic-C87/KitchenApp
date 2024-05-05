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
	bool Storage::Add(Ingredient aNewIngredient)
	{
		return false;
	}
	Ingredient* Storage::Search(const Product aProduct)
	{
		return nullptr;
	}
	Ingredient* Storage::Search(const std::string aName)
	{
		return nullptr;
	}
	Ingredient* Storage::Search(const unsigned int anID)
	{
		return nullptr;
	}
	bool Storage::Modify(Ingredient& anIngredientToChange)
	{
		return false;
	}
}