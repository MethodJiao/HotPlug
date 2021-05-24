#pragma once
#if defined (HOTPLUGCENTER_EXPORTS)
#define HOTPLUG_EXPORT __declspec(dllexport)
#else
#define HOTPLUG_EXPORT __declspec(dllimport)
#endif
#include <map>
#include <string>
#include "BPHotPlugEvent.h"
#include "BPHotPlugEventListener.h"
#include "BPHotPlugModuleManager.h"