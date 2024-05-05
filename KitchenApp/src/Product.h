#pragma once
#include "Utilities.h"

namespace Organizer
{
	struct Product
	{
		char Name[20];
		char NameEnglish[20];
		Utilities::EStorageType StandardLocation;
		Utilities::EMessurement StandardMessurement;
		int GramPerMessurement;
		unsigned int UniqueID;
	};
}