#include "RuntimeContainer.h"

pong::RuntimeContainer::RuntimeContainer()
{
	// Intialize collection.
	entities = std::unordered_map<unsigned long, Runtime*>();
}

pong::RuntimeContainer::~RuntimeContainer()
{
	// Clean container.
	entities.clear();
}

pong::RuntimeContainer& pong::RuntimeContainer::getInstance()
{
	// Create singleton instance.
	static pong::RuntimeContainer instance;
	return instance;
}

bool pong::RuntimeContainer::isIDExists(unsigned long id)
{
	auto& map = getInstance();
	auto it = map.entities.find(id);
	return it != map.entities.end();
}

void pong::RuntimeContainer::addRutime(unsigned long id, Runtime* runtime)
{
	// Add new runtime entity.
	getInstance().entities[id] = runtime;
}

void pong::RuntimeContainer::awake()
{
	// Call awake for all runtime object.
	for (const auto& objPtr : getInstance().entities)
		objPtr.second->onAwake();
}

void pong::RuntimeContainer::update()
{
	// Call update for all runtime object.
	for (const auto& objPtr : getInstance().entities)
		objPtr.second->onUpdate();
}

void pong::RuntimeContainer::end()
{
	// Call end for all runtime object.
	for (const auto& objPtr : getInstance().entities)
		objPtr.second->onEnd();
}
