#pragma once
#include "Utilities.h"

namespace Organizer
{
	class ProductFactory
	{
	public:
		ProductFactory();
		~ProductFactory();

		void Load(const char* aPath);
		bool Add(Utilities::Product aNewProduct);
		const Utilities::Product* Search(const std::string aName) const;
		const Utilities::Product* Search(const unsigned int anID) const;
		bool Modify(const std::string aNamedProductToChange, Utilities::Product aNewProduct);
		bool Modify(unsigned int anIDedProductToChange, Utilities::Product aNewProduct);
		bool Remove(const std::string aName);
		bool Remove(unsigned int anID);

		void SaveToFile(const char* aPath);

		int GetProductCount() const;

		std::vector<Utilities::Product>& GetProductList();

	private:
		std::vector<Utilities::Product> myProducts;
		int myProductCount;
	};
}
