#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
	virtual ~Entity() = default;

	virtual void OnEvent(sf::Event& event) {}

	virtual void OnUpdate(sf::Time ts) {}
	virtual void OnRender(sf::RenderWindow& window) {}

	void SimulatePhysics(sf::Time ts) {
		if (!m_Sprite)
			return;

		m_Force += gravity * m_Mass;
		m_Velocity += m_Force / m_Mass * ts.asSeconds();
		m_Sprite->setPosition(m_Sprite->getPosition() + (m_Velocity * ts.asSeconds()));
	}

protected:
	sf::Texture m_Texture;
	std::optional<sf::Sprite> m_Sprite;

	sf::Vector2f m_Velocity = sf::Vector2f(0, 0);
	sf::Vector2f m_Force = sf::Vector2f(0, 0);
	float m_Mass = 5;
	sf::Vector2f gravity = sf::Vector2f(0, 9.81f);
};