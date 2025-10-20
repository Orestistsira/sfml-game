#include "Player.h"
#include "Application.h"

Player::Player(std::shared_ptr<Entity> ball, bool isHome, sf::Vector2f pos)
	: m_IsHome(isHome)
	, m_CanJump(false)
	, m_CanShoot(false)
	, m_Ball(ball)
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
	m_Type = EntityType::Player;
}

Player::~Player()
{
}

void Player::OnEvent(sf::Event& event)
{

}

void Player::OnUpdate(sf::Time ts)
{
	HandleInput();
	
	SimulatePhysics(ts);

	m_CanJump = false;
	m_CanShoot = false;
}

void Player::OnRender(sf::RenderWindow& window)
{
	window.draw(*m_Sprite);
	auto boundingBox = GetBoundingRectangle();
	window.draw(boundingBox);
}

void Player::HandleInput()
{
	float MOVE_FORCE = 30000.f;
	float JUMP_FORCE = 3500000.f;
	float SHOOT_FORCE_X = 10000.f;
	float SHOOT_FORCE_Y = 10000.f;

	// Select control keys depending on mode
	sf::Keyboard::Key leftKey = m_IsHome ? sf::Keyboard::Key::A : sf::Keyboard::Key::Left;
	sf::Keyboard::Key rightKey = m_IsHome ? sf::Keyboard::Key::D : sf::Keyboard::Key::Right;
	sf::Keyboard::Key jumpKey = m_IsHome ? sf::Keyboard::Key::W : sf::Keyboard::Key::Up;
	sf::Keyboard::Key shootKey = m_IsHome ? sf::Keyboard::Key::Space : sf::Keyboard::Key::Numpad0;

	// Apply horizontal movement
	if (sf::Keyboard::isKeyPressed(leftKey))
		m_Force.x -= MOVE_FORCE;

	if (sf::Keyboard::isKeyPressed(rightKey))
		m_Force.x += MOVE_FORCE;

	// Apply jump
	if (sf::Keyboard::isKeyPressed(jumpKey) && CanJump())
		m_Force.y -= JUMP_FORCE;

	// Shoot
	if (sf::Keyboard::isKeyPressed(shootKey) && CanShoot())
		m_Ball->ApplyForce({ m_IsHome ? SHOOT_FORCE_X : -SHOOT_FORCE_X, -SHOOT_FORCE_Y });
}