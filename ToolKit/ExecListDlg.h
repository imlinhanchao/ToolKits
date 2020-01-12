#pragma once
#include "afxcmn.h"


// CExecListDlg dialog

class CExecListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExecListDlg)

public:
	CExecListDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CExecListDlg();

// Dialog Data
	enum { IDD = IDD_DLG_EXECS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()

	void InitList(void);

	CListCtrl m_List;
	EXECUTE_LIST m_lstExec;

public:
	void ListRefresh();
	void ListPush(EXECUTE_ITEM item);
	void ListModify(EXECUTE_ITEM item, int nRow);
};
