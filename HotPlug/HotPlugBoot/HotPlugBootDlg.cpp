
// HotPlugBootDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "HotPlugBoot.h"
#include "HotPlugBootDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHotPlugBootDlg 对话框

using namespace P3D;

CHotPlugBootDlg::CHotPlugBootDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOTPLUGBOOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHotPlugBootDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CHotPlugBootDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHotPlugBootDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CHotPlugBootDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CHotPlugBootDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CHotPlugBootDlg 消息处理程序

BOOL CHotPlugBootDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

	m_listCtrl.InsertColumn(0, _T("模块名"), LVCFMT_LEFT, 300);
	m_listCtrl.InsertColumn(1, _T("装态"), LVCFMT_LEFT, 300);

	m_listCtrl.InsertItem(0, _T("PlugIn.dll"));
	m_listCtrl.SetItemText(0, 1, _T("未加载"));

	m_listCtrl.InsertItem(1, _T("PlugInSec.dll"));
	m_listCtrl.SetItemText(1, 1, _T("未加载"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHotPlugBootDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHotPlugBootDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHotPlugBootDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//加载
void CHotPlugBootDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	int nIdx = m_listCtrl.GetSelectionMark();
	if (nIdx < 0)
		return;

	CString szVal = m_listCtrl.GetItemText(nIdx, 0);
	DWORD errorCode = BPHotPlugModuleManager::Get().loadModuleForManager(szVal.GetBuffer());
	if (errorCode != 0)
		return;

	m_listCtrl.SetItemText(nIdx, 1, _T("已加载！"));
}

//卸载
void CHotPlugBootDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	int nIdx = m_listCtrl.GetSelectionMark();
	if (nIdx < 0)
		return;
	CString szVal = m_listCtrl.GetItemText(nIdx, 0);
	DWORD errorCode = BPHotPlugModuleManager::Get().unLoadModuleForManager(szVal.GetBuffer());
	if (errorCode != 0)
		return;

	m_listCtrl.SetItemText(nIdx, 1, _T("已卸载"));
}
typedef void (*PlugInFunc)();
//执行
void CHotPlugBootDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIdx = m_listCtrl.GetSelectionMark();
	if (nIdx < 0)
		return;
	CString szVal = m_listCtrl.GetItemText(nIdx, 0);
	HINSTANCE hmod = BPHotPlugModuleManager::Get().getModule(szVal.GetBuffer());

	if (hmod == NULL)
	{
		m_listCtrl.SetItemText(nIdx, 1, _T("未被加载"));
		return;
	}

	PlugInFunc lpPlugInFunc;
	lpPlugInFunc = (PlugInFunc)GetProcAddress(hmod, "PlugInFunc");
	if (lpPlugInFunc == nullptr)
		return;

	(*lpPlugInFunc)();
}

