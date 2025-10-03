#include "Application.h"

#include <algorithm>

static Application* s_Application = nullptr;

Application::Application(const ApplicationSpecification& specification)
	: m_Specification(specification)
{
	s_Application = this;

	// Set window title to app name if empty
	if (m_Specification.WindowSpec.Title.empty())
		m_Specification.WindowSpec.Title = m_Specification.Name;

	m_Window = std::make_shared<Window>(m_Specification.WindowSpec);
	m_Window->Create();
}

Application::~Application()
{
	m_Window->Destroy();

	s_Application = nullptr;
}

void Application::Run()
{
	m_Running = true;
	sf::Clock clock;

	// Main Application loop
	while (m_Running)
	{
		while (std::optional event = m_Window->GetWindow().pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				m_Window->Destroy();
			}

			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
				layer->OnEvent(*event);
		}

		if (m_Window->ShouldClose())
		{
			Stop();
			break;
		}

		sf::Time timestep = GetTimestep(clock);

		// Main layer update here
		for (const std::unique_ptr<Layer>& layer : m_LayerStack)
			layer->OnUpdate(timestep);

		m_Window->Clear();
		// NOTE: rendering can be done elsewhere (eg. render thread)
		for (const std::unique_ptr<Layer>& layer : m_LayerStack)
			layer->OnRender(m_Window->GetWindow());
		m_Window->Update();

		// Consume queued layer transitions after frame
		for (const std::unique_ptr<Layer>& layer : m_LayerStack)
			layer->ConsumePendingTransition();
	}
}

void Application::Stop()
{
	m_Running = false;
}

Application& Application::Get()
{
	assert(s_Application);
	return *s_Application;
}

sf::Time Application::GetTimestep(sf::Clock& clock)
{
	sf::Time timestep = clock.restart();
	float clamped_timestep = std::clamp(
		timestep.asSeconds(),
		0.001f,
		0.1f
	);
	return sf::seconds(clamped_timestep);
}
