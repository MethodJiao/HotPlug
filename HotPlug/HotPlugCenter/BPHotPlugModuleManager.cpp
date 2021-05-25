#include "pch.h"
#include "BPHotPlugModuleManager.h"

using namespace P3D;
using namespace std;
BPHotPlugModuleManager::BPHotPlugModuleManager()
{

}

BPHotPlugModuleManager::~BPHotPlugModuleManager()
{
	m_moduleMap.clear();
}

BPHotPlugModuleManager& P3D::BPHotPlugModuleManager::Get()
{
	static BPHotPlugModuleManager m_instance;
	return m_instance;
}

HINSTANCE P3D::BPHotPlugModuleManager::getModule(std::wstring dllName)
{
	std::map<std::wstring, HINSTANCE>::iterator it = m_moduleMap.find(dllName);
	if (it == m_moduleMap.end())
		return NULL;

	return it->second;
}

DWORD P3D::BPHotPlugModuleManager::loadModuleForManager(std::wstring dllName)
{
	HINSTANCE hmod = LoadLibrary(dllName.c_str());
	DWORD errorCode = GetLastError();
	if (errorCode != 0)
		return errorCode;

	m_moduleMap.insert(make_pair(dllName, hmod));
	BPHotPlugEventListener::Get().notifyListeners(BPHotPlugEvent::BPHotPlugEventType::Load, dllName);
	return 0;
}

DWORD P3D::BPHotPlugModuleManager::unLoadModuleForManager(std::wstring dllName)
{
	std::map<std::wstring, HINSTANCE>::iterator it = m_moduleMap.find(dllName);
	if (it == m_moduleMap.end())
		return NULL;
	BPHotPlugEventListener::Get().notifyListeners(BPHotPlugEvent::BPHotPlugEventType::Unload, dllName);

	FreeLibrary(it->second);
	DWORD errorCode = GetLastError();
	if (errorCode != 0)
		return errorCode;

	m_moduleMap.erase(dllName);
	return 0;
}
