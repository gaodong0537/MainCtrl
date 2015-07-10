#if !defined(AFX_TABPROJDLG_H__2510999B_BDD9_4B32_A2F6_91B27D51387F__INCLUDED_)
#define AFX_TABPROJDLG_H__2510999B_BDD9_4B32_A2F6_91B27D51387F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabProjDlg.h : header file
//
#include "Project.h"

/////////////////////////////////////////////////////////////////////////////
// CTabProjDlg dialog

class CTabProjDlg : public CDialog
{
// Construction
public:
	CProject ProjectDlg[4];

	bool CreatedFlag;
	int  m_iTabProjDlgNum;
	CTabProjDlg(CWnd* pParent = NULL);   // standard constructor

	void SetTabProjDlgNum(int num);

// Dialog Data
	//{{AFX_DATA(CTabProjDlg)
	enum { IDD = IDD_CONTROLDIALOG };
	CTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabProjDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabProjDlg)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABPROJDLG_H__2510999B_BDD9_4B32_A2F6_91B27D51387F__INCLUDED_)
