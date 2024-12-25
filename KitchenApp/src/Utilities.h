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
#include <algorithm>
#include <map>


namespace Utilities
{
	enum class EAppStates
	{
		None,
		StartMenu,
		CookBook,
		RecipeList,
		ProductList,
		ProductDetails,
		CreateProduct,
		EditProduct,
		RecipeDetails,
		CreateRecipe,
		EditRecipe
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
		Krm,
		Pinch,
		Tsk,
		Msk,
		Dl,
		Liter,
		None
	};

	inline EUnitType GetUnitType(std::string aUnitTypeString)
	{
		std::string unitTypeToLower = aUnitTypeString;
		std::transform(unitTypeToLower.begin(), unitTypeToLower.end(), unitTypeToLower.begin(), [](unsigned char c) {return std::tolower(c); });
		if (unitTypeToLower.compare("gram") == 0)
		{
			return EUnitType::Gram;
		}
		if (unitTypeToLower.compare("hekto") == 0)
		{
			return EUnitType::Hekto;
		}
		if (unitTypeToLower.compare("kilo") == 0)
		{
			return EUnitType::Kilo;
		}
		if (unitTypeToLower.compare("pinch") == 0)
		{
			return EUnitType::Pinch;
		}
		if (unitTypeToLower.compare("krm") == 0)
		{
			return EUnitType::Krm;
		}
		if (unitTypeToLower.compare("tsk") == 0)
		{
			return EUnitType::Tsk;
		}
		if (unitTypeToLower.compare("msk") == 0)
		{
			return EUnitType::Msk;
		}
		if (unitTypeToLower.compare("dl") == 0)
		{
			return EUnitType::Dl;
		}
		if (unitTypeToLower.compare("liter") == 0)
		{
			return EUnitType::Liter;
		}

		return EUnitType::None;


	}

	inline std::string GetUnitTypeString(EUnitType aUnitType)
	{
		switch (aUnitType)
		{
		case Utilities::EUnitType::Gram:
			return "gram";
		case Utilities::EUnitType::Hekto:
			return "hekto";
		case Utilities::EUnitType::Kilo:
			return "kilo";
		case Utilities::EUnitType::Pinch:
			return "pinch";
		case Utilities::EUnitType::Krm:
			return "krm";
		case Utilities::EUnitType::Tsk:
			return "tsk";
		case Utilities::EUnitType::Msk:
			return "msk";
		case Utilities::EUnitType::Dl:
			return "dl";
		case Utilities::EUnitType::Liter:
			return "liter";
		case Utilities::EUnitType::None:
			return "piece";
		default:
			return "none";
		}

	}

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

	struct WindowDimensions
	{
		int Width;
		int Height;

		WindowDimensions(int aWidth, int aHeight)
		{
			Width = aWidth;
			Height = aHeight;
		}
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

		Product()
		{
			Name = "";
			NameEnglish = "";
			StandardLocation = EStorageType::Room;
			StandardMessurement = EMessurement::WeightKG;
			GramPerMessurement = 1;
			UniqueID = 0;
		}

		Product(std::string aName, std::string anEnglishName, EStorageType aStandardLocation, EMessurement aStandardMessurement, int aGramPerMessurement, unsigned int aUniqueID)
			:Name(aName), NameEnglish(anEnglishName), StandardLocation(aStandardLocation),
			StandardMessurement(aStandardMessurement), GramPerMessurement(aGramPerMessurement), UniqueID(aUniqueID)
		{}
	};

	struct Ingredient
	{
		unsigned int ProductID;
		std::string Name;
		float Amount;
		EUnitType Unit;

		Ingredient(unsigned int aProductID, std::string aName, float anAmount, EUnitType aUnit)
		{
			ProductID = aProductID;
			Name = aName;
			Amount = anAmount;
			Unit = aUnit;
		}
	};

	struct Recipe
	{
		std::string Name;
		int ID;
		int Portions;
		std::vector<Ingredient> Ingredients;
		std::vector<std::string> Instructions;
		std::vector<std::string> Notes;

		Recipe()
		{
			Name = "";
			ID = -1;
			Portions = 0;
		}

		Recipe(std::string aName, int anID, int aPortions, 
			std::vector<Ingredient> someIngredients, 
			std::vector<std::string> someInstructions, 
			std::vector<std::string> someNotes)
		{
			Name = aName;
			ID = anID;
			Portions = aPortions;
			Ingredients = someIngredients;
			Instructions = someInstructions;
			Notes = someNotes;
		}

		Recipe(const Recipe& aCopy)
		{
			Name = aCopy.Name;
			ID = aCopy.ID;
			Portions = aCopy.Portions;
			Ingredients = aCopy.Ingredients;
			Instructions = aCopy.Instructions;
			Notes = aCopy.Notes;
		}
	};

	struct State
	{
		std::map<EAppStates, bool> States;

		State()
		{
			SetMainMenu();
		}
		void SetState(EAppStates aStateToSet, bool aValue)
		{
			States[aStateToSet] = aValue;
		}

		bool CheckState(EAppStates aStateToCheck)
		{
			return States[aStateToCheck];
		}

		void SetMainMenu()
		{
			ResetAll();
			States[EAppStates::StartMenu] = true;
		}

		void ResetAll()
		{
			States[EAppStates::StartMenu] = false;
			States[EAppStates::CookBook] = false;
			States[EAppStates::RecipeList] = false;
			States[EAppStates::ProductList] = false;
			States[EAppStates::ProductDetails] = false;
			States[EAppStates::CreateProduct] = false;
			States[EAppStates::EditProduct] = false;
			States[EAppStates::RecipeDetails] = false;
			States[EAppStates::EditRecipe] = false;
			States[EAppStates::CreateRecipe] = false;
		}

		std::vector<EAppStates> GetActiveStates()
		{
 			std::vector<EAppStates> activeStates;

			std::map<EAppStates, bool>::iterator it = States.begin();

			while (it != States.end())
			{
				if (it->second)
				{
					activeStates.push_back(it->first);
				}
				++it;
			}

			return activeStates;
		}
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

		aProductCount = static_cast<int>(std::stoul(line)); 

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

	inline std::vector<std::string> SplitByCurlyBracers(std::string aLineToSplit)
	{
		std::vector<std::string> lines;
		std::string line;

		for (size_t i = 0; i < aLineToSplit.size(); i++)
		{
			if (aLineToSplit[i] == '{')
			{
				line = "";
			}
			else if (aLineToSplit[i] == '}')
			{
				lines.push_back(line);
			}
			else
			{
				line += aLineToSplit[i];
			}
		}

		return lines;
	}

	inline std::vector<std::string> SplitByComma(std::string aStringToSplit)
	{
		std::vector<std::string> strings;

		std::string line = "";

		for (size_t i = 0; i < aStringToSplit.size(); i++)
		{
			if (aStringToSplit[i] == ',')
			{
				strings.push_back(line);
				line = "";
			}
			else
			{
				line += aStringToSplit[i];
			}
		}

		return strings;
	}

	inline std::vector<Ingredient> ParseIngredients(std::vector<std::string> someStringsToParse)
	{
		std::vector<Ingredient> ingredients;

		for (size_t i = 0; i < someStringsToParse.size(); i++)
		{
			std::vector<std::string> splitIngredientsDetails = SplitByComma(someStringsToParse[i]);
			int id = static_cast<int>(std::stoul(splitIngredientsDetails[0]));
			std::string name = splitIngredientsDetails[1];
			float amount = std::stof(splitIngredientsDetails[2]);
			EUnitType unit = GetUnitType(splitIngredientsDetails[3]);

 			Ingredient ingredient(id, name, amount, unit);
			ingredients.push_back(ingredient);
		}
		return ingredients;
	}


	inline std::vector<Recipe> ParseRecipeFile(const char* aPath, int& aRecipetCount)
	{
		std::vector<Recipe> recipes;
		std::string line;

		std::ifstream fileStream(aPath);

		std::string name;
		int id;
		int portions;
		std::vector<Ingredient> ingredients;
		std::vector<std::string> instructions;
		std::vector<std::string> notes;

		std::getline(fileStream, line);

		aRecipetCount = static_cast<int>(std::stoul(line));

		std::getline(fileStream, line);
		while (std::getline(fileStream, line))
		{
			name = line;
			std::getline(fileStream, line);
			id = static_cast<int>(std::stoul(line)); 
			std::getline(fileStream, line);
			portions = static_cast<int>(std::stoul(line));
			std::getline(fileStream, line);
			std::vector<std::string> ingredientsLines = SplitByCurlyBracers(line);
			ingredients = ParseIngredients(ingredientsLines);
			std::getline(fileStream, line);
			instructions = SplitByComma(SplitByCurlyBracers(line)[0]);
			std::getline(fileStream, line);
			notes = SplitByComma(SplitByCurlyBracers(line)[0]); 
			std::getline(fileStream, line);
			Recipe recipe(name, id, portions, ingredients, instructions, notes);

			recipes.push_back(recipe);
		}


		return recipes;
	}



	inline std::string ParseVectorOfStringsToString(std::vector<std::string> someStrings)
	{
		std::string vectorString = "{";
		for (size_t i = 0; i < someStrings.size(); i++)
		{
			vectorString += someStrings[i] + ",";
		}
		vectorString += "}";

		return vectorString;
	}

	inline std::string ParseIngredientsToString(std::vector<Ingredient> someIngredients)
	{
		std::string ingredientsString = "";
		std::string ingredient;

		for (size_t i = 0; i < someIngredients.size(); i++)
		{
			ingredient = "{";
			ingredient += std::to_string(someIngredients[i].ProductID) + ",";
			ingredient += someIngredients[i].Name + ",";
			ingredient += std::to_string(someIngredients[i].Amount);
			ingredient += ",";
			ingredient += GetUnitTypeString(someIngredients[i].Unit) + ",";
			ingredient += "}";
			ingredientsString += ingredient;
		}

		return ingredientsString;
	}

	inline void SaveRecipesToFile(std::vector<Recipe> aRecipeList, int aRecipeCount, const char* aPath)
	{
		std::ofstream write;
		write.open(aPath, std::ios::in | std::ios::trunc);
		if (write.is_open())
		{
			write << aRecipeCount;
			write << "\n***";

			for (size_t i = 0; i < aRecipeList.size(); i++)
			{
				write << "\n" + aRecipeList[i].Name + "\n";
				write << std::to_string(aRecipeList[i].ID) + "\n";
				write << std::to_string(aRecipeList[i].Portions) + "\n";
				write << ParseIngredientsToString(aRecipeList[i].Ingredients) + "\n";
				write << ParseVectorOfStringsToString(aRecipeList[i].Instructions) + "\n";
				write << ParseVectorOfStringsToString(aRecipeList[i].Notes) + "\n";
				write << "***";
			}

			write.close();
		}
		else
		{
			std::cout << "could not open Recipes file to save" << std::endl;
		}


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
			std::cout << "could not open Product file to save" << std::endl;
		}
	}
}