#pragma once


namespace P3D
{
	class BPHotPlugEventListener
	{
	public:
		HOTPLUG_EXPORT static BPHotPlugEventListener& Get();
		HOTPLUG_EXPORT virtual ~BPHotPlugEventListener();
		HOTPLUG_EXPORT BPHotPlugEventListener(const BPHotPlugEventListener&) = delete;
		HOTPLUG_EXPORT BPHotPlugEventListener& operator=(const BPHotPlugEventListener&) = delete;

	public:
		HOTPLUG_EXPORT bool notifyListeners(BPHotPlugEvent::BPHotPlugEventType type, std::wstring moduleName);
		HOTPLUG_EXPORT void addListener(HINSTANCE moduleInstance, BPHotPlugEvent* handler);
		HOTPLUG_EXPORT void dropListener(std::wstring moduleName);

	private:
		BPHotPlugEventListener();
		std::map<std::wstring, BPHotPlugEvent*> m_eventPool;
	};

}