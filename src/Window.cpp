#include "Window.h"

#include <SFML/Graphics.hpp>

Window::Window(const WindowSpecification& specification)
	: m_Specification(specification)
{
	
}

Window::~Window()
{
	Destroy();
}

void Window::Create()
{
	m_Window = sf::RenderWindow(sf::VideoMode({ m_Specification.Width, m_Specification.Height }), m_Specification.Title);
	m_Window.setFramerateLimit(144);
	m_Window.setVerticalSyncEnabled(m_Specification.VSync);
}

void Window::Destroy()
{
	m_Window.close();
}

void Window::Clear()
{
	m_Window.clear();
}

void Window::Update()
{
	m_Window.display();
}

bool Window::ShouldClose()
{
	return !m_Window.isOpen();
}