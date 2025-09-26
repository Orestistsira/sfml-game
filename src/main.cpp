#include "Application.h"

#include <SFML/Graphics.hpp>

int main()
{
	ApplicationSpecification appSpec;
	appSpec.Name = "Game";
	appSpec.WindowSpec.Width = 1920;
	appSpec.WindowSpec.Height = 1080;

	Application game(appSpec);
	game.Run();
}
