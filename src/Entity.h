#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

class Entity
{
public:
	Entity();
	~Entity();

	void OnEvent(sf::Event& event);

	void OnUpdate(sf::Time ts);
	void OnRender(sf::RenderWindow& window);
private:
	sf::Texture m_Texture;
	std::optional<sf::Sprite> m_Sprite;
};