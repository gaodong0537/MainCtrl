#if !defined(AFX_MONITORCONFIGDLG_H__5FFDC65F_3207_40DF_850B_2F034F36A4BC__INCLUDED_)
#define AFX_MONITORCONFIGDLG_H__5FFDC65F_3207_40DF_850B_2F034F36A4BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonitorConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMonitorConfigDlg dialog

class CMonitorConfigDlg : public CDialog
{
// Construction
public:
	

	int chartoint(char val);
	int HexToInt(CString str,int len);
	void ADDCondtion(int addCondID,int Adress,int SubAdress,CString FileName)  ;
	bool ShowFlag_1553Data[32];
	bool NowFlag[32][32];
	CMonitorConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMonitorConfigDlg)
	enum { IDD = IDD_MONITORCONFIG };
	CListCtrl	m_StutasList;
	CListCtrl	m_VectorList;
	CListCtrl	m_FileCondtionList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitorConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMonitorConfigDlg)
	afx_msg void OnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton14();
	afx_msg void OnButton15();
	afx_msg void OnCheck1();
	afx_msg void OnButton16();
	afx_msg void OnButtonADD();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonDelete();
	afx_msg void OnCheck59();
	afx_msg void OnOk();
	afx_msg void OnButton122();
	afx_msg void OnButton123();
	afx_msg void OnButton124();
	afx_msg void OnButton3();
	afx_msg void OnButton5();
	afx_msg void OnButton4();
	afx_msg void OnButton22();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORCONFIGDLG_H__5FFDC65F_3207_40DF_850B_2F034F36A4BC__INCLUDED_)
