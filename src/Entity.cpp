#include "Entity.h"

void Entity::HandleGroundCollision()
{
	if (OnGround())
	{
		m_Sprite->setPosition({ m_Sprite->getPosition().x, GROUND_HEIGHT });
		m_Velocity.y = -m_Velocity.y * m_Restitution;
	}
}

void Entity::SimulatePhysics(sf::Time ts)
{
	m_Force += GRAVITY * m_Mass;
	if (OnGround())
		m_Force.x -= m_Velocity.x * FRICTION_COEFF;
	m_Velocity += (m_Force / m_Mass) * ts.asSeconds();
	m_Sprite->move(m_Velocity * ts.asSeconds());

	m_Force = { 0, 0 };
}

bool Entity::OnGround() const
{
	return m_Sprite->getPosition().y >= GROUND_HEIGHT;
}

sf::RectangleShape Entity::GetBoundingBox() {
	sf::FloatRect boundingBox = m_Sprite->getGlobalBounds();
	sf::RectangleShape rectangle(boundingBox.size);

	rectangle.setPosition(boundingBox.position);
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(2.f);
	rectangle.setOutlineColor(sf::Color::Red);

	return rectangle;
}