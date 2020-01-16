// HotKeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolKit.h"
#include "HotKeyDlg.h"
#include "afxdialogex.h"


// CHotKeyDlg dialog

IMPLEMENT_DYNAMIC(CHotKeyDlg, CDialogEx)

CHotKeyDlg::CHotKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHotKeyDlg::IDD, pParent)
{

}

CHotKeyDlg::~CHotKeyDlg()
{
}

void CHotKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HOTKEY1, m_HotKeyCtrl);
}


BEGIN_MESSAGE_MAP(CHotKeyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHotKeyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHotKeyDlg message handlers


BOOL CHotKeyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LoadExecuteList();
	if (0 != m_hotkey.dwHotKey)
	{
		WriteUi(m_hotkey);
		SetWindowText(_T("Modify HotKey ") + CHotKey::GetHotKeyName(m_hotkey.dwHotKey));
		SetDlgItemText(IDOK, _T("Modify"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CHotKeyDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		m_HotKeyCtrl.SetHotKey(VK_ESCAPE, 0);
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CHotKeyDlg::OnBnClickedOk()
{
	HOTKEY_ITEM hotkey = ReadUi();

	if (CHotKey::Exists(hotkey.dwHotKey) && m_hotkey.dwHotKey != hotkey.dwHotKey) {
		MessageBox(_T("The HotKey ") + CHotKey::GetHotKeyName(hotkey.dwHotKey) + _T(" was exists in Setting."), _T("HotKey Exists"), MB_OK | MB_ICONWARNING);
		return;
	}

	CHotKey::RemoveHotKey(m_hotkey.dwHotKey);
	if (!CHotKey::SetHotKey(hotkey.dwHotKey))
	{
		MessageBox(_T("The HotKey ") + CHotKey::GetHotKeyName(hotkey.dwHotKey) + _T(" was exists in System."), _T("HotKey Exists"), MB_OK | MB_ICONWARNING);
		return;
	}

	m_hotkey = hotkey;
	CDialogEx::OnOK();
}

void CHotKeyDlg::LoadExecuteList()
{
	EXECUTE_LIST lstExecute = CExecute::GetList();
	for (size_t i = 0; i < lstExecute.size(); i++)
	{
		((CComboBox*)GetDlgItem(IDC_CMB_EXEC))->AddString(lstExecute.at(i).sName);
	}
	((CComboBox*)GetDlgItem(IDC_CMB_EXEC))->SetCurSel(0);
}

void CHotKeyDlg::WriteUi( HOTKEY_ITEM item )
{
	m_HotKeyCtrl.SetHotKey(item.dwHotKey & 0xff, item.dwHotKey >> 0x08);
	((CComboBox*)GetDlgItem(IDC_CMB_EXEC))->SetCurSel(((CComboBox*)GetDlgItem(IDC_CMB_EXEC))->FindStringExact(0, item.sName.GetBuffer()));
	item.sName.ReleaseBuffer();
}

HOTKEY_ITEM CHotKeyDlg::ReadUi( void )
{
	HOTKEY_ITEM item;
	item.dwHotKey = m_HotKeyCtrl.GetHotKey();
	GetDlgItemText(IDC_CMB_EXEC, item.sName);
	return item;
}
