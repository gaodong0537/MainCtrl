

#if !defined(AFX_RTSELECTDLG_H__02D5E9C6_1D0A_4DC4_8899_D70F9275700F__INCLUDED_)
#define AFX_RTSELECTDLG_H__02D5E9C6_1D0A_4DC4_8899_D70F9275700F__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RTSelectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRTSelectDlg dialog

class CRTSelectDlg : public CDialog
{
// Construction
public:
	CRTSelectDlg(CWnd* pParent = NULL);   // standard constructor
	int NowInsetRt;
// Dialog Data
	//{{AFX_DATA(CRTSelectDlg)
	enum { IDD = IDD_RTSELECT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRTSelectDlg)
	virtual void OnOK();
	afx_msg void OnButton12();
	afx_msg void OnButton13();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTSELECTDLG_H__02D5E9C6_1D0A_4DC4_8899_D70F9275700F__INCLUDED_)
