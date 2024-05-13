#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <sstream>
#include <fstream>
#include <cassert>
#include <iostream>

#include <vector>
#include <string>
#include <string.h>

namespace Utilities
{
	enum class EAppMainState
	{

	};

	enum class EAppSecondState
	{
		StartMenu,
		CookBookSelection,
		RecipeList,
		ProductList
	};

	enum class EAppThirdState
	{
		None,
		ProductDetails,
		CreateProduct,
		EditProduct,
		CreateIngredient,
		EditIngredient
	};

	enum class EMessurement
	{
		WeightKG,
		VolumeLiter,
		PieceOne
	};

	enum class EUnitType
	{
		Gram,
		Hekto,
		Kilo,
		Pinch,
		Krm,
		Tsk,
		Msk,
		Dl,
		Liter
	};

	enum class EStorageType
	{
		Freezer,
		Refridgerator,
		DarkNCool,
		Room
	};

	enum class EDisplayLanguage
	{
		Svenska,
		English
	};

	struct Date
	{
		int Year;
		int Month;
		int Day;

		Date(int aYear, int aMonth, int aDay)
			: Year(aYear), Month(aMonth), Day(aDay)
		{}
	};

	struct Product
	{
		std::string Name;
		std::string NameEnglish;
		EStorageType StandardLocation;
		EMessurement StandardMessurement;
		int GramPerMessurement;
		unsigned int UniqueID;

		Product(std::string aName, std::string anEnglishName, EStorageType aStandardLocation, EMessurement aStandardMessurement, int aGramPerMessurement, unsigned int aUniqueID)
			:Name(aName), NameEnglish(anEnglishName), StandardLocation(aStandardLocation),
			StandardMessurement(aStandardMessurement), GramPerMessurement(aGramPerMessurement), UniqueID(aUniqueID)
		{}
	};

	struct Ingredient
	{
		Product Type;
		float Amount;
		EUnitType Unit;
	};

	inline EStorageType GetEStorageType(const std::string aStorageTypeString)
	{
		if (aStorageTypeString.compare("Freezer") == 0)
		{
			return EStorageType::Freezer;
		}
		else if (aStorageTypeString.compare("Refridgerator") == 0)
		{
			return EStorageType::Refridgerator;
		}
		else if (aStorageTypeString.compare("Dark n' Cool") == 0)
		{
			return EStorageType::DarkNCool;
		}
		else
		{
			return EStorageType::Room;
		}
	}

	inline std::string GetStorageTypeString(const EStorageType aStorageType)
	{
		switch (aStorageType)
		{
		case EStorageType::Freezer:
			return "Freezer";
			break;
		case EStorageType::Refridgerator:
			return "Refridgerator";
			break;
		case EStorageType::DarkNCool:
			return "Dark n' Cool";
			break;
		case EStorageType::Room:
			return "Room";
			break;
		default:
			return "Room";
			break;
		}
	}

	inline EMessurement GetEMessurementType(const std::string aMessurementTypeString)
	{
		if (aMessurementTypeString.compare("Weight") == 0)
		{
			return EMessurement::WeightKG;
		}
		else if (aMessurementTypeString.compare("Volume") == 0)
		{
			return EMessurement::VolumeLiter;
		}
		else
		{
			return EMessurement::PieceOne;
		}
	}

	inline std::string GetMessurementTypeString(const EMessurement aMessurementType)
	{
		switch (aMessurementType)
		{
		case EMessurement::WeightKG:
			return "Weight";
			break;
		case EMessurement::VolumeLiter:
			return "Volume";
			break;
		case EMessurement::PieceOne:
			return "Piece";
			break;
		default:
			return "Piece";
			break;
		}
	}

	inline std::string ParseFile(const char* aPath)
	{
		std::string sourceCode;
		std::string line;

		std::ifstream shaderStream(aPath);

		while (std::getline(shaderStream, line))
		{
			sourceCode += (line + "\n");
		}
		sourceCode += "\0";
		shaderStream.close();

		return sourceCode;
	}

	inline std::vector<Ingredient> ParseStorageFile(const char* aPath, int& aStorageCount)
	{
		std::vector<Ingredient> storage;
		std::string line;

		std::ifstream fileStream(aPath);

		Product* product;
		float amount;
		EUnitType unitType;


		return storage;
	}

	inline std::vector<Product> ParseProductFile(const char* aPath, int& aProductCount)
	{
		std::vector<Product> products;
		std::string line;

		std::ifstream fileStream(aPath);

		std::string name;
		std::string engName;
		EStorageType storageType;
		EMessurement messurementType;
		int gramPerMessurement;
		unsigned int uniqueID;

		std::getline(fileStream, line);

		aProductCount = static_cast<unsigned int>(std::stoul(line));

		std::getline(fileStream, line);
		while (std::getline(fileStream, line))
		{
			name = line;
			std::getline(fileStream, line);
			engName = line;
			std::getline(fileStream, line);
			storageType = GetEStorageType(line);			//EStorageType::Room;//FIX
			std::getline(fileStream, line);
			messurementType = GetEMessurementType(line);	//EMessurement::WeightKG;
			std::getline(fileStream, line);
			std::stringstream ss;
			ss << line;
			ss >> gramPerMessurement;
			std::getline(fileStream, line);
			uniqueID = static_cast<unsigned int>(std::stoul(line));
			std::getline(fileStream, line);

			Product product({ name, engName, storageType, messurementType, gramPerMessurement, uniqueID });

			products.push_back(product);
		}

		return products;
	}

	inline void SaveProductsToFile(std::vector<Product> aProductList, unsigned int aProductCount,const char* aPath)
	{
		std::ofstream write;
		write.open(aPath, std::ios::in | std::ios::trunc);
		if (write.is_open())
		{
			write << aProductCount;
			write << "\n***";
			
			for (int i = 0; i < aProductList.size(); i++)
			{
				write << "\n" + aProductList[i].Name + "\n";
				write << aProductList[i].NameEnglish + "\n";
				write << GetStorageTypeString(aProductList[i].StandardLocation) + "\n";
				write << GetMessurementTypeString(aProductList[i].StandardMessurement) + "\n";
				write << aProductList[i].GramPerMessurement;
				write << "\n";
				write << aProductList[i].UniqueID;
				write << "\n***";
			}

			write.close();
		}
		else
		{
			std::cout << "could not open file to save" << std::endl;
		}
	}
}