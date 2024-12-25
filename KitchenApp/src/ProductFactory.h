#pragma once
#include "Utilities.h"
//#include <memory>

namespace Organizer
{
	struct CreateProductInfo
	{
		char NameField[32] = "";
		char NameFieldEnglish[32] = "";
		int CurrentStorageIndex = -1;
		const char* StorageTypes[4]{ "Freezer", "Refridgerator", "Dark n' Cool", "Room" };
		int CurrentMessurementIndex = -1;
		const char* MessurementTypes[3]{ "Weight", "Volume", "Piece" };
		int GramPerMessurement = 1;

		void Clear()
		{
			memset(NameField, 0, sizeof(NameField));
			memset(NameFieldEnglish, 0, sizeof(NameFieldEnglish));
			CurrentStorageIndex = -1;
			CurrentMessurementIndex = -1;
			GramPerMessurement = 1;
		}

		void ClearEdit(Utilities::Product aProduct)
		{
			Clear();
			strcpy_s(NameField, 32, aProduct.Name.c_str());
			strcpy_s(NameFieldEnglish, 32, aProduct.NameEnglish.c_str());
			CurrentStorageIndex = (int)aProduct.StandardLocation;
			CurrentMessurementIndex = (int)aProduct.StandardMessurement;
			GramPerMessurement = aProduct.GramPerMessurement;
		}

	};

	class ProductFactory
	{
	public:
		ProductFactory();
		~ProductFactory();

		void Load(const char* aPath);
		bool Add(Utilities::Product aNewProduct);
		Utilities::Product* SearchByIndex(const int anIndex);
		const Utilities::Product* Search(const std::string aName) const;
		const Utilities::Product* Search(const unsigned int anID) const;
		bool Modify(const std::string aNamedProductToChange, Utilities::Product aNewProduct);
		bool Modify(unsigned int anIDedProductToChange, Utilities::Product aNewProduct);
		bool Remove(const std::string aName);
		bool Remove(unsigned int anID);

		void SaveToFile(const char* aPath);

		void DisplayProductWindow(ImGuiIO& anIO, int& aSelectedProductIndex, const Utilities::WindowDimensions& aWindowDimension, Utilities::State& aState);
		void CreateProductWindow(ImGuiIO& anIO, Utilities::State& aState);
		void ProductDetailsWindow(ImGuiIO& anIO, const int anIndex, Utilities::State& aState);
		void EditProductWindow(ImGuiIO& anIO, Utilities::State& aState);

		const Utilities::EDisplayLanguage GetDisplayLanguage() const;
		void SetDisplayLanguage(Utilities::EDisplayLanguage aLanguagechoice);
		int GetProductCount() const;

		std::string GetProductNameList() const;
		std::string GetProductName(int anID) const;


	private:
		std::vector<Utilities::Product> myProducts;
		int myProductCount;
		Utilities::EDisplayLanguage myDisplayLanguage;
		CreateProductInfo myCreateProductInfo;
		CreateProductInfo myEditProductInfo;

		int mySelectedEditProductId;

		Utilities::Product myCurrentBackUp;
	};
}
