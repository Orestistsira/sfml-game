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
	m_Eagle.OnEvent(event);
	m_Ball.OnEvent(event);
}

void GameLayer::OnUpdate(sf::Time ts)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		TransitionTo<MenuLayer>();
	}
	m_Eagle.OnUpdate(ts);
	m_Ball.OnUpdate(ts);
}

void GameLayer::OnRender(sf::RenderWindow& window)
{
	m_Eagle.OnRender(window);
	m_Ball.OnRender(window);
}

