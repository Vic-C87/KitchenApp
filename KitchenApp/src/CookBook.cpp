#include "CookBook.h"

namespace Organizer
{
	CookBook::CookBook()
	{
	}

	CookBook::~CookBook()
	{
	}
	void CookBook::Load()
	{
	}
	bool CookBook::Add(Recipe aNewRecipe)
	{
		return false;
	}
	bool CookBook::RemoveByName(const std::string aName)
	{
		return false;
	}
	bool CookBook::RemoveByID(const int anID)
	{
		return false;
	}
	Recipe* CookBook::Search(const std::string aName)
	{
		return nullptr;
	}
	Recipe* CookBook::Search(const int anID)
	{
		return nullptr;
	}
}