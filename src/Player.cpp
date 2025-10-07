#include "Player.h"

Player::Player()
{
	if (!m_Texture.loadFromFile("res/textures/p1_idle.png"))
	{
		throw std::runtime_error("Player::Player - Failed to load texture");
	}

	m_Texture.setSmooth(true);
	m_Sprite = sf::Sprite(m_Texture);
	m_Sprite->setPosition({ 300.f, 550.f });

	m_Mass = 80;
	m_Restitution = 0;
}

Player::~Player()
{
}

void Player::OnEvent(sf::Event& event)
{

}

void Player::OnUpdate(sf::Time ts)
{
	float MOVE_FORCE = 30000.f;
	float JUMP_FORCE = 3500000.f;

	// Apply horizontal movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		m_Force.x -= MOVE_FORCE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		m_Force.x += MOVE_FORCE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) 
		&& m_Sprite->getPosition().y >= GROUND_HEIGHT)
		m_Force.y -= JUMP_FORCE;

	HandleGroundCollision();
	SimulatePhysics(ts);
}

void Player::OnRender(sf::RenderWindow& window)
{
	window.draw(*m_Sprite);
}