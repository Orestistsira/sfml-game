#include "GameLayer.h"

GameLayer::GameLayer()
{
	if (!m_Texture.loadFromFile("res/textures/Eagle.png"))
	{
		throw std::runtime_error("GameLayer::GameLayer - Failed to load texture");
	}

	m_Sprite = sf::Sprite(m_Texture);
	m_Sprite->setPosition({ 10.f, 50.f });
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnEvent(Event& event)
{

}

void GameLayer::OnUpdate(sf::Time ts)
{
	if (m_Sprite)
		m_Sprite->move({ 5.f, 10.f });
}

void GameLayer::OnRender(sf::RenderWindow& window)
{
	if (m_Sprite)
		window.draw(*m_Sprite);
}

