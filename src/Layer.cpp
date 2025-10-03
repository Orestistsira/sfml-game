#include "Layer.h"
#include "Application.h"

void Layer::QueueTransition(std::unique_ptr<Layer> toLayer)
{
	m_PendingTransition = std::move(toLayer);
}

void Layer::ConsumePendingTransition()
{
	if (!m_PendingTransition)
		return;

	auto& layerStack = Application::Get().m_LayerStack;
	for (auto& layer : layerStack)
	{
		if (layer.get() == this)
		{
			layer = std::move(m_PendingTransition);
			return;
		}
	}
}