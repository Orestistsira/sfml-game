#pragma once

#include <SFML/Graphics.hpp>

#include <string>

struct WindowSpecification
{
	std::string Title;
	uint32_t Width = 1280;
	uint32_t Height = 720;
};

class Window
{
public:
	Window(const WindowSpecification& specification = WindowSpecification());
	~Window();

	void Create();

	void Destroy();
	void Clear();
	void Update();

	bool ShouldClose();

	sf::RenderWindow& GetWindow() { return m_Window; }
private:
	WindowSpecification m_Specification;

	sf::RenderWindow m_Window;
};