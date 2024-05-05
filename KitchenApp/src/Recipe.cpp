#include "Recipe.h"

namespace Organizer
{
	Recipe::Recipe(std::string aName, int anID, int anAmountOfPorions, std::vector<Ingredient> someIngredient, std::vector<std::string> someInstruction, std::vector<std::string> someNotes)
	{
	}
	Recipe::~Recipe()
	{
	}
	bool Recipe::AddIngredient(Ingredient aNewIngredient)
	{
		return false;
	}
	bool Recipe::AddInstruction(std::string aNewInstruction, int anIndexInsertPoint)
	{
		return false;
	}
	bool Recipe::AddNote(std::string aNewNote)
	{
		return false;
	}
	bool Recipe::EditPortions(int anAmountOfPortions)
	{
		return false;
	}
	bool Recipe::EditIngredients(std::vector<Ingredient> aNewIngredientsList)
	{
		return false;
	}
	bool Recipe::EditInstructions(std::vector<std::string> aNewInstructionList)
	{
		return false;
	}
	bool Recipe::EditNotes(std::vector<std::string> aNewNotesList)
	{
		return false;
	}
}