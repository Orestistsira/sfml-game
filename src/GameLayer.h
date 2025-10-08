#pragma once

#include "Layer.h"
#include "Entity.h"

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;

	void ResolveCollisions();
	void ResolveDynamicVsDynamicCollision(Entity& A, Entity& B, sf::FloatRect& intersection);
	void ResolveDynamicVsStaticCollision(Entity& A, Entity& B, sf::FloatRect& intersection);
private:
	std::vector<std::unique_ptr<Entity>> m_StaticEntities;
	std::vector<std::unique_ptr<Entity>> m_DynamicEntities;
	sf::View m_WorldView;
};