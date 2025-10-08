#include "Application.h"
#include "GameLayer.h"
#include "OverlayLayer.h"
#include "MenuLayer.h"

#include <SFML/Graphics.hpp>

int main()
{
	ApplicationSpecification appSpec;
	appSpec.Name = "Game";
	appSpec.WindowSpec.Width = 1620;
	appSpec.WindowSpec.Height = 900;

	Application game(appSpec);
	game.PushLayer<GameLayer>();
	// game.PushLayer<MenuLayer>();
	game.PushLayer<OverlayLayer>();
	game.Run();
}
