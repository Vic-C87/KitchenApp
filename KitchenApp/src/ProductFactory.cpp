#include "ProductFactory.h"

namespace Organizer
{
	ProductFactory::ProductFactory()
		: myProductCount(0)
	{
		myDisplayLanguage = Utilities::EDisplayLanguage::Svenska;
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
		aNewProduct.UniqueID = myProductCount + 1;
		myProducts.push_back(aNewProduct);
		++myProductCount;
		return true;
	}
	Utilities::Product* ProductFactory::SearchByIndex(const int anIndex)
	{
		if (anIndex < myProductCount)
			return &myProducts[anIndex];
		return nullptr;
	}
	const Utilities::Product* ProductFactory::Search(const std::string aName) const
	{
		switch (myDisplayLanguage)
		{
		case Utilities::EDisplayLanguage::Svenska:
			for (int i = 0; i < myProductCount; i++)
			{
				if (aName.compare(myProducts[i].Name) == 0)
				{
					return &myProducts[i];
				}
			}
			break;
		case Utilities::EDisplayLanguage::English:
			for (int i = 0; i < myProductCount; i++)
			{
				if (aName.compare(myProducts[i].NameEnglish) == 0)
				{
					return &myProducts[i];
				}
			}
			break;
		default:
			break;
		}
		
		return nullptr;
	}

	const Utilities::Product* ProductFactory::Search(const unsigned int anID) const
	{
		for (int i = 0; i < myProductCount; i++)
		{
			if (anID == myProducts[i].UniqueID)
			{
				return &myProducts[i];
			}
		}

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
	const Utilities::EDisplayLanguage ProductFactory::GetDisplayLanguage() const
	{
		return myDisplayLanguage;
	}
	void ProductFactory::SetDisplayLanguage(Utilities::EDisplayLanguage aLanguagechoice)
	{
		myDisplayLanguage = aLanguagechoice;
	}
	int ProductFactory::GetProductCount() const
	{
		return myProductCount;
	}
}