#if !defined(AFX_BCLISTCTRL_H__DE87159A_245B_48D3_9DF0_EB764A42AFB2__INCLUDED_)
#define AFX_BCLISTCTRL_H__DE87159A_245B_48D3_9DF0_EB764A42AFB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBCListCtrl window

class CBCListCtrl : public CListCtrl
{
// Construction
public:
	CButton CheckBox[MAXMESSAGECOUNT];
	bool CheckBoxCreateFlag[MAXMESSAGECOUNT];
	int del_flag;
	int type;
	int FirstSelectRow;
	int LastSelectRow;
	CPoint NowPoint;
	void AddNewItem(int ID) ;
	void OnInit();
	void DeletItemCheckBox(int ID);
	void CheckValChange();
	CPoint LDonwUPpoint;
	bool LDonwFlag;
	void SetCheckBoxVal(int ID,bool val) ;
	void OnContextMenu(CWnd *, CPoint point);
	CBCListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void DeleteAllItemCheckBox();
	short ListType;
	virtual ~CBCListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCListCtrl)
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCLISTCTRL_H__DE87159A_245B_48D3_9DF0_EB764A42AFB2__INCLUDED_)
