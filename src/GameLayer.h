#pragma once

#include "Layer.h"

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual void OnEvent(Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;
private:
	sf::Texture m_Texture;
	std::optional<sf::Sprite> m_Sprite;
};