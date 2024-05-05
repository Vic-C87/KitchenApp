#pragma once
#include "ProductFactory.h"

namespace Organizer
{
	struct Ingredient
	{
		Product Type;
		float Amount;
		Utilities::EUnitType Unit;
		Utilities::EStorageType Location;
		Utilities::Date BestBefore;
	};
}