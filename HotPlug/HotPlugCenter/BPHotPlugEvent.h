#pragma once
namespace P3D
{
	class BPHotPlugEvent
	{
	public:
		enum BPHotPlugEventType
		{
			Load,
			Unload
		}; 
	public:
		HOTPLUG_EXPORT BPHotPlugEvent();
		HOTPLUG_EXPORT virtual ~BPHotPlugEvent();

	public:
		HOTPLUG_EXPORT void onLoadModule();
		HOTPLUG_EXPORT void onUnLoadModule();

	protected:
		virtual void _onLoadModule() = 0;
		virtual void _onUnLoadModule() = 0;

	};
}


