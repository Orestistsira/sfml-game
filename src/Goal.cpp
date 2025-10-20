#include "Goal.h"
#include "Application.h"

Goal::Goal(bool isHome)
	: m_IsHome(isHome)
{
	if (!m_Texture.loadFromFile("res/textures/goal_1.png"))
	{
		throw std::runtime_error("Goal::Goal - Failed to load texture");
	}

	m_Texture.setSmooth(true);
	// m_Sprite = sf::Sprite(m_Texture);
	m_Sprite = std::make_unique<sf::RectangleShape>();
	m_Sprite->setTexture(&m_Texture);
	m_Sprite->setSize({ 200.f, 400.f });

	auto& window = Application::Get().GetWindow();
	auto& worldView = window.getView();
	auto worldSize = worldView.getSize();
	m_Sprite->setPosition(sf::Vector2f(PIXELS_PER_METER, worldSize.y - PIXELS_PER_METER - 400.f));

	m_InvMass = 0;
	m_Restitution = 0.5;
	m_IsStatic = true;
	m_Type = EntityType::Goal;
}

Goal::~Goal()
{
}

void Goal::OnEvent(sf::Event& event)
{

}

void Goal::OnUpdate(sf::Time ts)
{
}

void Goal::OnRender(sf::RenderWindow& window)
{
	window.draw(*m_Sprite);
	auto boundingBox = GetBoundingRectangle();
	window.draw(boundingBox);
}

sf::FloatRect Goal::GetBoundingBox() const {
	return sf::FloatRect(m_Sprite->getPosition(), sf::Vector2f(m_Sprite->getSize().x, 20));
}