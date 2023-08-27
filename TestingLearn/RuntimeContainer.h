#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Runtime.h"

namespace pong
{
	class RuntimeContainer
	{
	private:
		std::unordered_map<unsigned long, Runtime*> entities;
		// TODO: Event handler.
		//std::unordered_set<void(*)(unsigned long, Runtime*)> onAddRuntime;

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
		static void addRuntime(unsigned long id, Runtime* runtime);

		template <typename TValue>
		static void getRuntimeObjects(std::unordered_map<unsigned long, TValue*>* cont);

		static void subsOnAddRuntime(void(*func)(unsigned long, Runtime*));
		static void unsubsOnAddRuntime(void(*func)(unsigned long, Runtime*));

		static void awake();
		static void update();
		static void end();
	};
}
