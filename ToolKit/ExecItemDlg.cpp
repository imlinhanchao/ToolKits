// ExecItemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ToolKit.h"
#include "ExecItemDlg.h"
#include "afxdialogex.h"


// CExecItemDlg dialog

IMPLEMENT_DYNAMIC(CExecItemDlg, CDialogEx)

CExecItemDlg::CExecItemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExecItemDlg::IDD, pParent)
{

}

CExecItemDlg::~CExecItemDlg()
{
}

void CExecItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExecItemDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CExecItemDlg::OnBnClickedBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_EXEC_PATH, &CExecItemDlg::OnBnClickedBtnExecPath)
	ON_BN_CLICKED(IDOK, &CExecItemDlg::OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_DELAY, &CExecItemDlg::OnDeltaposSpinDelay)
END_MESSAGE_MAP()

BOOL CExecItemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	WriteUi(m_exec);
	m_bModify = !m_exec.sName.IsEmpty();
	if (m_bModify)
	{
		SetWindowText(_T("Modify Execute ") + m_exec.sName);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// CExecItemDlg message handlers

void CExecItemDlg::OnBnClickedBtnBrowse()
{
	CString sPath = Path::Browse(_T("All Files (*.*)|*.*;||"), NULL, TRUE, NULL);
	if (sPath.IsEmpty()) return;
	SetDlgItemText(IDC_EDIT_PATH, sPath);
}


void CExecItemDlg::OnBnClickedBtnExecPath()
{
	CString sPath = Path::Browse(_T("All Files (*.*)|*.*;||"), NULL, TRUE, NULL);
	if (sPath.IsEmpty()) return;
	SetDlgItemText(IDC_EDIT_EXEC, sPath);
}

void CExecItemDlg::WriteUi( EXECUTE_ITEM item )
{
	SetDlgItemText(IDC_EDIT_NAME, item.sName);
	SetDlgItemText(IDC_EDIT_PATH, item.sPath);
	SetDlgItemText(IDC_EDIT_ARGU, item.sArgv);
	SetDlgItemText(IDC_EDIT_EXEC, item.sExecPath);
	SetDlgItemInt(IDC_EDIT_DELAY, item.dwDelay);
	((CButton*)GetDlgItem(IDC_CHK_VISIBLE))->SetCheck(item.bVisible ? BST_CHECKED : BST_UNCHECKED);
}

EXECUTE_ITEM CExecItemDlg::ReadUi( void )
{
	EXECUTE_ITEM item;
	GetDlgItemText(IDC_EDIT_NAME, item.sName);
	GetDlgItemText(IDC_EDIT_PATH, item.sPath);
	GetDlgItemText(IDC_EDIT_ARGU, item.sArgv);
	GetDlgItemText(IDC_EDIT_EXEC, item.sExecPath);
	item.dwDelay = GetDlgItemInt(IDC_EDIT_DELAY);
	item.bVisible = ((CButton*)GetDlgItem(IDC_CHK_VISIBLE))->GetCheck() == BST_CHECKED;
	return item;
}

void CExecItemDlg::OnBnClickedOk()
{
	EXECUTE_ITEM exec = ReadUi();
	if (exec.sName.FindOneOf(_T("\\/:*?\"<>|")) >= 0) {
		MessageBox(_T("The Name can't contain \\/:*?\"<>|"), _T(""), MB_OK | MB_ICONWARNING);
		return;
	}

	if (CExecute::Exists(exec.sName)) {
		MessageBox(_T("The Execute Name ") + exec.sName + _T(" was exists."), _T("Execute Exists"), MB_OK | MB_ICONWARNING);
		return;
	}
	m_exec = exec;
	CDialogEx::OnOK();
}


void CExecItemDlg::OnDeltaposSpinDelay(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int nDelay = GetDlgItemInt(IDC_EDIT_DELAY);

	if(pNMUpDown->iDelta >= 0)
	{
		if(nDelay > 0) nDelay--;
	}
	else if(pNMUpDown->iDelta < 0)
	{
		nDelay++;
	}

	SetDlgItemInt(IDC_EDIT_DELAY, nDelay);
	*pResult = 0;
}
