#pragma once
#include "Product.h"

namespace Organizer
{
	class ProductFactory
	{
	public:
		ProductFactory();
		~ProductFactory();

		void Load();
		bool Add(Product aNewProduct);
		const Product Search(const std::string aName) const;
		const Product Search(const unsigned int anID) const;
		bool Modify(const std::string aNamedProductToChange, Product aNewProduct);
		bool Modify(unsigned int anIDedProductToChange, Product aNewProduct);
		bool Remove(const std::string aName);
		bool Remove(unsigned int anID);


	private:
		std::vector<Product> myProducts;
	};
}
