#pragma once
//https://github.com/Group2IsCrap/GameEngine/blob/main/FirelightEngine/Source/Events/Event.h
namespace Engine::EventFunc {
	class Event
	{
	public:
		virtual ~Event() {};

		using DescriptorType = const char*;
	};

#define NEW_EVENT(eventName) \
	class eventName : public Event\
	{\
	public:\
		static constexpr DescriptorType sm_descriptor = #eventName;\
	};


	NEW_EVENT(update);
}