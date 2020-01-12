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
