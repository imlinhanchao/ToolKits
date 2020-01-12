// HotKeyListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolKit.h"
#include "HotKeyListDlg.h"
#include "afxdialogex.h"
#include "ExecItemDlg.h"


// CHotKeyListDlg dialog

IMPLEMENT_DYNAMIC(CHotKeyListDlg, CDialogEx)

CHotKeyListDlg::CHotKeyListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHotKeyListDlg::IDD, pParent)
{

}

CHotKeyListDlg::~CHotKeyListDlg()
{
}

void CHotKeyListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}


BEGIN_MESSAGE_MAP(CHotKeyListDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


BOOL CHotKeyListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// CHotKeyListDlg message handlers

HBRUSH CHotKeyListDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);
}

void CHotKeyListDlg::InitList( void )
{
	CRect rcCli;
	m_List.GetClientRect(&rcCli);
	int nColInterval = (rcCli.Width() - 20) / 3;

	LONG lStyle   = GetWindowLong(m_List.GetSafeHwnd(), GWL_STYLE);
	DWORD dwStyle = m_List.GetExtendedStyle();
	SetWindowLong(m_List.GetSafeHwnd(), GWL_STYLE,  lStyle | LVS_REPORT);
	m_List.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_NOLABELWRAP); 

	int nIndex = 0;
	m_List.InsertColumn(nIndex++, _T("Hot Key"),	LVCFMT_LEFT, nColInterval);
	m_List.InsertColumn(nIndex++, _T("Execute"),	LVCFMT_LEFT, nColInterval);
	m_List.InsertColumn(nIndex++, _T("Program"),	LVCFMT_LEFT, nColInterval);
}

