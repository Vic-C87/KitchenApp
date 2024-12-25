#include "CookBook.h"

namespace Organizer
{
	CookBook::CookBook(std::shared_ptr<ProductFactory> aProductFactory)
		: myRecipeCount(0), myCurrentProductIndex(-1), myCurrentEditProductIndex(-1), myCurrentMessurementIndex(-1), myCurrentEditMessurementIndex(-1), mySelecetedEditRecipeIndex(-1)
	{
		myProductFactory = aProductFactory;
	}

	CookBook::~CookBook()
	{
	}

	void CookBook::Load(const char* aPath)
	{
		myRecipes = Utilities::ParseRecipeFile(aPath, myRecipeCount);
	}

	bool CookBook::AddRecipe(Utilities::Recipe aNewRecipe)
	{
		aNewRecipe.ID = myRecipeCount + 1;
		myRecipes.push_back(aNewRecipe);
		++myRecipeCount;
		return true;
	}

	bool CookBook::RemoveByName(const std::string aName)
	{
		return false;
	}
	bool CookBook::RemoveByID(const int anID)
	{
		return false;
	}
	Utilities::Recipe CookBook::Search(const std::string aName)
	{
		Utilities::Recipe recipe("null", -1, -1, { {0, "null", 1.0f, Utilities::EUnitType::Gram} }, { "NULL" }, { "NULL" });
		return recipe;
	}

	Utilities::Recipe CookBook::SearchByIndex(const int anID)
	{
		return myRecipes[anID];
	}

	int CookBook::GetRecipeCount() const
	{
		return myRecipeCount;
	}

	void CookBook::CookBookStartWindow(ImGuiIO& anIO, Utilities::State& aState)
	{
		if (ImGui::Begin("CookBook"))
		{
			if (ImGui::Button("Recipes"))
			{
				aState.SetState(Utilities::EAppStates::RecipeList, true);
			}

			if (ImGui::Button("Back To Menu"))
			{
				aState.SetMainMenu();
			}
		}
		ImGui::End();
	}

	void CookBook::DisplayRecipesWindow(ImGuiIO& anIO, int& aSelectedProductIndex, const Utilities::WindowDimensions& aWindowDimension, Utilities::State& aState)
	{
		if (ImGui::Begin("Recipes"))
		{
			ImGui::PushItemWidth(aWindowDimension.Width * 0.25f);
			if (ImGui::BeginListBox("Recipes"))
			{
				for (int n = 0; n < GetRecipeCount(); n++)
				{
					const bool is_selected = (aSelectedProductIndex == n);
					if (ImGui::Selectable(SearchByIndex(n).Name.c_str(), is_selected))
					{
						aSelectedProductIndex = n;
						aState.SetState(Utilities::EAppStates::RecipeDetails, true);
					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndListBox();
			}
			if (ImGui::Button("Back To Menu"))
			{
				aState.SetMainMenu();
			}
			if (ImGui::Button("New Recipe"))
			{
				aState.SetState(Utilities::EAppStates::CreateRecipe, true);
				myCreateRecipeInfo.Clear();
				ClearLastInput();
			}

		}
		ImGui::End();
	}

	void CookBook::CreateRecipeWindow(ImGuiIO& anIO, const Utilities::WindowDimensions& aWindowDimension, Utilities::State& aState)
	{
		bool shouldClose = false;

		if (ImGui::Begin("CreateRecipe"))
		{
			ImGui::Text("Namn(Swe):\t\t\t"); ImGui::SameLine();
			ImGui::InputText("swe", myCreateRecipeInfo.NameField, IM_ARRAYSIZE(myCreateRecipeInfo.NameField));

			ImGui::Text("Portions: "); ImGui::SameLine();
			ImGui::InputInt("portions", &myCreateRecipeInfo.Portions);
			ImGui::Separator();

			ImGui::Text("Ingredients: ");
			
			for (int i = 0; i < myCurrentIngredients.size(); i++)
			{
				ImGui::Text(myCurrentIngredients[i].Name.c_str()); 
				ImGui::SameLine();
				ImGui::Text(" : ");
				ImGui::SameLine();

				float fAmount = myCurrentIngredients[i].Amount;
				int iAmount = (int)fAmount;
				fAmount -= iAmount;
				fAmount *= 100;
				std::string temp = fAmount != .0f ? std::to_string((int)fAmount) : "00";
				std::string sAmount = std::to_string(iAmount);
				sAmount += "." + temp;

				ImGui::Text((sAmount + " " + Utilities::GetUnitTypeString(myCurrentIngredients[i].Unit)).c_str());
				ImGui::SameLine();
				std::string label = "X##" + std::to_string(i);
				if (ImGui::SmallButton(label.c_str()))
				{
					myCurrentIngredients.erase(myCurrentIngredients.begin() + i);
				}
			}
			//FIX WIDTH!!!
			ImGui::Separator();
			ImGui::Text("Add Ingredient: ");
			std::string productNames = myProductFactory->GetProductNameList();
			ImGui::Combo("IngredientSelected", &myCurrentProductIndex, productNames.data(), myProductFactory->GetProductCount());
			ImGui::Text("Amount"); ImGui::SameLine();
			ImGui::InputFloat("amount", &myCreateRecipeInfo.Amount); ImGui::SameLine();
			ImGui::Combo("MessurementSelected", &myCurrentMessurementIndex, myCreateRecipeInfo.Units, IM_ARRAYSIZE(myCreateRecipeInfo.Units));

			ImGui::Text("Add"); ImGui::SameLine();
			if (ImGui::ArrowButton("Add", ImGuiDir_Up))
			{
				if (VerifyIngrdient(myCurrentProductIndex, myCreateRecipeInfo.Amount, myCurrentMessurementIndex))
				{
					Utilities::Ingredient ingredient(myCurrentProductIndex, myProductFactory->GetProductName(myCurrentProductIndex), myCreateRecipeInfo.Amount, Utilities::GetUnitType(myCreateRecipeInfo.Units[myCurrentMessurementIndex]));
					myCurrentIngredients.push_back(ingredient);
					myCurrentProductIndex = -1;
					myCurrentMessurementIndex = -1;
					myCreateRecipeInfo.Amount = .0f;
				}
				else
				{
					//Handle missing inputs!!!
				}
			}

			if (ImGui::Button("Open ProductList"))
			{
				aState.SetState(Utilities::EAppStates::ProductList, true);
			}

			ImGui::Separator();
			ImGui::Separator();

			ImGui::Text("Instructions:");
			for (int i = 0; i < myCurrentInstructions.size(); i++)
			{
				std::string instText = std::to_string(i + 1) + ". " + myCurrentInstructions[i];
				ImGui::Text(instText.c_str());
				ImGui::SameLine();
				std::string label = "X##" + std::to_string(i);
				if (ImGui::SmallButton(label.c_str()))
				{
					myCurrentInstructions.erase(myCurrentInstructions.begin() + i);
				}
			}
			ImGui::Separator();

			ImGui::InputText("instructionsLabel", myCreateRecipeInfo.CurrentInstructionString, 128);
			if (ImGui::ArrowButton("AddInstruction", ImGuiDir_Up))
			{
				myCurrentInstructions.push_back(myCreateRecipeInfo.CurrentInstructionString);
				memset(myCreateRecipeInfo.CurrentInstructionString, 0, sizeof(myCreateRecipeInfo.CurrentInstructionString));
			}

			ImGui::Separator();
			ImGui::Separator();

			ImGui::Text("Notes:");
			for (int i = 0; i < myCurrentNotes.size(); i++)
			{
				std::string notesText = std::to_string(i + 1) + ". " + myCurrentNotes[i];
				ImGui::Text(notesText.c_str());
				ImGui::SameLine();
				std::string label = "X##" + std::to_string(i);
				if (ImGui::SmallButton(label.c_str()))
				{
					myCurrentNotes.erase(myCurrentNotes.begin() + i);
				}
			}
			ImGui::Separator();

			ImGui::InputText("notesLabel", myCreateRecipeInfo.CurrentNoteString, 128);
			if (ImGui::ArrowButton("AddNote", ImGuiDir_Up))
			{
				myCurrentNotes.push_back(myCreateRecipeInfo.CurrentNoteString);
				memset(myCreateRecipeInfo.CurrentNoteString, 0, sizeof(myCreateRecipeInfo.CurrentNoteString));
			}

			ImGui::Separator();

			if (ImGui::Button("Create"))
			{
				Utilities::Recipe recipe(myCreateRecipeInfo.NameField, ++myRecipeCount, myCreateRecipeInfo.Portions,myCurrentIngredients, myCurrentInstructions, myCurrentNotes);
				myRecipes.push_back(recipe);
				shouldClose = true;
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
			myCreateRecipeInfo.Clear();
			aState.SetState(Utilities::EAppStates::CreateRecipe, false);
		}
	}
	
	void CookBook::RecipeDetailsWindow(ImGuiIO& anIO, int& aSelectedRecipeIndex, Utilities::State& aState)
	{
		bool shouldClose = false;


		if (ImGui::Begin("RecipeDetails"))
		{
			std::string textOutput;
			ImGui::Text(myRecipes[aSelectedRecipeIndex].Name.c_str());
			textOutput = "Recipe ID: ";
			textOutput += std::to_string(myRecipes[aSelectedRecipeIndex].ID);
			ImGui::Text(textOutput.c_str());
				

			ImGui::Text("Ingredients: ");
			for (int i = 0; i < myRecipes[aSelectedRecipeIndex].Ingredients.size(); i++)
			{
				std::string ingredientText = "\t";
				std::string temp;
				float fAmount = myRecipes[aSelectedRecipeIndex].Ingredients[i].Amount;
				int iAmount = (int)fAmount;
				fAmount -= iAmount;
				fAmount *= 100;
				temp = fAmount != .0f ? std::to_string((int)fAmount) : "00";
				ingredientText += std::to_string(iAmount);
				ingredientText += "." + temp; 
				ingredientText += " " + Utilities::GetUnitTypeString(myRecipes[aSelectedRecipeIndex].Ingredients[i].Unit);
				ingredientText += " : " + myRecipes[aSelectedRecipeIndex].Ingredients[i].Name;

				ImGui::Text(ingredientText.c_str());
			}

			ImGui::Separator();
			ImGui::Text("Instructions: ");

			for (int i = 0; i < myRecipes[aSelectedRecipeIndex].Instructions.size(); i++)
			{
				std::string instructionsText = "\t" + std::to_string(i + 1) + ". ";
				instructionsText += " " + myRecipes[aSelectedRecipeIndex].Instructions[i];

				ImGui::Text(instructionsText.c_str());
			}

			ImGui::Separator();
			ImGui::Text("Notes: ");

			for (int i = 0; i < myRecipes[aSelectedRecipeIndex].Notes.size(); i++)
			{
				std::string notesText = "\t" + std::to_string(i + 1) + ". ";
				notesText += " " + myRecipes[aSelectedRecipeIndex].Notes[i];

				ImGui::Text(notesText.c_str());
			}

			if (ImGui::Button("Edit"))
			{
				aState.SetState(Utilities::EAppStates::EditRecipe, true);
				myCurrentEditProductIndex = -1;
				myCurrentEditMessurementIndex = -1;
				mySelecetedEditRecipeIndex = aSelectedRecipeIndex;
				myEditRecipeInfo.ClearEdit(myRecipes[mySelecetedEditRecipeIndex]);
				myCurrentBackUp = myRecipes[mySelecetedEditRecipeIndex];

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
			aState.SetState(Utilities::EAppStates::RecipeDetails, false);
		}
	}
	
	void CookBook::EditRecipe(ImGuiIO& anIO, Utilities::State& aState)
	{
		bool shouldClose = false;

		if (ImGui::Begin("Edit Recipe"))
		{
			ImGui::Text("Namn(Swe):\t\t\t"); ImGui::SameLine();
			ImGui::InputText("sweEdit", myEditRecipeInfo.NameField, sizeof(myEditRecipeInfo.NameField));

			ImGui::Text("Portions: "); ImGui::SameLine();
			ImGui::InputInt("portionsEdit", &myEditRecipeInfo.Portions);
			ImGui::Separator();

			ImGui::Text("Ingredients: ");

			for (int i = 0; i < myRecipes[mySelecetedEditRecipeIndex].Ingredients.size(); i++)
			{
				ImGui::Text(myRecipes[mySelecetedEditRecipeIndex].Ingredients[i].Name.c_str());
				ImGui::SameLine();
				ImGui::Text(" : ");
				ImGui::SameLine();

				float fAmount = myRecipes[mySelecetedEditRecipeIndex].Ingredients[i].Amount;
				int iAmount = (int)fAmount;
				fAmount -= iAmount;
				fAmount *= 100;
				std::string temp = fAmount != .0f ? std::to_string((int)fAmount) : "00";
				std::string sAmount = std::to_string(iAmount);
				sAmount += "." + temp;

				ImGui::Text((sAmount + " " + Utilities::GetUnitTypeString(myRecipes[mySelecetedEditRecipeIndex].Ingredients[i].Unit)).c_str());
				ImGui::SameLine();
				std::string label = "X##E" + std::to_string(i);
				if (ImGui::SmallButton(label.c_str()))
				{
					myRecipes[mySelecetedEditRecipeIndex].Ingredients.erase(myRecipes[mySelecetedEditRecipeIndex].Ingredients.begin() + i);
				}
			}
			//FIX WIDTH!!!
			ImGui::Separator();
			ImGui::Text("Add Ingredient: ");
			std::string productNames = myProductFactory->GetProductNameList();
			ImGui::Combo("NewIngredientSelected", &myCurrentEditProductIndex, productNames.data(), myProductFactory->GetProductCount());
			ImGui::Text("Amount"); ImGui::SameLine();
			ImGui::InputFloat("NewAmount", &myEditRecipeInfo.Amount); ImGui::SameLine();
			ImGui::Combo("EditMessurementSelected", &myCurrentEditMessurementIndex, myEditRecipeInfo.Units, IM_ARRAYSIZE(myEditRecipeInfo.Units));

			ImGui::Text("Add"); ImGui::SameLine();
			if (ImGui::ArrowButton("Add##Edit", ImGuiDir_Up))
			{
				if (VerifyIngrdient(myCurrentEditProductIndex, myEditRecipeInfo.Amount, myCurrentEditMessurementIndex))
				{
					Utilities::Ingredient ingredient(myCurrentEditProductIndex, myProductFactory->GetProductName(myCurrentEditProductIndex), myEditRecipeInfo.Amount, Utilities::GetUnitType(myEditRecipeInfo.Units[myCurrentEditMessurementIndex]));
					myRecipes[mySelecetedEditRecipeIndex].Ingredients.push_back(ingredient);
					myCurrentEditProductIndex = -1;
					myCurrentEditMessurementIndex = -1;
					myEditRecipeInfo.Amount = .0f;
				}
				else
				{
					//Handle missing inputs!!!
				}
			}

			if (ImGui::Button("Open the ProductList"))
			{
				aState.SetState(Utilities::EAppStates::ProductList, true);
			}

			ImGui::Separator();
			ImGui::Separator();

			ImGui::Text("Instructions:");
			for (int i = 0; i < myRecipes[mySelecetedEditRecipeIndex].Instructions.size(); i++)
			{
				std::string instText = std::to_string(i + 1) + ". " + myRecipes[mySelecetedEditRecipeIndex].Instructions[i];
				ImGui::Text(instText.c_str());
				ImGui::SameLine();
				std::string label = "X##E" + std::to_string(i);
				if (ImGui::SmallButton(label.c_str()))
				{
					myRecipes[mySelecetedEditRecipeIndex].Instructions.erase(myRecipes[mySelecetedEditRecipeIndex].Instructions.begin() + i);
				}
			}
			ImGui::Separator();

			ImGui::InputText("instructionsLabelEdit", myEditRecipeInfo.CurrentInstructionString, 128);
			if (ImGui::ArrowButton("AddInstructionEdit", ImGuiDir_Up))
			{
				myRecipes[mySelecetedEditRecipeIndex].Instructions.push_back(myEditRecipeInfo.CurrentInstructionString);
				memset(myEditRecipeInfo.CurrentInstructionString, 0, sizeof(myEditRecipeInfo.CurrentInstructionString));
			}

			ImGui::Separator();
			ImGui::Separator();

			ImGui::Text("Notes:");
			for (int i = 0; i < myRecipes[mySelecetedEditRecipeIndex].Notes.size(); i++)
			{
				std::string notesText = std::to_string(i + 1) + ". " + myRecipes[mySelecetedEditRecipeIndex].Notes[i];
				ImGui::Text(notesText.c_str());
				ImGui::SameLine();
				std::string label = "X##E" + std::to_string(i);
				if (ImGui::SmallButton(label.c_str()))
				{
					myRecipes[mySelecetedEditRecipeIndex].Notes.erase(myRecipes[mySelecetedEditRecipeIndex].Notes.begin() + i);
				}
			}
			ImGui::Separator();

			ImGui::InputText("notesLabelEdit", myEditRecipeInfo.CurrentNoteString, 128);
			if (ImGui::ArrowButton("AddNoteEdit", ImGuiDir_Up))
			{
				myRecipes[mySelecetedEditRecipeIndex].Notes.push_back(myEditRecipeInfo.CurrentNoteString);
				memset(myEditRecipeInfo.CurrentNoteString, 0, sizeof(myEditRecipeInfo.CurrentNoteString));
			}

			ImGui::Separator();

			if (ImGui::Button("Save"))
			{
				myRecipes[mySelecetedEditRecipeIndex].Name = myEditRecipeInfo.NameField;
				myRecipes[mySelecetedEditRecipeIndex].Portions = myEditRecipeInfo.Portions;
				shouldClose = true;
			}

			if (ImGui::Button("Undo"))
			{
				myRecipes[mySelecetedEditRecipeIndex] = myCurrentBackUp;
				myEditRecipeInfo.ClearEdit(myCurrentBackUp);
			}

			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				myRecipes[mySelecetedEditRecipeIndex] = myCurrentBackUp;
				shouldClose = true;
			}

		}
		ImGui::End();

		if (shouldClose)
		{
			myEditRecipeInfo.Clear();
			aState.SetState(Utilities::EAppStates::EditRecipe, false);
		}
	}

	void CookBook::SaveToFile(const char* aPath)
	{
		Utilities::SaveRecipesToFile(myRecipes, myRecipeCount, aPath);
	}

	bool CookBook::VerifyIngrdient(int& aProductIndex, float& anAmount, int& aCurrentMessurementIndex)
	{
		if (aProductIndex >= 0 && anAmount > 0.0f && aCurrentMessurementIndex >= 0)
			return true;
		return false;
	}

	void CookBook::ClearLastInput()
	{
		myCurrentProductIndex = -1;
		myCurrentMessurementIndex = -1;
		myCurrentIngredients.clear();
		myCurrentInstructions.clear();
		myCurrentNotes.clear();
	}
}