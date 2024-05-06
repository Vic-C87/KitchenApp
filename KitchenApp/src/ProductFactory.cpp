#include "ProductFactory.h"

namespace Organizer
{
	ProductFactory::ProductFactory()
	{
	}

	ProductFactory::~ProductFactory()
	{
	}
	void ProductFactory::Load(std::vector<Utilities::Product> someProducts)
	{
		for (int i = 0; i < someProducts.size(); i++)
		{
			myProducts.push_back(someProducts[i]);
		}
	}
	bool ProductFactory::Add(Utilities::Product aNewProduct)
	{
		myProducts.push_back(aNewProduct);
		return true;
	}
	const Utilities::Product* ProductFactory::Search(const std::string aName) const
	{
		return nullptr;
	}
	const Utilities::Product* ProductFactory::Search(const unsigned int anID) const
	{
		return nullptr;
	}
	bool ProductFactory::Modify(const std::string aNamedProductToChange, Utilities::Product aNewProduct)
	{
		return false;
	}
	bool ProductFactory::Modify(unsigned int anIDedProductToChange, Utilities::Product aNewProduct)
	{
		return false;
	}
	bool ProductFactory::Remove(const std::string aName)
	{
		return false;
	}
	bool ProductFactory::Remove(unsigned int anID)
	{
		return false;
	}
}