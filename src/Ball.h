#pragma once

#include "Entity.h"

class Ball : public Entity
{
public:
	Ball();
	virtual ~Ball();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;
private:
};