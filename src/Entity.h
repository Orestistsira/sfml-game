#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

inline const float PIXELS_PER_METER = 100.f;
inline const float FRICTION_COEFF = 0.8;
inline const sf::Vector2f GRAVITY = sf::Vector2f(0, 9.81f * PIXELS_PER_METER);

class Entity
{
public:
	virtual ~Entity() = default;

	virtual void OnEvent(sf::Event& event) {}

	virtual void OnUpdate(sf::Time ts) {}
	virtual void OnRender(sf::RenderWindow& window) {}

	void SimulatePhysics(sf::Time ts);

	bool IsOnGround() const;

	sf::FloatRect GetBoundingBox() const;
	sf::RectangleShape GetBoundingRectangle() const;

public:
	sf::Texture m_Texture;
	std::unique_ptr<sf::RectangleShape> m_Sprite;

	bool m_IsStatic = false;

	sf::Vector2f m_Velocity = sf::Vector2f(0, 0);
	sf::Vector2f m_Force = sf::Vector2f(0, 0);
	float m_Mass = 0;
	float m_Restitution = 0.8;
};