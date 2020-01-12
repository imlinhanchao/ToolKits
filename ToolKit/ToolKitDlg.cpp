
// ToolKitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolKit.h"
#include "ToolKitDlg.h"
#include "afxdialogex.h"
#include "ExecItemDlg.h"
#include "HotKeyListDlg.h"
#include "ExecListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CToolKitDlg dialog




CToolKitDlg::CToolKitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CToolKitDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nCurPage = 0;
}

void CToolKitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_FEATURE, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CToolKitDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_FEATURE, &CToolKitDlg::OnTcnSelchangeTabFeature)
	ON_BN_CLICKED(IDC_BTN_EXECUTE, &CToolKitDlg::OnBnClickedBtnExecute)
END_MESSAGE_MAP()


// CToolKitDlg message handlers

BOOL CToolKitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CConfig::Init();
	CExecute::Load();
	InitTab();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CToolKitDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CToolKitDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CToolKitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CToolKitDlg::OnTcnSelchangeTabFeature(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_nCurPage = m_TabCtrl.GetCurSel();
	for (int i = 0; i < DLG_QTY; i++)
	{
		m_pTabDlg[i]->ShowWindow(i == m_nCurPage ? SW_SHOW : SW_HIDE);
	}
	*pResult = 0;
}

void CToolKitDlg::InitTab( void )
{
	const TCHAR* szTabTitles[DLG_QTY] = {
		_T("HotKeys"),
		_T("Execute"),
	};

	CDialogEx* Dialogs[DLG_QTY] = {
		new CHotKeyListDlg,
		new CExecListDlg,
	};

	DWORD dwDialogID[DLG_QTY] = {
		IDD_DLG_HOTKEYS,
		IDD_DLG_EXECS,
	};

	CRect rc;
	CRect rcItem;
	m_TabCtrl.GetClientRect(&rc);
	m_TabCtrl.GetItemRect(0, rcItem);
	rc.top	  += rcItem.bottom + 2; 
	rc.bottom -= 4; 
	rc.left	  += 2; 
	rc.right  -= 4;

	for (int i = 0; i < DLG_QTY; i++)
	{
		m_TabCtrl.InsertItem(i, szTabTitles[i]);
		m_pTabDlg[i] = Dialogs[i];
		m_pTabDlg[i]->Create(dwDialogID[i], &m_TabCtrl); 
		m_pTabDlg[i]->ShowWindow(SW_HIDE);
		m_pTabDlg[i]->MoveWindow(rc);
	}

	m_pTabDlg[0]->ShowWindow(SW_SHOW);
}

void CToolKitDlg::OnBnClickedBtnExecute()
{
	CExecItemDlg ExecDlg;
	if(IDOK != ExecDlg.DoModal()) return;

	CExecute::Write(ExecDlg.m_exec);
}
