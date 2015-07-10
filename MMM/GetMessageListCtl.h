#if !defined(AFX_GETMESSAGELISTCTL_H__CE533644_E188_4EC7_85A2_0482239E0DBE__INCLUDED_)
#define AFX_GETMESSAGELISTCTL_H__CE533644_E188_4EC7_85A2_0482239E0DBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetMessageListCtl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GetMessageListCtl window

class GetMessageListCtl : public CListCtrl
{
// Construction
public:
	CPoint OldPoint,NewPoint,NowPoint;
	void Init();
	GetMessageListCtl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GetMessageListCtl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~GetMessageListCtl();

	// Generated message map functions
protected:
	//{{AFX_MSG(GetMessageListCtl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETMESSAGELISTCTL_H__CE533644_E188_4EC7_85A2_0482239E0DBE__INCLUDED_)
