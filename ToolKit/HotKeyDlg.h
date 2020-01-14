#pragma once
#include "afxcmn.h"


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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	void LoadExecuteList();
	void WriteUi(HOTKEY_ITEM item);
	HOTKEY_ITEM ReadUi(void);

	CHotKeyCtrl m_HotKeyCtrl;

public:
	HOTKEY_ITEM m_hotkey;
};
