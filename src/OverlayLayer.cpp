#include "OverlayLayer.h"
#include "Utils.h"

#include <iostream>

OverlayLayer::OverlayLayer()
	: m_StatisticsText(m_Font)
{
	if (!m_Font.openFromFile("res/fonts/Sansation.ttf"))
	{
		throw std::runtime_error("OverlayLayer::OverlayLayer - Failed to load font");
	}

	m_StatisticsText.setPosition({ 5.f, 5.f });
	m_StatisticsText.setCharacterSize(24);
	m_StatisticsText.setFillColor(sf::Color::Red);
	m_StatisticsText.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

OverlayLayer::~OverlayLayer()
{
}

void OverlayLayer::OnEvent(sf::Event& event)
{
}

void OverlayLayer::OnUpdate(sf::Time ts)
{
	m_StatisticsUpdateTime += ts;
	m_StatisticsNumFrames += 1;

	if (m_StatisticsUpdateTime >= sf::seconds(1.0f))
	{
		std::string stats =
			"Frames / Second = " + toString(m_StatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(m_StatisticsUpdateTime.asMicroseconds() / m_StatisticsNumFrames) + "us";

		std::cout << stats << std::endl;

		m_StatisticsText.setString(stats);

		m_StatisticsUpdateTime -= sf::seconds(1.0f);
		m_StatisticsNumFrames = 0;
	}
}

void OverlayLayer::OnRender(sf::RenderWindow& window)
{
	window.draw(m_StatisticsText);
}