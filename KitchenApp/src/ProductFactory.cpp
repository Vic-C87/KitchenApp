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

	void ProductFactory::DisplayProductWindow(ImGuiIO& anIO, int& aSelectedProductIndex, const Utilities::WindowDimensions& aWindowDimension, Utilities::State& aState)
	{
		if (ImGui::Begin("Products"))
		{
			static bool language = GetDisplayLanguage() == Utilities::EDisplayLanguage::English;
			ImGui::Checkbox("English", &language);

			if (language)
			{
				SetDisplayLanguage(Utilities::EDisplayLanguage::English);
			}
			else
			{
				SetDisplayLanguage(Utilities::EDisplayLanguage::Svenska);
			}

			ImGui::PushItemWidth(aWindowDimension.Width * 0.25f);
			if (ImGui::BeginListBox("Products"))
			{
				switch (GetDisplayLanguage())
				{
				case Utilities::EDisplayLanguage::Svenska:
					for (int n = 0; n < GetProductCount(); n++)
					{
						const bool is_selected = (aSelectedProductIndex == n);
						if (ImGui::Selectable(SearchByIndex(n)->Name.c_str(), is_selected))
						{
							aSelectedProductIndex = n;
							aState.SetState(Utilities::EAppStates::ProductDetails, true);
						}

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					break;
				case Utilities::EDisplayLanguage::English:
					for (int n = 0; n < GetProductCount(); n++)
					{
						const bool is_selected = (aSelectedProductIndex == n);
						if (ImGui::Selectable(SearchByIndex(n)->NameEnglish.c_str(), is_selected))
						{
							aSelectedProductIndex = n;
							aState.SetState(Utilities::EAppStates::ProductDetails, true);
						}

						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					break;
				default:
					break;
				}

				ImGui::EndListBox();
			}

			if (ImGui::Button("NEW"))
			{
				aState.SetState(Utilities::EAppStates::CreateProduct, true);
			}

			ImGui::SameLine();

			if (ImGui::Button("Back To Menu"))
			{
				aState.SetMainMenu();
			}

		}
		ImGui::End();
		
	}

	void ProductFactory::CreateProductWindow(ImGuiIO& anIO, Utilities::State& aState)
	{

		bool shouldClose = false;

		if (ImGui::Begin("CreateProduct"))
		{
			ImGui::Text("Namn(Swe):\t\t\t"); ImGui::SameLine();
			ImGui::InputText("swe", myCreateProductInfo.NameField, IM_ARRAYSIZE(myCreateProductInfo.NameField));

			ImGui::Text("Name(Eng):\t\t\t"); ImGui::SameLine();
			ImGui::InputText("eng", myCreateProductInfo.NameFieldEnglish, IM_ARRAYSIZE(myCreateProductInfo.NameFieldEnglish));

			ImGui::Text("Storage:  \t\t\t"); ImGui::SameLine();
			ImGui::Combo("Storage", &myCreateProductInfo.CurrentStorageIndex, myCreateProductInfo.StorageTypes, IM_ARRAYSIZE(myCreateProductInfo.StorageTypes));

			ImGui::Text("Messurement:  \t\t"); ImGui::SameLine();
			ImGui::Combo("Messurement", &myCreateProductInfo.CurrentMessurementIndex, myCreateProductInfo.MessurementTypes, IM_ARRAYSIZE(myCreateProductInfo.MessurementTypes));

			ImGui::Text("Gram per Messurement: "); ImGui::SameLine();
			ImGui::InputInt("GperM", &myCreateProductInfo.GramPerMessurement);

			if (ImGui::Button("Create"))
			{
				//Make sure data correct!!!
				Utilities::EStorageType storage = Utilities::GetEStorageType(myCreateProductInfo.StorageTypes[myCreateProductInfo.CurrentStorageIndex]);
				Utilities::EMessurement messurement = Utilities::GetEMessurementType(myCreateProductInfo.MessurementTypes[myCreateProductInfo.CurrentMessurementIndex]);
				Utilities::Product newProduct((std::string)myCreateProductInfo.NameField, (std::string)myCreateProductInfo.NameFieldEnglish, storage, messurement, myCreateProductInfo.GramPerMessurement, 0);
				if (Add(newProduct));
				{
					shouldClose = true;
				}
			}

			ImGui::SameLine();
			if (ImGui::Button("Close"))
			{
				shouldClose = true;
			}

		}
		ImGui::End();

		if (shouldClose)
		{			
			myCreateProductInfo.Clear(); 
			aState.SetState(Utilities::EAppStates::CreateProduct, false);
		}
	}
	void ProductFactory::ProductDetailsWindow(ImGuiIO& anIO, const int anIndex, Utilities::State& aState)
	{
		bool shouldClose = false;

		if (ImGui::Begin("ProductsDetails"))
		{
			switch (GetDisplayLanguage())
			{
			case Utilities::EDisplayLanguage::Svenska:
				ImGui::Text(myProducts[anIndex].Name.c_str());
				break;
			case Utilities::EDisplayLanguage::English:
				ImGui::Text(myProducts[anIndex].NameEnglish.c_str());
				break;
			default:
				break;
			}
			ImGui::Text("Stored in :"); ImGui::SameLine();
			ImGui::Text(Utilities::GetStorageTypeString(myProducts[anIndex].StandardLocation).c_str());
			ImGui::Text("Standard messurement type:"); ImGui::SameLine();
			ImGui::Text(Utilities::GetMessurementTypeString(myProducts[anIndex].StandardMessurement).c_str());
			ImGui::Text("Weight(gram) per messurement unit:"); ImGui::SameLine();
			ImGui::Text(std::to_string(myProducts[anIndex].GramPerMessurement).c_str());
			ImGui::Text("Product ID:"); ImGui::SameLine();
			ImGui::Text(std::to_string(myProducts[anIndex].UniqueID).c_str());

			if (ImGui::Button("EditProduct"))
			{
				mySelectedEditProductId = anIndex;
				myEditProductInfo.ClearEdit(myProducts[anIndex]);
				aState.SetState(Utilities::EAppStates::EditProduct, true);
				myCurrentBackUp = myProducts[anIndex];
			}

			ImGui::SameLine();
			if (ImGui::Button("Close"))
			{
				shouldClose = true;
			}

		}
		ImGui::End();

		if (shouldClose)
		{
			aState.SetState(Utilities::EAppStates::ProductDetails, false);
		}
	}
	void ProductFactory::EditProductWindow(ImGuiIO& anIO, Utilities::State& aState)
	{
		bool shouldClose = false;

		if (ImGui::Begin("CreateProduct"))
		{
			ImGui::Text("Namn(Swe):\t\t\t"); ImGui::SameLine();
			ImGui::InputText("swe", myEditProductInfo.NameField, IM_ARRAYSIZE(myEditProductInfo.NameField));

			ImGui::Text("Name(Eng):\t\t\t"); ImGui::SameLine();
			ImGui::InputText("eng", myEditProductInfo.NameFieldEnglish, IM_ARRAYSIZE(myEditProductInfo.NameFieldEnglish));

			ImGui::Text("Storage:  \t\t\t"); ImGui::SameLine();
			ImGui::Combo("Storage", &myEditProductInfo.CurrentStorageIndex, myEditProductInfo.StorageTypes, IM_ARRAYSIZE(myEditProductInfo.StorageTypes));

			ImGui::Text("Messurement:  \t\t"); ImGui::SameLine();
			ImGui::Combo("Messurement", &myEditProductInfo.CurrentMessurementIndex, myEditProductInfo.MessurementTypes, IM_ARRAYSIZE(myEditProductInfo.MessurementTypes));

			ImGui::Text("Gram per Messurement: "); ImGui::SameLine();
			ImGui::InputInt("GperM", &myEditProductInfo.GramPerMessurement);

			if (ImGui::Button("SaveProduct"))
			{
				//Make sure data correct!!!
				Utilities::EStorageType storage = Utilities::GetEStorageType(myEditProductInfo.StorageTypes[myEditProductInfo.CurrentStorageIndex]);
				Utilities::EMessurement messurement = Utilities::GetEMessurementType(myEditProductInfo.MessurementTypes[myEditProductInfo.CurrentMessurementIndex]);
				myProducts[mySelectedEditProductId].Name = myEditProductInfo.NameField;
				myProducts[mySelectedEditProductId].NameEnglish = myEditProductInfo.NameFieldEnglish;
				myProducts[mySelectedEditProductId].StandardLocation = storage;
				myProducts[mySelectedEditProductId].StandardMessurement = messurement;
				myProducts[mySelectedEditProductId].GramPerMessurement = myEditProductInfo.GramPerMessurement;
				Utilities::Product newProduct((std::string)myCreateProductInfo.NameField, (std::string)myCreateProductInfo.NameFieldEnglish, storage, messurement, myCreateProductInfo.GramPerMessurement, 0);
				shouldClose = true;

			}

			if (ImGui::Button("UndoEditProduct"))
			{
				myProducts[mySelectedEditProductId] = myCurrentBackUp;
				myEditProductInfo.ClearEdit(myCurrentBackUp);
			}

			ImGui::SameLine();
			if (ImGui::Button("CancelEditproduct"))
			{
				myProducts[mySelectedEditProductId] = myCurrentBackUp;
				shouldClose = true;
			}

		}
		ImGui::End();

		if (shouldClose)
		{
			myCreateProductInfo.Clear();
			aState.SetState(Utilities::EAppStates::EditProduct, false);
		}
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
	std::string ProductFactory::GetProductNameList() const
	{
		std::string names = "";

		for (size_t i = 0; i < myProducts.size(); i++)
		{
			names += myProducts[i].Name;
			names += '\0';
		}

		return names;
	}

	std::string ProductFactory::GetProductName(int anID) const
	{
		return myProducts[anID].Name;
	}


}