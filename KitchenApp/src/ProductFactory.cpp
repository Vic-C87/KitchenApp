#include "ProductFactory.h"

namespace Organizer
{
	ProductFactory::ProductFactory()
		: myProductCount(0)
	{
	}

	ProductFactory::~ProductFactory()
	{
	}
	void ProductFactory::Load(const char* aPath)
	{
		std::vector<Utilities::Product> products = Utilities::ParseProductFile(aPath, myProductCount);

		for (int i = 0; i < products.size(); i++)
		{
			myProducts.push_back(products[i]);
		}
	}
	bool ProductFactory::Add(Utilities::Product aNewProduct)
	{
		myProducts.push_back(aNewProduct);
		++myProductCount;
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
	void ProductFactory::SaveToFile(const char* aPath)
	{
		Utilities::SaveProductsToFile(myProducts, myProductCount, aPath);
	}
}