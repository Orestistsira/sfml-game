#pragma once

#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(sf::Vector2f size, sf::Vector2f position);
	virtual ~Wall();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;
};