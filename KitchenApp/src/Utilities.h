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

namespace Utilities
{
	enum class EAppMainState
	{
		StartMenu,
		CookBookSelection,
		RecipeList,
		ProductList
	};

	enum class EAppSecondState
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
		EStorageType Location;
		Date BestBefore;
	};

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
			storageType = EStorageType::Room;//FIX
			std::getline(fileStream, line);
			messurementType = EMessurement::WeightKG;
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
				write << "R\n";
				write << "KG\n";
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