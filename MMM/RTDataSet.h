//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_RTDATASET_H__1E57B6A3_237D_46FB_833A_84AE495D594E__INCLUDED_)
#define AFX_RTDATASET_H__1E57B6A3_237D_46FB_833A_84AE495D594E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RTDataSet.h : header file
//
#include "BtnST.h"
/////////////////////////////////////////////////////////////////////////////
// CRTDataSet dialog

class CRTDataSet : public CDialog
{
// Construction
public:
	int vectorword;
	int SubAdress;
	int IniType;
	int RTAdress;
	int statusword;
	int chartoint(char val);
	int HexToInt(CString str,int len);
	CRTDataSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRTDataSet)
	enum { IDD = IDD_RTDATASET };
	CButtonST	m_Button2;
	CButtonST	m_Button1;
	CStatic	m_Static1;
	CListCtrl	m_VectorList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTDataSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRTDataSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck7();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButtonCreateRond();
	afx_msg void OnButtonCreatezero();
	afx_msg void OnButtonCreataff();
	afx_msg void OnButtonCreateadd();
	afx_msg void OnButton11();
	afx_msg void OnButtonOK();
	afx_msg void OnButtonADDvec();
	afx_msg void OnButtonEnableContrl();
	afx_msg void OnCheck124Enable();
	afx_msg void OnButtonAllEnable();
	afx_msg void OnButtonAllDisable();
	afx_msg void OnButton5();
	afx_msg void OnButton22();
	afx_msg void OnSelchangeSubadress();
	afx_msg void OnSelchangeAdress4();
	afx_msg void OnCheckVectorEnableFlash();
	afx_msg void OnButtonAddvector();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTDATASET_H__1E57B6A3_237D_46FB_833A_84AE495D594E__INCLUDED_)
