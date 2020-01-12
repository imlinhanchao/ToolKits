#pragma once


// CExecItemDlg dialog

class CExecItemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExecItemDlg)

public:
	CExecItemDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExecItemDlg();

// Dialog Data
	enum { IDD = IDD_DLG_EXEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
