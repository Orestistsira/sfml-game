#include "Player.h"
#include "Application.h"

Player::Player(bool isHome, sf::Vector2f pos)
	: m_IsHome(isHome)
{
	std::string texturePath = m_IsHome ? "res/textures/p1_idle.png" : "res/textures/p2_idle.png";

	if (!m_Texture.loadFromFile(texturePath))
	{
		throw std::runtime_error("Player::Player - Failed to load texture");
	}

	m_Texture.setSmooth(true);
	// m_Sprite = sf::RectangleShape(m_Texture);
	m_Sprite = std::make_unique<sf::RectangleShape>();
	m_Sprite->setSize({ 100.f, 100.f });
	m_Sprite->setTexture(&m_Texture);
	m_Sprite->setPosition(pos);

	m_InvMass = 0.0125;
	m_Restitution = 0.6;
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

	if (!m_IsHome)
	{
		// Apply horizontal movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			m_Force.x -= MOVE_FORCE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			m_Force.x += MOVE_FORCE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)
			&& IsOnGround())
		{
			m_Force.y -= JUMP_FORCE;
			std::cout << "Jump" << std::endl;
		}
	}
	else
	{
		// Apply horizontal movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			m_Force.x -= MOVE_FORCE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			m_Force.x += MOVE_FORCE;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
			&& IsOnGround())
		{
			m_Force.y -= JUMP_FORCE;
			std::cout << "Jump" << std::endl;
		}
	}
	
	// HandleGroundCollision();
	SimulatePhysics(ts);
}

void Player::OnRender(sf::RenderWindow& window)
{
	window.draw(*m_Sprite);
	auto boundingBox = GetBoundingRectangle();
	window.draw(boundingBox);
}