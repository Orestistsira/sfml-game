#pragma once

#include "Layer.h"
#include "Entity.h"

class OverlayLayer : public Layer
{
public:
	OverlayLayer();
	virtual ~OverlayLayer();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;
private:
	sf::Font m_Font;
	sf::Text m_StatisticsText;
	sf::Time m_StatisticsUpdateTime;
	std::size_t m_StatisticsNumFrames = 0;
};