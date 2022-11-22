#include"EventDespatcher.h"

namespace Engine::EventFunc {
	
	std::map<Event::DescriptorType, std::vector<EventDespatcher::CallbackFunctionType>> EventDespatcher::sm_observers;
	std::map<Event::DescriptorType, std::unordered_map<size_t, size_t>> EventDespatcher::sm_eventMap;
	void EventDespatcher::UnsubscribeFunction(DescriptorType descriptor, const size_t index)
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
	void EventDespatcher::InvokeFunctions(DescriptorType descriptor)
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
	void EventDespatcher::InvokeFunctions(DescriptorType descriptor, void* data)
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