#include "GameLayer.h"
#include "MenuLayer.h"
#include "Player.h"
#include "Ball.h"
#include "Goal.h"
#include "Wall.h"
#include "Application.h"

GameLayer::GameLayer()
{
    auto ball = std::make_shared<Ball>();
    m_Entities.push_back(ball);

    m_Entities.push_back(std::make_shared<Player>(ball));
    m_Entities.push_back(std::make_shared<Player>(ball, false, sf::Vector2f{ 500.f, 550.f }));

    auto& window = Application::Get().GetWindow();

    m_WorldView = window.getDefaultView();
    auto worldSize = m_WorldView.getSize();

    m_Entities.push_back(std::make_shared<Wall>(
        sf::Vector2f(worldSize.x, PIXELS_PER_METER), sf::Vector2f(0.f, worldSize.y - PIXELS_PER_METER))); // bottom

    m_Entities.push_back(std::make_shared<Wall>(
        sf::Vector2f(worldSize.x, PIXELS_PER_METER), sf::Vector2f(0.f, 0.f))); // top

    m_Entities.push_back(std::make_shared<Wall>(
        sf::Vector2f(PIXELS_PER_METER, worldSize.y), sf::Vector2f(0.f, 0.f))); // left

    m_Entities.push_back(std::make_shared<Wall>(
        sf::Vector2f(PIXELS_PER_METER, worldSize.y), sf::Vector2f(worldSize.x - PIXELS_PER_METER, 0.f))); // right

    m_Entities.push_back(std::make_shared<Goal>(true));
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

static Manifold GetCollisionManifold(Entity& a, Entity& b, sf::FloatRect& intersection)
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
            normal = sf::Vector2f(1.f, 0.f); // a is left of b
        else
            normal = sf::Vector2f(-1.f, 0.f);  // a is right of b
    }
    else
    {
        // Vertical collision
        penetration = intersection.size.y;
        if (aCenter.y < bCenter.y)
            normal = sf::Vector2f(0.f, 1.f); // a is above b
        else
            normal = sf::Vector2f(0.f, -1.f);  // a is below b
    }

    return Manifold(&a, &b, normal, penetration);
}

void GameLayer::ResolveCollisions()
{
    // Dynamic vs Static collisions
    for (auto& a : m_Entities)
    {
        for (auto& b : m_Entities)
        {
            if (a == b)
                break;

            if (!a->HasSprite() || !b->HasSprite())
                continue;

            if (a->IsStatic() && b->IsStatic())
                continue;

            sf::FloatRect boundsA = a->GetBoundingBox();
            sf::FloatRect boundsB = b->GetBoundingBox();

            auto intersection = boundsA.findIntersection(boundsB);
            if (intersection)
            {
                Manifold manifold = GetCollisionManifold(*a, *b, *intersection);
                ResolveCollision(manifold);
            }
        }
    }
}

void CheckCollisionEntitiesCanJump(Manifold& manifold)
{
    Entity& a = *manifold.a;
    Entity& b = *manifold.b;

    if (a.GetType() == EntityType::Player && manifold.normal == sf::Vector2f(0.f, 1.f))
    {
        static_cast<Player&>(a).SetCanJump(true);
    }
    else if (b.GetType() == EntityType::Player && manifold.normal == sf::Vector2f(0.f, -1.f))
    {
        static_cast<Player&>(b).SetCanJump(true);
    }
}

void CheckCollisionEntitiesCanShoot(Manifold& manifold)
{
    Entity& a = *manifold.a;
    Entity& b = *manifold.b;

    Player* player = nullptr;
    Ball* ball = nullptr;

    if (a.GetType() == EntityType::Player && b.GetType() == EntityType::Ball)
    {
        player = dynamic_cast<Player*>(&a);
        ball = dynamic_cast<Ball*>(&b);

        if (player->IsHome() && manifold.normal == sf::Vector2f(1.f, 0.f))
            player->SetCanShoot(true);
        else if (!player->IsHome() && manifold.normal == sf::Vector2f(-1.f, 0.f))
            player->SetCanShoot(true);
    }
    else if (a.GetType() == EntityType::Ball && b.GetType() == EntityType::Player)
    {
        ball = dynamic_cast<Ball*>(&a);
        player = dynamic_cast<Player*>(&b);

        if (!player->IsHome() && manifold.normal == sf::Vector2f(1.f, 0.f))
            player->SetCanShoot(true);
        else if (player->IsHome() && manifold.normal == sf::Vector2f(-1.f, 0.f))
            player->SetCanShoot(true);
    }
}

void GameLayer::ResolveCollision(Manifold& manifold)
{
    Entity& a = *manifold.a;
    Entity& b = *manifold.b;
    CheckCollisionEntitiesCanJump(manifold);
    CheckCollisionEntitiesCanShoot(manifold);

    sf::Vector2f rv = b.GetVelocity() - a.GetVelocity();

    // Reflect velocity along collision normal
    float vn = rv.x * manifold.normal.x + rv.y * manifold.normal.y;

    // Do not resolve if velocities are separating 
    if (vn >= 0)
        return;

    // Calculate restitution 
    // float e = std::min(a.m_Restitution, b.m_Restitution);
    float e = a.GetRestitution() * b.GetRestitution();

    // Calculate impulse scalar 
    float j = -(1 + e) * vn;
    j /= a.GetInvMass() + b.GetInvMass();

    // Apply impulse 
    sf::Vector2f impulse = j * manifold.normal;
    a.AddVelocity(-a.GetInvMass() * impulse);
    b.AddVelocity(b.GetInvMass() * impulse);

    // Positional correction
    const float percent = 0.3; // usually 20% to 80%
    const float slop = 0.01; // usually 0.01 to 0.1
    sf::Vector2f correction = 
        (std::max(manifold.penetration - slop, 0.0f) / (a.GetInvMass() + b.GetInvMass())) * percent * manifold.normal;
    a.Move(-a.GetInvMass() * correction);
    b.Move(b.GetInvMass() * correction);
}
