#include "ProductFactory.h"

namespace Organizer
{
	ProductFactory::ProductFactory()
	{
	}

	ProductFactory::~ProductFactory()
	{
	}
	void ProductFactory::Load()
	{
	}
	bool ProductFactory::Add(Product aNewProduct)
	{
		return false;
	}
	const Product ProductFactory::Search(const std::string aName) const
	{
		return Product();
	}
	const Product ProductFactory::Search(const unsigned int anID) const
	{
		return Product();
	}
	bool ProductFactory::Modify(const std::string aNamedProductToChange, Product aNewProduct)
	{
		return false;
	}
	bool ProductFactory::Modify(unsigned int anIDedProductToChange, Product aNewProduct)
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