// HotKeyListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolKit.h"
#include "HotKeyDlg.h"
#include "HotKeyListDlg.h"
#include "afxdialogex.h"


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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CHotKeyListDlg::OnNMDblclkList)
END_MESSAGE_MAP()


BOOL CHotKeyListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// CHotKeyListDlg message handlers

BOOL CHotKeyListDlg::PreTranslateMessage(MSG* pMsg)
{
	if (GetFocus() == GetDlgItem(IDC_LIST) 
	 && pMsg->message == WM_KEYDOWN 
	 && pMsg->wParam == VK_DELETE
	 && IDYES == MessageBox(_T("Are you sure remove there items?"), _T("Remove Program Setting"), MB_YESNO | MB_ICONQUESTION))
	{
		POSITION pos = m_List.GetFirstSelectedItemPosition();
		int nRow = -1, nCount = 0;
		while(pos)
		{
			nRow = m_List.GetNextSelectedItem(pos);
			nRow -= nCount;
			if (nRow < 0) break;
			CHotKey::Remove(m_lstHotKey.at(nRow).dwHotKey);
			m_lstHotKey.erase(m_lstHotKey.begin() + nRow);
			m_List.DeleteItem(nRow);
			nCount ++;
		}
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F5) 
	{
		CHotKey::Load();
		ListRefresh();
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CHotKeyListDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nRow = pNMListView->iItem;
	*pResult = 0;

	if(nRow < 0) return;	

	EXECUTE_ITEM item;
	
	CHotKeyDlg HotKeyDlg;
	HotKeyDlg.m_hotkey = m_lstHotKey.at(nRow);
	if(IDOK == HotKeyDlg.DoModal())
	{
		CHotKey::Modify(m_lstHotKey.at(nRow).dwHotKey, HotKeyDlg.m_hotkey);
		m_lstHotKey.at(nRow) = HotKeyDlg.m_hotkey;
		ListModify(HotKeyDlg.m_hotkey, nRow);
	}
	*pResult = 0;
}

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
	m_List.InsertColumn(nIndex++, _T("Exec Way"),	LVCFMT_LEFT, nColInterval);

	ListRefresh();
}

void CHotKeyListDlg::ListRefresh()
{
	m_lstHotKey = CHotKey::GetList();
	m_List.DeleteAllItems();
	for (size_t i = 0; i < m_lstHotKey.size(); i++)
	{
		ListPush(m_lstHotKey.at(i));
	}
}

void CHotKeyListDlg::ListPush( HOTKEY_ITEM item )
{
	int nCount = m_List.GetItemCount();
	int nIndex = 1;
	m_List.InsertItem(nCount, CHotKey::GetHotKeyName(item.dwHotKey));
	m_List.SetItemText(nCount, nIndex++, item.sName);
	m_List.SetItemText(nCount, nIndex++, CExecute::WAY[item.nExecWay]);
}

void CHotKeyListDlg::ListModify( HOTKEY_ITEM item, int nRow )
{
	int nIndex = 0;
	m_List.SetItemText(nRow, nIndex++, CHotKey::GetHotKeyName(item.dwHotKey));
	m_List.SetItemText(nRow, nIndex++, item.sName);
	m_List.SetItemText(nRow, nIndex++, CExecute::WAY[item.nExecWay]);
}

