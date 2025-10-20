#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

 const float PIXELS_PER_METER = 100.f;
 const float FRICTION_COEFF = 0.8;
 const sf::Vector2f GRAVITY = sf::Vector2f(0, 9.81f * PIXELS_PER_METER);

enum class EntityType
{
	Player = 0,
	Ball = 1,
	Wall = 2
};

class Entity
{
public:
	virtual ~Entity() = default;

	virtual void OnEvent(sf::Event& event) {}

	virtual void OnUpdate(sf::Time ts) {}
	virtual void OnRender(sf::RenderWindow& window) {}

	void SimulatePhysics(sf::Time ts);

	bool IsOnGround() const;

	sf::RectangleShape& GetSprite() const { return *m_Sprite; }
	bool HasSprite() const { return m_Sprite != nullptr; }
	sf::Vector2f GetPosition() const { return m_Sprite->getPosition(); }
	sf::Vector2f GetVelocity() const { return m_Velocity; }
	sf::Vector2f GetForce() const { return m_Force; }
	float GetInvMass() const { return m_InvMass; }
	float GetRestitution() const { return m_Restitution; }
	bool IsStatic() const { return m_IsStatic; }
	EntityType GetType() const { return m_Type; }

	void Move(sf::Vector2f offset) const { m_Sprite->move(offset); }
	void AddVelocity(sf::Vector2f v) { m_Velocity += v; }
	void ApplyForce(sf::Vector2f f) { m_Force += f; }

	sf::FloatRect GetBoundingBox() const;
	sf::RectangleShape GetBoundingRectangle() const;

protected:
	sf::Texture m_Texture;
	std::unique_ptr<sf::RectangleShape> m_Sprite;

	bool m_IsStatic = false;
	EntityType m_Type = EntityType::Player;

	sf::Vector2f m_Velocity = sf::Vector2f(0, 0);
	sf::Vector2f m_Force = sf::Vector2f(0, 0);
	float m_InvMass = 0;
	float m_Restitution = 0.8;
};