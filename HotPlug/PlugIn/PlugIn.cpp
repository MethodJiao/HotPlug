// PlugIn.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "PlugIn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CPlugInApp

BEGIN_MESSAGE_MAP(CPlugInApp, CWinApp)
END_MESSAGE_MAP()

extern "C" _declspec(dllexport) void PlugInFunc()
{
	AfxMessageBox(_T("PlugIn 被调用"));
}
// CPlugInApp 构造

CPlugInApp::CPlugInApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CPlugInApp 对象

CPlugInApp theApp;


// CPlugInApp 初始化

class PlugInEvent:public P3D::BPHotPlugEvent
{
public:
	PlugInEvent();
	~PlugInEvent();

private:

protected:
	virtual bool _onLoadModule() override
	{
		AfxMessageBox(L"PlugIn 加载成功");
		return true;
	}


	virtual bool _onUnLoadModule() override
	{
		AfxMessageBox(L"PlugIn 卸载成功");
		return true;
	}

};

PlugInEvent::PlugInEvent()
{
}

PlugInEvent::~PlugInEvent()
{
}

BOOL CPlugInApp::InitInstance()
{
	CWinApp::InitInstance();
	P3D::BPHotPlugEventListener::Get().addListener(AfxGetApp()->m_hInstance, new PlugInEvent());
	return TRUE;
}
