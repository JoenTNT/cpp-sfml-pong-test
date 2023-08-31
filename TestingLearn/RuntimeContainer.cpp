#include "RuntimeContainer.h"

pong::RuntimeContainer::RuntimeContainer()
{
	// Intialize collection.
	entities = std::unordered_map<unsigned long, IRuntime*>();

	// Initialized events.
	onAddRuntimeEvCont = std::unordered_multimap<const void*, std::function<void(const Event&)>>();
	onAddRuntimeEvInvk = new Invoker(&onAddRuntimeEvCont);
}

pong::RuntimeContainer::~RuntimeContainer()
{
	delete onAddRuntimeEvInvk;
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

void pong::RuntimeContainer::addRuntime(unsigned long id, IRuntime* runtime)
{
	// Add new runtime entity.
	auto& instance = getInstance();
	instance.entities[id] = runtime;

	// Call an event.
	instance.onAddRuntimeEvInvk->Invoke(pong::OnAddRuntimeEventArgs(id, runtime));
}

pong::Subscriber* pong::RuntimeContainer::createOnAddRuntimeEvSubs()
{
	return new Subscriber(&(getInstance().onAddRuntimeEvCont));
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

	// Clean container.
	getInstance().entities.clear();
}
