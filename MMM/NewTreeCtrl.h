#if !defined(AFX_NEWTREECTRL_H__EF9F1DB0_6642_4E4F_844D_71A10E8B0029__INCLUDED_)
#define AFX_NEWTREECTRL_H__EF9F1DB0_6642_4E4F_844D_71A10E8B0029__INCLUDED_

#include "RxMenu.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NewTreeCtrl window

class NewTreeCtrl : public CTreeCtrl
{
// Construction
public:
	NewTreeCtrl();
	
// Attributes
public:

// Operations
public:
	bool ExPandFlag;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NewTreeCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	HTREEITEM NowClickItem;
	CRxMenu menu;
	
	HTREEITEM finditem(HTREEITEM item,CPoint point);
	void RClickSelectItem(CPoint point);
	CPoint Nowpoint;
	bool BCRun_flag;
	void OnContextMenu(CWnd*, CPoint point,int type,int del_flag);
	void InitMenu(int menuid ,int type,int del_flag);
	virtual ~NewTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(NewTreeCtrl)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWTREECTRL_H__EF9F1DB0_6642_4E4F_844D_71A10E8B0029__INCLUDED_)
