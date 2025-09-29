#pragma once

#include <SFML/Graphics.hpp>

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void OnEvent(sf::Event& event) {}

	virtual void OnUpdate(sf::Time ts) {}
	virtual void OnRender(sf::RenderWindow& window) {}
};