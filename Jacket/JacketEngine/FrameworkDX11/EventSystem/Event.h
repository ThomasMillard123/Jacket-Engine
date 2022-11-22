#pragma once
namespace Engine::Event {
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

}