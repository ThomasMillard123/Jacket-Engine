#include"EventDespatcher.h"
namespace Engine::Event {

	template<typename EventType>
	inline size_t EventDespatcher::SubscribeFunction(CallbackFunctionType&& callbackFunction)
	{
		sm_observers[EventType::sm_descriptor].push_back(callbackFunction);
		size_t index = sm_observers[EventType::sm_descriptor].size() - 1;

		sm_eventMap[EventType::sm_descriptor].insert({ index,index });

		return index;
	}



	template<typename EventType>
	inline void EventDespatcher::UnsubscribeFunction(const size_t index)
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
	inline void EventDespatcher::UnsubscribeAllFunctions()
	{
		sm_observers[EventType::sm_descriptor].clear();
	}

	template<typename EventType>
	inline void EventDespatcher::InvokeFunctions()
	{
		InvokeFunctions(EventType::sm_descriptor);
	}

	template<typename EventType>
	inline void EventDespatcher::InvokeFunctions(void* data)
	{
		InvokeFunctions(EventType::sm_descriptor, data);
	}

	inline void EventDespatcher::UnsubscribeFunction(DescriptorType descriptor, const size_t index)
	{
		size_t trueIndex = sm_eventMap[descriptor][index];
		if (trueIndex < sm_observers[descriptor].size())
		{
			sm_observers[descriptor].erase(sm_observers[descriptor].begin() + trueIndex);
			sm_eventMap[descriptor].erase(index);

			for (auto& ele : sm_eventMap[descriptor])
			{
				if (ele.second > trueIndex)
				{
					ele.second--;
				}
			}
		}
	}

	inline void EventDespatcher::InvokeFunctions(DescriptorType descriptor)
	{
		if (!sm_observers.contains(descriptor))
		{
			return;
		}

		auto&& observers = sm_observers.at(descriptor);

		for (auto&& observer : observers)
		{
			observer(nullptr);
		}
	}

	inline void EventDespatcher::InvokeFunctions(DescriptorType descriptor, void* data)
	{
		if (!sm_observers.contains(descriptor))
		{
			return;
		}

		auto&& observers = sm_observers.at(descriptor);

		for (auto&& observer : observers)
		{
			observer(data);
		}
	}

}