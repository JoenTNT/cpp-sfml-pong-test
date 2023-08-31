#pragma once
#include <unordered_map>

#include "Interfaces/IContainer.h"
#include "Interfaces/IRenderUI.h"
#include "Interfaces/IRuntime.h"

namespace pong
{
	class UIContainer : public IContainer
	{
	private:
		std::unordered_map<unsigned long, IRenderUI*> elements;

		UIContainer();
		~UIContainer();

		UIContainer(UIContainer const&) = delete;
		void operator=(UIContainer const&) = delete;

	public:
		/// <summary>
		/// Singleton implementation.
		/// </summary>
		/// <returns>Singleton instance.</returns>
		static UIContainer& getInstance();

		static bool isIDExists(unsigned long id);
		static void addRenderUI(unsigned long id, IRenderUI* element);

		static void render();
		static void clear();
	};
}
