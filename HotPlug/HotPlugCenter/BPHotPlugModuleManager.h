#pragma once
namespace P3D
{
	class BPHotPlugModuleManager
	{
	public:
		HOTPLUG_EXPORT static BPHotPlugModuleManager& Get();
		HOTPLUG_EXPORT virtual ~BPHotPlugModuleManager();
		HOTPLUG_EXPORT BPHotPlugModuleManager(const BPHotPlugModuleManager&) = delete;
		HOTPLUG_EXPORT BPHotPlugModuleManager& operator=(const BPHotPlugModuleManager&) = delete;
	public:
		HOTPLUG_EXPORT HINSTANCE getModule (std::wstring dllName);
		HOTPLUG_EXPORT DWORD loadModuleForManager(std::wstring dllName);
		HOTPLUG_EXPORT DWORD unLoadModuleForManager(std::wstring dllName);
	private:
		BPHotPlugModuleManager();
		std::map<std::wstring, HINSTANCE> m_moduleMap;
	};

}

