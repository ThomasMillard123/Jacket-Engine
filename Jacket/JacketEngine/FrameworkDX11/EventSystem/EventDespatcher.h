#pragma once
#include <functional>
#include <map>
#include <vector>


#include"Event.h"
namespace Engine::Event {

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



}