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
	std::map<std::wstring, BPHotPlugEvent*>::iterator it =  m_eventPool.find(moduleName);
	if (it == m_eventPool.end())
		return false;
	if (it->second == nullptr)
		return false;

	switch (type)
	{
	case P3D::BPHotPlugEvent::BPHotPlugEventType::Load:
	{
		it->second->onLoadModule();
		break;
	}
	case P3D::BPHotPlugEvent::BPHotPlugEventType::Unload:
	{
		it->second->onUnLoadModule();
		delete it->second;
		m_eventPool.erase(moduleName);
		break;
	}
	default:
		break;
	}

	return true;
}

HOTPLUG_EXPORT void P3D::BPHotPlugEventListener::addListener(std::wstring moduleName,BPHotPlugEvent* handler)
{
	if (handler == nullptr)
		return;
	m_eventPool.insert(make_pair(moduleName, handler));
}

HOTPLUG_EXPORT void P3D::BPHotPlugEventListener::dropListener(std::wstring moduleName)
{
	m_eventPool.erase(moduleName);
}
