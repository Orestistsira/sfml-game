#include "Wall.h"
#include "Application.h"

Wall::Wall(sf::Vector2f size, sf::Vector2f position)
{
	m_Sprite = std::make_unique<sf::RectangleShape>();
	m_Sprite->setSize(size);
	m_Sprite->setPosition(position);

	m_InvMass = 0;
	m_Restitution = 0.5;
	m_IsStatic = true;
}

Wall::~Wall()
{
}

void Wall::OnEvent(sf::Event& event)
{

}

void Wall::OnUpdate(sf::Time ts)
{
}

void Wall::OnRender(sf::RenderWindow& window)
{
	auto boundingBox = GetBoundingRectangle();
	window.draw(boundingBox);
}