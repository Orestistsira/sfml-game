#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(bool isHome = true, sf::Vector2f pos = { 300.f, 550.f });
	virtual ~Player();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;

	void HandleInput();
	bool CanJump() const { return m_CanJump; }
	void SetCanJump(bool canJump) { m_CanJump = canJump; }
private:
	bool m_IsHome;
	bool m_CanJump;
};