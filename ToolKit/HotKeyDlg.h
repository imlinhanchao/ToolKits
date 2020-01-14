#pragma once


// CHotKeyDlg dialog

class CHotKeyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHotKeyDlg)

public:
	CHotKeyDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHotKeyDlg();

// Dialog Data
	enum { IDD = IDD_DLG_HOTKEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
};
