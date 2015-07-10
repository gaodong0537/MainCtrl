
#if !defined(AFX_BCVIEWDLG_H__81021CDD_3FCE_4D87_BCC7_D0FEAB139873__INCLUDED_)
#define AFX_BCVIEWDLG_H__81021CDD_3FCE_4D87_BCC7_D0FEAB139873__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCViewDlg.h : header file
//
#include "BCListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CBCViewDlg dialog

class CBCViewDlg : public CDialog
{
// Construction
public:
	void MoveDownBCMessage(int type,int NowMoveID);
	void MoveUpBCMessage(int type,int NowMoveID);
	CRect MaxRect;
	int HaveCreate;
	
	
	CBCViewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBCViewDlg)
	enum { IDD = IDD_BCVIEW };
	CBCListCtrl	m_BC_MesList2;
	CBCListCtrl	m_BC_MesList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCViewDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBCViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkBCViewList(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCVIEWDLG_H__81021CDD_3FCE_4D87_BCC7_D0FEAB139873__INCLUDED_)
