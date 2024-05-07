#include "App.h"

int main()
{
	Organizer::App* app = new Organizer::App();

	if (app->Initialize())
	{
		app->Update();
	}

	delete app;
	return 0;
}
