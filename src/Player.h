#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(sf::Vector2f pos = { 300.f, 550.f });
	virtual ~Player();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;
private:
};