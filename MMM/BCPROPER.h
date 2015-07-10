

//{{AFX_INCLUDES()
#include "TypeDefine.h"
//}}AFX_INCLUDES

#if !defined(AFX_BCPROPER_H__8355ACBF_7201_4345_8F17_D9B165DA60C6__INCLUDED_)
#define AFX_BCPROPER_H__8355ACBF_7201_4345_8F17_D9B165DA60C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCPROPER.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBCPROPER dialog

class CBCPROPER : public CDialog
{
// Construction
public:
	BT_U16BIT wRetry;
	BC_RetryType		multiple_retryval;
	int Maxcount;
	int frameTime;
	int GrapTime;
	CBCPROPER(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBCPROPER)
	enum { IDD = IDD_BCPROPER };
	int		m_BCcount;
	int		m_Frametimer;
	int		m_Graptimer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCPROPER)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBCPROPER)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck1();
	afx_msg void OnCheck15();
	afx_msg void OnCheck9();
	afx_msg void OnCheck2();
	afx_msg void OnCheck10();
	afx_msg void OnCheck11();
	afx_msg void OnCheck12();
	afx_msg void OnCheck13();
	afx_msg void OnCheck14();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCPROPER_H__8355ACBF_7201_4345_8F17_D9B165DA60C6__INCLUDED_)
