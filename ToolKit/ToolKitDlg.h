
// ToolKitDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CToolKitDlg dialog
class CToolKitDlg : public CDialogEx
{
// Construction
public:
	CToolKitDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TOOLKIT_DIALOG };
// Tab Dialog ID
	enum { DLG_HOKEYS = 0, DLG_EXEC, DLG_QTY };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTcnSelchangeTabFeature(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnExecute();
	DECLARE_MESSAGE_MAP()

	void InitTab(void);

	CDialogEx*	m_pTabDlg[DLG_QTY];
	CTabCtrl	m_TabCtrl;
	int			m_nCurPage;
public:
	afx_msg void OnBnClickedBtnHotkey();
};
