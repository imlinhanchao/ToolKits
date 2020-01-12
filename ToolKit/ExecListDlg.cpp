// ExecListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolKit.h"
#include "ExecListDlg.h"
#include "afxdialogex.h"
#include "ExecItemDlg.h"

// CExecListDlg dialog

IMPLEMENT_DYNAMIC(CExecListDlg, CDialogEx)

CExecListDlg::CExecListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExecListDlg::IDD, pParent)
{

}

CExecListDlg::~CExecListDlg()
{
}

void CExecListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
}

BEGIN_MESSAGE_MAP(CExecListDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CExecListDlg::OnNMDblclkList)
END_MESSAGE_MAP()


// CExecListDlg message handlers

BOOL CExecListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CExecListDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialogEx::PreTranslateMessage(pMsg);
}

HBRUSH CExecListDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return (HBRUSH)::GetStockObject(WHITE_BRUSH);
}

void CExecListDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;
	*pResult = 0;

	if(nRow < 0) return;	

	EXECUTE_ITEM item;
	
	CExecItemDlg ExecDlg;
	ExecDlg.m_exec = m_lstExec.at(nRow);
	if(IDOK == ExecDlg.DoModal())
	{
		m_lstExec.at(nRow) = ExecDlg.m_exec;
		ListModify(ExecDlg.m_exec, nRow);
	}
	*pResult = 0;
}

void CExecListDlg::InitList( void )
{
	CRect rcCli;
	m_List.GetClientRect(&rcCli);
	int nColInterval = (rcCli.Width() - 20) / 4;

	LONG lStyle   = GetWindowLong(m_List.GetSafeHwnd(), GWL_STYLE);
	DWORD dwStyle = m_List.GetExtendedStyle();
	SetWindowLong(m_List.GetSafeHwnd(), GWL_STYLE,  lStyle | LVS_REPORT);
	m_List.SetExtendedStyle(dwStyle | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_NOLABELWRAP); 

	int nIndex = 0;
	m_List.InsertColumn(nIndex++, _T("Name"),		LVCFMT_LEFT, nColInterval);
	m_List.InsertColumn(nIndex++, _T("Program"),	LVCFMT_LEFT, nColInterval);
	m_List.InsertColumn(nIndex++, _T("Arguments"),	LVCFMT_LEFT, nColInterval);
	m_List.InsertColumn(nIndex++, _T("Delay"),		LVCFMT_LEFT, nColInterval / 2);
	m_List.InsertColumn(nIndex++, _T("Visible"),	LVCFMT_LEFT, nColInterval / 2);

	ListRefresh();
}

void CExecListDlg::ListRefresh()
{
	m_lstExec = CExecute::GetList();
	m_List.DeleteAllItems();
	for (size_t i = 0; i < m_lstExec.size(); i++)
	{
		ListPush(m_lstExec.at(i));
	}
}

void CExecListDlg::ListPush( EXECUTE_ITEM item )
{
	int nCount = m_List.GetItemCount();
	int nIndex = 1;
	m_List.InsertItem(nCount, item.sName);
	m_List.SetItemText(nCount, nIndex++, Path::GetFileName(item.sPath));
	m_List.SetItemText(nCount, nIndex++, item.sArgv);
	m_List.SetItemText(nCount, nIndex++, Cvt::ToString(item.dwDelay));
	m_List.SetItemText(nCount, nIndex++, Cvt::ToString(item.bVisible));
}

void CExecListDlg::ListModify( EXECUTE_ITEM item, int nRow )
{
	int nIndex = 0;
	m_List.SetItemText(nRow, nIndex++, item.sName);
	m_List.SetItemText(nRow, nIndex++, Path::GetFileName(item.sPath));
	m_List.SetItemText(nRow, nIndex++, item.sArgv);
	m_List.SetItemText(nRow, nIndex++, Cvt::ToString(item.dwDelay));
	m_List.SetItemText(nRow, nIndex++, Cvt::ToString(item.bVisible));
}

