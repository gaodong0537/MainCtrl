#if !defined(AFX_RTLISTCTRL_H__85D2C421_19CB_448C_B1ED_CFC1C6A8AE6D__INCLUDED_)
#define AFX_RTLISTCTRL_H__85D2C421_19CB_448C_B1ED_CFC1C6A8AE6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RTListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRTListCtrl window

class CRTListCtrl : public CListCtrl
{
// Construction
public:
	int del_flag;
	CPoint NowPoint;
	void OnContextMenu(CWnd *, CPoint point);
	CRTListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRTListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRTListCtrl)
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTLISTCTRL_H__85D2C421_19CB_448C_B1ED_CFC1C6A8AE6D__INCLUDED_)
