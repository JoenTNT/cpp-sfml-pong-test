#include "RuntimeContainer.h"

pong::RuntimeContainer::RuntimeContainer()
{
	// Intialize collection.
	entities = std::unordered_map<unsigned long, Runtime*>();
	//onAddRuntime = std::unordered_set<std::function<void(unsigned long, Runtime*)>*>();
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

void pong::RuntimeContainer::addRuntime(unsigned long id, Runtime* runtime)
{
	// Add new runtime entity.
	getInstance().entities[id] = runtime;
}

template <typename TValue>
void pong::RuntimeContainer::getRuntimeObjects(std::unordered_map<unsigned long, TValue*>* cont)
{
	auto& container = getInstance();
	TValue* obj;
	for (auto& entity : container.entities) {
		obj = dynamic_cast<TValue*>(entity.second);
		if (obj) (*cont)[entity.first] = obj;
	}
	obj = nullptr;
}

void pong::RuntimeContainer::subsOnAddRuntime(void(*func)(unsigned long, Runtime*))
{
	std::cout << "Subscribe Function " << func << std::endl;
	//getInstance().onAddRuntime.insert(func);
}

void pong::RuntimeContainer::unsubsOnAddRuntime(void(*func)(unsigned long, Runtime*))
{
	std::cout << "Unsubscribe Function " << func << std::endl;
	//getInstance().onAddRuntime.erase(func);
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
