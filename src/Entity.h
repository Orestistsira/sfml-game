#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

inline const float PIXELS_PER_METER = 100.f;
inline const float GROUND_HEIGHT = 800.f;
inline const float FRICTION_COEFF = 30.f;
inline const sf::Vector2f GRAVITY = sf::Vector2f(0, 9.81f * PIXELS_PER_METER);

class Entity
{
public:
	virtual ~Entity() = default;

	virtual void OnEvent(sf::Event& event) {}

	virtual void OnUpdate(sf::Time ts) {}
	virtual void OnRender(sf::RenderWindow& window) {}

	void HandleGroundCollision()
	{
		if (OnGround())
		{
			m_Sprite->setPosition({ m_Sprite->getPosition().x, GROUND_HEIGHT });
			m_Velocity.y = -m_Velocity.y * m_Restitution;
		}
	}

	void SimulatePhysics(sf::Time ts) 
	{
		std::cout << "Velocity: (" << m_Velocity.x << ", " << m_Velocity.y << ")\n";

		m_Force += GRAVITY * m_Mass;
		if (OnGround())
			m_Force.x -= m_Velocity.x * FRICTION_COEFF;
		m_Velocity += (m_Force / m_Mass) * ts.asSeconds();
		m_Sprite->move(m_Velocity * ts.asSeconds());

		m_Force = { 0, 0 };
	}

	bool OnGround() const
	{
		return m_Sprite->getPosition().y >= GROUND_HEIGHT;
	}

protected:
	sf::Texture m_Texture;
	std::optional<sf::Sprite> m_Sprite;

	sf::RectangleShape m_Rectangle;

	sf::Vector2f m_Velocity = sf::Vector2f(0, 0);
	sf::Vector2f m_Force = sf::Vector2f(0, 0);
	float m_Mass = 0;
	float m_Restitution = 0.8;
};