#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace Utilities
{
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
}