#pragma once
#include <functional>
#include <map>
#include <vector>
#include"Event.h"
//https://github.com/Group2IsCrap/GameEngine/blob/main/FirelightEngine/Source/Events/EventDispatcher.h
namespace Engine::EventFunc {

	class EventDespatcher
	{
	public:
		using CallbackFunctionType = std::function< void(void*) >;
		using DescriptorType = const char*;
		//Function Events
		template<typename EventType>
		static size_t SubscribeFunction(CallbackFunctionType&& callbackFunction);
		template<typename EventType>
		static void UnsubscribeFunction(const size_t index);
		static void UnsubscribeFunction(DescriptorType descriptor, const size_t index);
		template<typename EventType>
		static void UnsubscribeAllFunctions();
		template<typename EventType>
		static void InvokeFunctions();
		template<typename EventType>
		static void InvokeFunctions(void* data);
		static void InvokeFunctions(DescriptorType descriptor);
		static void InvokeFunctions(DescriptorType descriptor, void* data);
	private:
		static std::map<Event::DescriptorType, std::vector<CallbackFunctionType>> sm_observers;
		static std::map<Event::DescriptorType, std::unordered_map<size_t, size_t>> sm_eventMap;
	};

	template<typename EventType>
	inline size_t EventFunc::EventDespatcher::SubscribeFunction(CallbackFunctionType&& callbackFunction)
	{
		sm_observers[EventType::sm_descriptor].push_back(callbackFunction);
		size_t index = sm_observers[EventType::sm_descriptor].size() - 1;

		sm_eventMap[EventType::sm_descriptor].insert({ index,index });

		return index;
	}

	template<typename EventType>
	inline void EventFunc::EventDespatcher::UnsubscribeFunction(const size_t index)
	{
		size_t trueIndex = sm_eventMap[EventType::sm_descriptor][index];
		if (trueIndex < sm_observers[EventType::sm_descriptor].size())
		{
			sm_observers[EventType::sm_descriptor].erase(sm_observers[EventType::sm_descriptor].begin() + trueIndex);
			sm_eventMap[EventType::sm_descriptor].erase(index);

			for (auto& ele : sm_eventMap[EventType::sm_descriptor])
			{
				if (ele.second > trueIndex)
				{
					ele.second--;
				}
			}
		}
	}

	template<typename EventType>
	inline void EventFunc::EventDespatcher::UnsubscribeAllFunctions()
	{
		sm_observers[EventType::sm_descriptor].clear();
	}

	template<typename EventType>
	inline void EventFunc::EventDespatcher::InvokeFunctions()
	{
		InvokeFunctions(EventType::sm_descriptor);
	}

	template<typename EventType>
	inline void EventFunc::EventDespatcher::InvokeFunctions(void* data)
	{
		InvokeFunctions(EventType::sm_descriptor, data);
	}

}