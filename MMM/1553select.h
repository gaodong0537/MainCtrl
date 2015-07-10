#if !defined(AFX_1553SELECT_H__712C93CF_CF57_4142_A976_6E1D02C66425__INCLUDED_)
#define AFX_1553SELECT_H__712C93CF_CF57_4142_A976_6E1D02C66425__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 1553select.h : header file
//
#include "TabProjDlg.h"
/////////////////////////////////////////////////////////////////////////////
// C1553select dialog

class C1553select : public CDialog
{
// Construction
public:
	CTabProjDlg ProjectTabDlg[2];
	
	bool CreatedFlag;
	C1553select(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C1553select)
	enum { IDD = IDD_1553SEL };
	CTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C1553select)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C1553select)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1553b(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1553SELECT_H__712C93CF_CF57_4142_A976_6E1D02C66425__INCLUDED_)
