#pragma once

#include "Entity.h"

class Goal : public Entity
{
public:
	Goal(bool isHome);
	virtual ~Goal();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;

	sf::FloatRect GetBoundingBox() const override;
private:
	bool m_IsHome;
};