#pragma once
namespace P3D
{
	class BPHotPlugEvent
	{
	public:
		enum class BPHotPlugEventType
		{
			Load,
			Unload
		}; 
	public:
		HOTPLUG_EXPORT BPHotPlugEvent();
		HOTPLUG_EXPORT virtual ~BPHotPlugEvent();

	public:
		HOTPLUG_EXPORT bool onLoadModule();
		HOTPLUG_EXPORT bool onUnLoadModule();

	protected:
		virtual bool _onLoadModule() = 0;
		virtual bool _onUnLoadModule() = 0;

	};
}


