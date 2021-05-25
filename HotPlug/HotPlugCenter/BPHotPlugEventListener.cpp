#include "pch.h"
#include "BPHotPlugEventListener.h"
#include <utility>
using namespace P3D;
using namespace std;

BPHotPlugEventListener::BPHotPlugEventListener()
{
}

BPHotPlugEventListener::~BPHotPlugEventListener()
{

}

BPHotPlugEventListener& P3D::BPHotPlugEventListener::Get()
{
	static BPHotPlugEventListener m_instance;
	return m_instance;
}

HOTPLUG_EXPORT bool P3D::BPHotPlugEventListener::notifyListeners(BPHotPlugEvent::BPHotPlugEventType type, std::wstring moduleName)
{
	std::map<std::wstring, BPHotPlugEvent*>::iterator it = m_eventPool.find(moduleName);
	if (it == m_eventPool.end())
		return false;
	if (it->second == nullptr)
		return false;
	bool status = false;
	switch (type)
	{
	case P3D::BPHotPlugEvent::BPHotPlugEventType::Load:
	{
		status = it->second->onLoadModule();
		break;
	}
	case P3D::BPHotPlugEvent::BPHotPlugEventType::Unload:
	{
		status = it->second->onUnLoadModule();
		dropListener(moduleName);
		break;
	}
	default:
		break;
	}

	return status;
}

HOTPLUG_EXPORT void P3D::BPHotPlugEventListener::addListener(HINSTANCE moduleInstance, BPHotPlugEvent* handler)
{
	if (handler == nullptr)
		return;

	TCHAR szDLLFolder[MAX_PATH + 1];
	GetModuleFileName(moduleInstance, szDLLFolder, MAX_PATH);
	wstring dllFolder = szDLLFolder;
	size_t pos = dllFolder.rfind(L"\\") + 1;
	wstring moduleName = dllFolder.substr(pos);

	m_eventPool.insert(make_pair(moduleName, handler));
}

HOTPLUG_EXPORT void P3D::BPHotPlugEventListener::dropListener(std::wstring moduleName)
{
	std::map<std::wstring, BPHotPlugEvent*>::iterator it = m_eventPool.find(moduleName);
	if (it == m_eventPool.end())
		return;
	delete it->second;
	m_eventPool.erase(moduleName);
}
