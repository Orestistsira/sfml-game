#pragma once

#include "Layer.h"
#include "Player.h"
#include "Ball.h"

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;
private:
	std::vector<std::unique_ptr<Entity>> m_Entities;
};