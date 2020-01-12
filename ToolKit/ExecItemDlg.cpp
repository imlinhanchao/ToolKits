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
END_MESSAGE_MAP()


// CExecItemDlg message handlers
