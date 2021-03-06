#pragma once
#include "afxcmn.h"


// CHotKeyListDlg dialog

class CHotKeyListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHotKeyListDlg)

public:
	CHotKeyListDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHotKeyListDlg();

// Dialog Data
	enum { IDD = IDD_DLG_HOTKEYS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

	void InitList(void);

	CListCtrl m_List;
	HOTKEY_LIST m_lstHotKey;

public:
	void ListRefresh();
	void ListPush(HOTKEY_ITEM item);
	void ListModify(HOTKEY_ITEM item, int nRow);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
