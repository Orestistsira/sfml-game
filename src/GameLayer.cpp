#include "GameLayer.h"
#include "MenuLayer.h"
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
#include "Application.h"

GameLayer::GameLayer()
{
	m_DynamicEntities.push_back(std::make_unique<Player>());
    // m_DynamicEntities.push_back(std::make_unique<Player>(sf::Vector2f{ 500.f, 550.f }));
    m_DynamicEntities.push_back(std::make_unique<Ball>());

    auto& window = Application::Get().GetWindow();

    m_WorldView = window.getDefaultView();
    auto worldSize = m_WorldView.getSize();

    m_StaticEntities.push_back(std::make_unique<Wall>(
        sf::Vector2f(worldSize.x, 100.f), sf::Vector2f(0.f, worldSize.y - 100.f))); // bottom

    m_StaticEntities.push_back(std::make_unique<Wall>(
        sf::Vector2f(worldSize.x, 100.f), sf::Vector2f(0.f, 0.f))); // top

    m_StaticEntities.push_back(std::make_unique<Wall>(
        sf::Vector2f(100.f, worldSize.y), sf::Vector2f(0.f, 0.f))); // left

    m_StaticEntities.push_back(std::make_unique<Wall>(
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

	for (auto& e : m_DynamicEntities)
	{
		e->OnEvent(event);
	}
    for (auto& e : m_StaticEntities)
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

	for (auto& e : m_DynamicEntities)
	{
		e->OnUpdate(ts);
	}
    for (auto& e : m_StaticEntities)
    {
        e->OnUpdate(ts);
    }
}

void GameLayer::OnRender(sf::RenderWindow& window)
{
	for (auto& e : m_DynamicEntities)
	{
		e->OnRender(window);
	}
    for (auto& e : m_StaticEntities)
    {
        e->OnRender(window);
    }
}

void GameLayer::ResolveCollisions()
{
    // std::cout << "ResolveCollisions" << std::endl;
    // Dynamic vs Static collisions
    for (auto& a : m_DynamicEntities)
    {
        for (auto& b : m_StaticEntities)
        {
            sf::FloatRect boundsA = a->GetBoundingBox();
            sf::FloatRect boundsB = b->GetBoundingBox();

            auto intersection = boundsA.findIntersection(boundsB);
            if (intersection)
            {
                // std::cout << "Collision" << std::endl;
                ResolveDynamicVsStaticCollision(*a, *b, *intersection);
            }
        }
    }

    // Dynamic vs Static collisions
    for (auto& a : m_DynamicEntities)
    {
        for (auto& b : m_DynamicEntities)
        {
            if (a == b)
                break;

            sf::FloatRect boundsA = a->GetBoundingBox();
            sf::FloatRect boundsB = b->GetBoundingBox();

            auto intersection = boundsA.findIntersection(boundsB);
            if (intersection)
            {
                // std::cout << "Collision" << std::endl;
                ResolveDynamicVsDynamicCollision(*a, *b, *intersection);
            }
        }
    }

    // Clear collision normals from dynamic entities
    for (auto& a : m_DynamicEntities)
    {
        a->m_StaticColNormals.clear();
    }
}

static bool EntityCanMoveAcrossNormal(Entity& dynamicEntity, sf::Vector2f normal)
{
    for (const auto& n : dynamicEntity.m_StaticColNormals)
    {
        if (n == -normal)
            return false;
    }
    return true;
}

struct Collision
{
    sf::Vector2f normal;
    float penetration;
};

static Collision GetCollision(Entity& a, Entity& b, sf::FloatRect& intersection)
{
    // Get bounding boxes
    sf::FloatRect aBounds = a.GetBoundingBox();
    sf::FloatRect bBounds = b.GetBoundingBox();

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

    return Collision(normal, penetration);
}

void GameLayer::ResolveDynamicVsDynamicCollision(Entity& a, Entity& b, sf::FloatRect& intersection)
{
    if (!a.m_Sprite || !b.m_Sprite)
        return;

    Entity* staticEntity = nullptr;
    Entity* dynamicEntity = nullptr;

    // --- Case 1: both static -> nothing happens
    if (a.m_IsStatic || b.m_IsStatic)
    {
        throw std::runtime_error("GameLayer::ResolveDynamicVsDynamicCollision - Found a static Entity");
        return;
    }

    if (a.m_Mass >= b.m_Mass)
    {
        staticEntity = &a;
        dynamicEntity = &b;
    }
    else
    {
        staticEntity = &b;
        dynamicEntity = &a;
    }

    auto Collision = GetCollision(*dynamicEntity, *staticEntity, intersection);

    if (EntityCanMoveAcrossNormal(*dynamicEntity, Collision.normal))
    {
        dynamicEntity->m_Sprite->move(Collision.normal * Collision.penetration);
    }
    else
    {
        staticEntity->m_Sprite->move(-Collision.normal * Collision.penetration);
        staticEntity->m_Velocity = 
            { staticEntity->m_Velocity.x * abs(Collision.normal.y), staticEntity->m_Velocity.y * abs(Collision.normal.x) };
    }

    // Reflect velocity along collision normal
    float vn = dynamicEntity->m_Velocity.x * Collision.normal.x + dynamicEntity->m_Velocity.y * Collision.normal.y;

    if (vn < 0.f)
    {
        dynamicEntity->m_Velocity -= (1.f + dynamicEntity->m_Restitution) * vn * Collision.normal;
    }
}

void GameLayer::ResolveDynamicVsStaticCollision(Entity& a, Entity& b, sf::FloatRect& intersection)
{
    if (!a.m_Sprite || !b.m_Sprite)
        return;

    Entity* staticEntity = nullptr;
    Entity* dynamicEntity = nullptr;

    // --- Case 1: both static -> nothing happens
    if (a.m_IsStatic && b.m_IsStatic)
        return;

    // --- Case 2: one static
    if (a.m_IsStatic)
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
    {
        throw std::runtime_error("GameLayer::ResolveDynamicVsStaticCollision - Failed to find a static entity");
        return;
    }

    auto Collision = GetCollision(*dynamicEntity, *staticEntity, intersection);
    dynamicEntity->m_StaticColNormals.push_back(Collision.normal);

    // Separate dynamic entity out of the static one
    dynamicEntity->m_Sprite->move(Collision.normal * Collision.penetration);

    // Reflect velocity along collision normal
    float vn = dynamicEntity->m_Velocity.x * Collision.normal.x + dynamicEntity->m_Velocity.y * Collision.normal.y;

    if (vn < 0.f)
    {
        dynamicEntity->m_Velocity -= (1.f + dynamicEntity->m_Restitution) * vn * Collision.normal;
    }
}



