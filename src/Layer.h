#pragma once

#include <SFML/Graphics.hpp>

#include <memory>

class Layer
{
public:
	virtual ~Layer() = default;

	virtual void OnEvent(sf::Event& event) {}

	virtual void OnUpdate(sf::Time ts) {}
	virtual void OnRender(sf::RenderWindow& window) {}

	template<std::derived_from<Layer> T, typename... Args>
	void TransitionTo(Args&&... args)
	{
		QueueTransition(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
	}

	void ConsumePendingTransition();
private:
	void QueueTransition(std::unique_ptr<Layer> toLayer);

	std::unique_ptr<Layer> m_PendingTransition;
};