#include "GameLayer.h"

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnEvent(sf::Event& event)
{
	m_Entity.OnEvent(event);
}

void GameLayer::OnUpdate(sf::Time ts)
{
	m_Entity.OnUpdate(ts);
}

void GameLayer::OnRender(sf::RenderWindow& window)
{
	m_Entity.OnRender(window);
}

