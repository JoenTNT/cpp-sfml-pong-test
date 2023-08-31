#include "UIContainer.h"

pong::UIContainer::UIContainer()
{
	// Initialize element.
	elements = std::unordered_map<unsigned long, IRenderUI*>();
}

pong::UIContainer::~UIContainer() { }

pong::UIContainer& pong::UIContainer::getInstance()
{
	// Create singleton instance.
	static pong::UIContainer instance;
	return instance;
}

bool pong::UIContainer::isIDExists(unsigned long id)
{
	auto& map = getInstance();
	auto it = map.elements.find(id);
	return it != map.elements.end();
}

void pong::UIContainer::addRenderUI(unsigned long id, IRenderUI* element)
{
	// Add new runtime entity.
	auto& instance = getInstance();
	instance.elements[id] = element;
}

void pong::UIContainer::render()
{
	// Call update for all runtime object.
	for (const auto& objPtr : getInstance().elements)
		objPtr.second->render();
}

void pong::UIContainer::clear()
{
	// Call end for all runtime object.
	for (const auto& objPtr : getInstance().elements)
		delete objPtr.second;

	// Clean container.
	getInstance().elements.clear();
}
