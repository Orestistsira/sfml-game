#include "GameLayer.h"
#include "MenuLayer.h"

GameLayer::GameLayer()
{
	m_Entities.push_back(std::make_unique<Player>());
	m_Entities.push_back(std::make_unique<Ball>());
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnEvent(sf::Event& event)
{
	for (auto& e : m_Entities)
	{
		e->OnEvent(event);
	}
}

void GameLayer::OnUpdate(sf::Time ts)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		TransitionTo<MenuLayer>();
	}

	for (auto& e : m_Entities)
	{
		e->OnUpdate(ts);
	}
}

void GameLayer::OnRender(sf::RenderWindow& window)
{
	for (auto& e : m_Entities)
	{
		e->OnRender(window);
	}
}

