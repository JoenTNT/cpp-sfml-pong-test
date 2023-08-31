#pragma once
#include <vector>
#include <unordered_map>
#include <functional>

namespace pong
{
	struct Event {
		virtual ~Event() { }
	};

	//typedef std::vector<EventBaseType> EventVector;
	typedef std::unordered_multimap<const void*, std::function<void(const Event&)>> EventMap;

	class Subscriber {
	private:
		EventMap* evv;

	public:
		Subscriber(EventMap* evv) : evv(evv) { }

		template <typename EventType>
		void Subscribe(const std::function<void(const EventType&)>& callback) {
			const void* callbackAddress = &callback;
			evv->emplace(std::make_pair(callbackAddress, [callback](const Event& event) {
				callback(dynamic_cast<const EventType&>(event));
			}));
			//std::cout << "Subscribed: " << callbackAddress << "; Amount of subs: ";
			//std::cout << static_cast<int>(evv->size()) << std::endl;
		}

		template <typename EventType>
		void Unsubscribe(const std::function<void(const EventType&)>& callback) {
			const void* callbackAddress = &callback;
			for (auto& ev : *evv) {
				if (ev.first == callbackAddress) {
					evv->erase(callbackAddress);
					break;
				}
			}
			//std::cout << "Unsubscribed: " << callbackAddress << "; Amount of subs: ";
			//std::cout << static_cast<int>(evv->size()) << std::endl;
		}
	};

	class Invoker {
	private:
		EventMap* evv;

	public:
		Invoker(EventMap* evv) : evv(evv) { }

		template <typename EventType>
		void Invoke(const EventType& ev) {
			// Attempt to invoke the functions.
			for (auto const& evsub : *evv) {
				evsub.second(ev);
			}
		}
	};
}