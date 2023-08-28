#include "RuntimeContainer.h"

pong::RuntimeContainer::RuntimeContainer()
{
	// Intialize collection.
	entities = std::unordered_map<unsigned long, IRuntime*>();
	//onAddRuntime = std::unordered_set<std::function<void(unsigned long, Runtime*)>*>();
	//onAddRuntime = std::unordered_set<std::function<void(unsigned long, IRuntime*)>>();

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
	instance.onAddRuntimeEvInvk->Invoke(OnAddRuntimeEventArgs(id, runtime));
}

//void pong::RuntimeContainer::subsOnAddRuntime(void(*func)(unsigned long, Runtime*))
//{
//	std::cout << "Subscribe Function " << func << std::endl;
//	getInstance().onAddRuntime.insert(func);
//}
//
//void pong::RuntimeContainer::unsubsOnAddRuntime(void(*func)(unsigned long, Runtime*))
//{
//	std::cout << "Unsubscribe Function " << func << std::endl;
//	getInstance().onAddRuntime.erase(func);
//}

//void pong::RuntimeContainer::subsOnAddRuntime(std::function<void(unsigned long, IRuntime*)> func)
//{
//	std::cout << "Subscribe Function " << &func << std::endl;
//
//	// Insert new event.
//	getInstance().onAddRuntime.insert(func);
//}
//
//void pong::RuntimeContainer::unsubsOnAddRuntime(std::function<void(unsigned long, IRuntime*)> func)
//{
//	std::cout << "Unsubscribe Function " << &func << std::endl;
//
//	// Find and delete event.
//	auto ev = getInstance().onAddRuntime;
//	auto it = std::find(ev.begin(), ev.end(), func);
//	if (it != ev.end()) ev.erase(it);
//}

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
