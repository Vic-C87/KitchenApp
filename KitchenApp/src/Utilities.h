#pragma once
#include <sstream>
#include <fstream>
#include <cassert>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <vector>
#include <string>
#include <iostream>

namespace Utilities
{
	static unsigned int ProductCount = 0;
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

	inline std::vector<Product> ParseProductFile(const char* aPath)
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

		ProductCount = static_cast<unsigned int>(std::stoul(line));

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
}