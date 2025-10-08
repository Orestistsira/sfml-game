#include "Ball.h"

Ball::Ball()
{
	if (!m_Texture.loadFromFile("res/textures/Football.png"))
	{
		throw std::runtime_error("Ball::Ball - Failed to load texture");
	}

	m_Texture.setSmooth(true);
	// m_Sprite = sf::Sprite(m_Texture);
	m_Sprite = std::make_unique<sf::RectangleShape>();
	m_Sprite->setTexture(&m_Texture);
	m_Sprite->setSize({ 50.f, 50.f });
	m_Sprite->setPosition({ 250.f, 250.f });

	m_Mass = 0.43;
	m_Force = { 100000, -100 };
}

Ball::~Ball()
{
}

void Ball::OnEvent(sf::Event& event)
{

}

void Ball::OnUpdate(sf::Time ts)
{
	// HandleGroundCollision();
	SimulatePhysics(ts);
}

void Ball::OnRender(sf::RenderWindow& window)
{
	window.draw(*m_Sprite);
	auto boundingBox = GetBoundingRectangle();
	window.draw(boundingBox);
}