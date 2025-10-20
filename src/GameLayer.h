#pragma once

#include "Layer.h"
#include "Entity.h"

struct Manifold
{
	Entity* a;
	Entity* b;
	sf::Vector2f normal;
	float penetration;
};

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;

	void ResolveCollisions();
	void ResolveCollision(Manifold& manifold);
private:
	std::vector<std::shared_ptr<Entity>> m_Entities;
	sf::View m_WorldView;
};