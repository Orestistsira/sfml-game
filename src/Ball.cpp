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
	m_Sprite->setPosition({ 300.f, 250.f });

	m_InvMass = 2.3255;
	m_Restitution = 0.8;
	m_Type = EntityType::Ball;

	std::cout << "Ball start pos: " << m_Sprite->getPosition().x << ", " << m_Sprite->getPosition().y << std::endl;
}

Ball::~Ball()
{
}

void Ball::OnEvent(sf::Event& event)
{

}

void Ball::OnUpdate(sf::Time ts)
{
	SimulatePhysics(ts);
}

void Ball::OnRender(sf::RenderWindow& window)
{
	window.draw(*m_Sprite);
	auto boundingBox = GetBoundingRectangle();
	window.draw(boundingBox);
}