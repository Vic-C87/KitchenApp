#pragma once
#include "Storage.h"

namespace Organizer
{
	class Recipe
	{
	public:
		Recipe(std::string aName, int anID, int anAmountOfPorions, std::vector<Utilities::Ingredient> someIngredient, std::vector<std::string> someInstruction, std::vector<std::string> someNotes);
		~Recipe();

		bool AddIngredient(Utilities::Ingredient aNewIngredient);
		bool AddInstruction(std::string aNewInstruction, int anIndexInsertPoint = -1);
		bool AddNote(std::string aNewNote);

		bool EditPortions(int anAmountOfPortions);
		bool EditIngredients(std::vector<Utilities::Ingredient> aNewIngredientsList);
		bool EditInstructions(std::vector<std::string> aNewInstructionList);
		bool EditNotes(std::vector<std::string> aNewNotesList);

	private:
		int myPortions;
		int myID;
		std::string myName;
		std::vector<Utilities::Ingredient> myIngredients;
		std::vector<std::string> myInstructions;
		std::vector<std::string> myNotes;
	};
}