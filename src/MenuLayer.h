#pragma once

#include "Layer.h"

class MenuLayer : public Layer
{
public:
	MenuLayer();
	virtual ~MenuLayer();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;
private:
};