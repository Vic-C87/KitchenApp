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