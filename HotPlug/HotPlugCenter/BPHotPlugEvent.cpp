#include "pch.h"
#include "BPHotPlugEvent.h"
using namespace P3D;

P3D::BPHotPlugEvent::BPHotPlugEvent()
{

}

P3D::BPHotPlugEvent::~BPHotPlugEvent()
{

}

bool P3D::BPHotPlugEvent::onLoadModule()
{
	return _onLoadModule();
}

bool P3D::BPHotPlugEvent::onUnLoadModule()
{
	return _onUnLoadModule();
}
