#if !defined(AFX_FIRSTDLG_H__A4331C7E_C8CE_4557_A04A_A3A1F9852207__INCLUDED_)
#define AFX_FIRSTDLG_H__A4331C7E_C8CE_4557_A04A_A3A1F9852207__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FirstDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFirstDlg dialog

class CFirstDlg : public CDialog
{
// Construction
public:
	int board;
	int Countinu;
	int Max_Select_Channel;
	CFirstDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFirstDlg)
	enum { IDD = IDD_FIRSTDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFirstDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFirstDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTDLG_H__A4331C7E_C8CE_4557_A04A_A3A1F9852207__INCLUDED_)
