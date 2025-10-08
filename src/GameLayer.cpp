#include "GameLayer.h"
#include "MenuLayer.h"
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
#include "Application.h"

GameLayer::GameLayer()
{
	m_Entities.push_back(std::make_unique<Player>());
	m_Entities.push_back(std::make_unique<Ball>());

    auto& window = Application::Get().GetWindow();

    m_WorldView = window.getDefaultView();
    auto worldSize = m_WorldView.getSize();

    m_Entities.push_back(std::make_unique<Wall>(
        sf::Vector2f(worldSize.x, 100.f), sf::Vector2f(0.f, worldSize.y - 100.f))); // bottom

    m_Entities.push_back(std::make_unique<Wall>(
        sf::Vector2f(worldSize.x, 100.f), sf::Vector2f(0.f, 0.f))); // top

    m_Entities.push_back(std::make_unique<Wall>(
        sf::Vector2f(100.f, worldSize.y), sf::Vector2f(0.f, 0.f))); // left

    m_Entities.push_back(std::make_unique<Wall>(
        sf::Vector2f(100.f, worldSize.y), sf::Vector2f(worldSize.x - 100.f, 0.f))); // right
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnEvent(sf::Event& event)
{
    if (const auto* resized = event.getIf<sf::Event::Resized>())
    {
        std::cout << "new width: " << resized->size.x << std::endl;
        std::cout << "new height: " << resized->size.y << std::endl;
        auto& window = Application::Get().GetWindow();
        window.setView(m_WorldView);
    }

	for (auto& e : m_Entities)
	{
		e->OnEvent(event);
	}
}

void GameLayer::OnUpdate(sf::Time ts)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		TransitionTo<MenuLayer>();
	}

    ResolveCollisions();

	for (auto& e : m_Entities)
	{
		e->OnUpdate(ts);
	}
}

void GameLayer::OnRender(sf::RenderWindow& window)
{
	for (auto& e : m_Entities)
	{
		e->OnRender(window);
	}
}

void GameLayer::ResolveCollisions()
{
    // std::cout << "ResolveCollisions" << std::endl;
    for (auto& a : m_Entities)
    {
        for (auto& b : m_Entities)
        {
            if (a == b)
                break;

            sf::FloatRect boundsA = a->GetBoundingBox();
            sf::FloatRect boundsB = b->GetBoundingBox();

            auto intersection = boundsA.findIntersection(boundsB);
            if (intersection)
            {
                // std::cout << "Collision" << std::endl;
                ResolveCollision(*a, *b, *intersection);
            }
        }
    }
}

void GameLayer::ResolveCollision(Entity& a, Entity& b, sf::FloatRect& intersection)
{
    if (!a.m_Sprite || !b.m_Sprite)
        return;

    Entity* staticEntity = nullptr;
    Entity* dynamicEntity = nullptr;

    if (a.m_IsStatic && b.m_IsStatic)
        return;
    else if (a.m_IsStatic)
    {
        staticEntity = &a;
        dynamicEntity = &b;
    }
    else if (b.m_IsStatic)
    {
        staticEntity = &b;
        dynamicEntity = &a;
    }
    else
        return;

    // Get bounding boxes
    sf::FloatRect aBounds = dynamicEntity->GetBoundingBox();
    sf::FloatRect bBounds = staticEntity->GetBoundingBox();

    // Compute centers
    sf::Vector2f aCenter = aBounds.getCenter();
    sf::Vector2f bCenter = bBounds.getCenter();

    // Compute collision normal based on overlap
    sf::Vector2f normal(0.f, 0.f);
    float penetration = 0.f;

    if (intersection.size.x < intersection.size.y)
    {
        // Horizontal collision
        penetration = intersection.size.x;
        if (aCenter.x < bCenter.x)
            normal = sf::Vector2f(-1.f, 0.f); // a is left of b
        else
            normal = sf::Vector2f(1.f, 0.f);  // a is right of b
    }
    else
    {
        // Vertical collision
        penetration = intersection.size.y;
        if (aCenter.y < bCenter.y)
            normal = sf::Vector2f(0.f, -1.f); // a is above b
        else
            normal = sf::Vector2f(0.f, 1.f);  // a is below b
    }

    // Separate dynamic entity out of the static one
    dynamicEntity->m_Sprite->move(normal * penetration);

    // Reflect velocity along collision normal
    float vn = dynamicEntity->m_Velocity.x * normal.x + dynamicEntity->m_Velocity.y * normal.y;

    if (vn < 0.f)
    {
        dynamicEntity->m_Velocity -= (1.f + dynamicEntity->m_Restitution) * vn * normal;
    }
}



