#include "pch.h"
#include "BPHotPlugEvent.h"
using namespace P3D;

P3D::BPHotPlugEvent::BPHotPlugEvent()
{

}

P3D::BPHotPlugEvent::~BPHotPlugEvent()
{

}

void P3D::BPHotPlugEvent::onLoadModule()
{
	_onLoadModule();
}

void P3D::BPHotPlugEvent::onUnLoadModule()
{
	_onUnLoadModule();
}
