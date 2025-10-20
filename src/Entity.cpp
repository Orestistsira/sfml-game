#include "Entity.h"
#include "Application.h"

void Entity::SimulatePhysics(sf::Time ts)
{
	m_Force += GRAVITY * (1.0f / m_InvMass);
	if (IsOnGround())
		m_Force.x -= m_Velocity.x * FRICTION_COEFF;
	m_Velocity += m_Force * m_InvMass * ts.asSeconds();
	m_Sprite->move(m_Velocity * ts.asSeconds());

	m_Force = { 0, 0 };
}

bool Entity::IsOnGround() const
{
	auto& window = Application::Get().GetWindow();
	auto& worldView = window.getView();
	auto worldSize = worldView.getSize();
	return m_Sprite->getPosition().y >= worldSize.y - PIXELS_PER_METER - m_Sprite->getSize().y;
}

sf::FloatRect Entity::GetBoundingBox() const {
	return m_Sprite->getGlobalBounds();
}

sf::RectangleShape Entity::GetBoundingRectangle() const
{
	sf::FloatRect boundingBox = GetBoundingBox();
	sf::RectangleShape rectangle(boundingBox.size);

	rectangle.setPosition(boundingBox.position);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(2.f);
	rectangle.setOutlineColor(sf::Color::Red);

	return rectangle;
}