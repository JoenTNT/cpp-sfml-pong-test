#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Events/EventSystem.h"
#include "Interfaces/IRuntime.h"
#include "Interfaces/IContainer.h"

namespace pong
{
	/// <summary>
	/// Event called when added a new object into the game.
	/// </summary>
	struct OnAddRuntimeEventArgs : Event {
	public:
		unsigned long id;
		IRuntime* runtime;

		OnAddRuntimeEventArgs(unsigned long id, IRuntime* runtime) : id(id), runtime(runtime) { }
	};

	class RuntimeContainer : public IContainer
	{
	private:
		std::unordered_map<unsigned long, IRuntime*> entities;
		
		std::unordered_multimap<const void*, std::function<void(const Event&)>> onAddRuntimeEvCont;
		Invoker* onAddRuntimeEvInvk;

		RuntimeContainer();
		~RuntimeContainer();

		RuntimeContainer(RuntimeContainer const&) = delete;
		void operator=(RuntimeContainer const&) = delete;

	public:
		/// <summary>
		/// Singleton implementation.
		/// </summary>
		/// <returns>Singleton instance.</returns>
		static RuntimeContainer& getInstance();

		static bool isIDExists(unsigned long id);
		static void addRuntime(unsigned long id, IRuntime* runtime);

		template <typename TValue>
		static void getRuntimeObjects(std::unordered_map<unsigned long, TValue*>* cont) {
			auto& container = getInstance();
			TValue* obj;
			for (auto& entity : container.entities) {
				obj = dynamic_cast<TValue*>(entity.second);
				if (obj) (*cont)[entity.first] = obj;
			}
			obj = nullptr;
		}

		/// <summary>
		/// This will create a subscriber from the event container.
		/// </summary>
		/// <returns></returns>
		static Subscriber* createOnAddRuntimeEvSubs();

		static void awake();
		static void update();
		static void end();
	};
}
