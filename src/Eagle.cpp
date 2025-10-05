#include "Eagle.h"

Eagle::Eagle()
{
	if (!m_Texture.loadFromFile("res/textures/Eagle.png"))
	{
		throw std::runtime_error("GameLayer::GameLayer - Failed to load texture");
	}

	m_Sprite = sf::Sprite(m_Texture);
	m_Sprite->setPosition({ 10.f, 50.f });
}

Eagle::~Eagle()
{
}

void Eagle::OnEvent(sf::Event& event)
{

}

void Eagle::OnUpdate(sf::Time ts)
{
	const float speed = 200.f; // pixels per second

	sf::Vector2f movement(0.f, 0.f);

	// poll current key state
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		movement.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		movement.x += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		movement.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		movement.y += 1.f;

	// normalize for diagonal movement
	if (movement.x != 0.f || movement.y != 0.f)
	{
		float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
		movement /= length; // unit vector
	}

	if (m_Sprite)
		m_Sprite->move(movement * speed * ts.asSeconds());
}

void Eagle::OnRender(sf::RenderWindow& window)
{
	if (m_Sprite)
		window.draw(*m_Sprite);
}