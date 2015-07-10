#if !defined(AFX_RTVIEWDLG_H__7119914F_A7FA_41C3_8A92_5F7E3C7C0E73__INCLUDED_)
#define AFX_RTVIEWDLG_H__7119914F_A7FA_41C3_8A92_5F7E3C7C0E73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RTViewDlg.h : header file
//
#include "RTListCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CRTViewDlg dialog

class CRTViewDlg : public CDialog
{
// Construction
public:
	void DeleteRT();
	void SetRTViewData(int rtadrss,int subadress,API_RT_MBUF_WRITE data,bool flag);
	int subAdressTocount[32];
	bool SubAdressShow[32];
	CRTViewDlg(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CRTViewDlg)
	enum { IDD = IDD_RTVIEW };
	CRTListCtrl	m_RT_DataList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTViewDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void Serialize(CArchive& ar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRTViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTVIEWDLG_H__7119914F_A7FA_41C3_8A92_5F7E3C7C0E73__INCLUDED_)
