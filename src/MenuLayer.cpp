#include "MenuLayer.h"
#include "GameLayer.h"

MenuLayer::MenuLayer()
{
}

MenuLayer::~MenuLayer()
{
}

void MenuLayer::OnEvent(sf::Event& event)
{
}

void MenuLayer::OnUpdate(sf::Time ts)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	{
		TransitionTo<GameLayer>();
	}
}

void MenuLayer::OnRender(sf::RenderWindow& window)
{
	window.clear(sf::Color::Magenta);
}