#include "Ball.h"

Ball::Ball()
{
	if (!m_Texture.loadFromFile("res/textures/Football.png"))
	{
		throw std::runtime_error("Ball::Ball - Failed to load texture");
	}

	m_Texture.setSmooth(true);
	m_Sprite = sf::Sprite(m_Texture);
	m_Sprite->setPosition({ 250.f, 250.f });
	m_Sprite->setScale({ 0.02, 0.02 });

	m_Mass = 0.43;
}

Ball::~Ball()
{
}

void Ball::OnEvent(sf::Event& event)
{

}

void Ball::OnUpdate(sf::Time ts)
{
	HandleGroundCollision();
	SimulatePhysics(ts);
}

void Ball::OnRender(sf::RenderWindow& window)
{
	window.draw(*m_Sprite);
}