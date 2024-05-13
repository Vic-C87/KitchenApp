#include "Storage.h"

namespace Organizer
{
	Storage::Storage()
		: myStorageCount(0)
	{
	}

	Storage::~Storage()
	{
	}
	void Storage::Load(const char* aPath)
	{
	}
	bool Storage::Add(Utilities::Ingredient aNewIngredient)
	{
		return false;
	}
	Utilities::Ingredient* Storage::SearchByIndex(const int anIndex)
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
	void Storage::SaveToFile(const char* aPath)
	{

	}
}