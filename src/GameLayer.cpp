#include "GameLayer.h"
#include "MenuLayer.h"

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnEvent(sf::Event& event)
{
	m_Player.OnEvent(event);
	m_Ball.OnEvent(event);
}

void GameLayer::OnUpdate(sf::Time ts)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		TransitionTo<MenuLayer>();
	}
	m_Player.OnUpdate(ts);
	m_Ball.OnUpdate(ts);
}

void GameLayer::OnRender(sf::RenderWindow& window)
{
	m_Player.OnRender(window);
	m_Ball.OnRender(window);
}

