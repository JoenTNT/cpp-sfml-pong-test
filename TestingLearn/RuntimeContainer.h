#pragma once
#include <iostream>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Runtime.h"

namespace pong
{
	class RuntimeContainer
	{
	private:
		std::unordered_map<unsigned long, Runtime*> entities;

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
		static void addRutime(unsigned long id, Runtime* runtime);

		static void awake();
		static void update();
		static void end();
	};
}
