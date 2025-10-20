#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(std::shared_ptr<Entity> ball, bool isHome = true, sf::Vector2f pos = { 300.f, 550.f });
	virtual ~Player();

	virtual void OnEvent(sf::Event& event) override;

	virtual void OnUpdate(sf::Time ts) override;
	virtual void OnRender(sf::RenderWindow& window) override;

	void HandleInput();

	bool CanJump() const { return m_CanJump; }
	void SetCanJump(bool canJump) { m_CanJump = canJump; }

	bool CanShoot() const { return m_CanShoot; }
	void SetCanShoot(bool canShoot) { m_CanShoot = canShoot; }

	bool IsHome() const { return m_IsHome; }
private:
	bool m_IsHome;
	bool m_CanJump;
	bool m_CanShoot;

	std::shared_ptr<Entity> m_Ball = nullptr;
};