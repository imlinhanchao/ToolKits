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
}


BEGIN_MESSAGE_MAP(CHotKeyDlg, CDialogEx)
END_MESSAGE_MAP()


// CHotKeyDlg message handlers


BOOL CHotKeyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
