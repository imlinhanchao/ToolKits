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
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnBnClickedBtnExecPath();
	afx_msg void OnDeltaposSpinDelay(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()

	void WriteUi(EXECUTE_ITEM item);
	EXECUTE_ITEM ReadUi(void);

public:
	EXECUTE_ITEM m_exec;
};
