#include "Player.h"
#include "Application.h"

Player::Player(sf::Vector2f pos)
{
	if (!m_Texture.loadFromFile("res/textures/p1_idle.png"))
	{
		throw std::runtime_error("Player::Player - Failed to load texture");
	}

	m_Texture.setSmooth(true);
	// m_Sprite = sf::RectangleShape(m_Texture);
	m_Sprite = std::make_unique<sf::RectangleShape>();
	m_Sprite->setSize({ 100.f, 100.f });
	m_Sprite->setTexture(&m_Texture);
	m_Sprite->setPosition(pos);

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)
		&& IsOnGround())
	{
		m_Force.y -= JUMP_FORCE;
		std::cout << "Jump" << std::endl;
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