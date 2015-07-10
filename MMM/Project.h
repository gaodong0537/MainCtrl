//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_PROJECT_H__0D55505E_6294_4EDF_9D67_C143457C95D2__INCLUDED_)
#define AFX_PROJECT_H__0D55505E_6294_4EDF_9D67_C143457C95D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Project.h : header file
//
# include "NewTreeCtrl.h"
#include "BtnST.h"
#include "RxStatic.h"
/////////////////////////////////////////////////////////////////////////////
// CProject dialog

class CProject : public CDialog
{
// Construction
public:
	bool ReadFlag;
	void DeleteRT(int RT_ID);
	void SetRTIcon(int RT_ID ,bool flag_val);
	
	CButtonST m_RunBC;
	CButtonST m_StopBC;
	CButtonST m_StepBC;
	CButtonST m_RunRT;
	CButtonST m_StopRT;
	CButtonST m_EditBC;
	CButtonST m_EditRT;

	void MoveDownBCMessage(int type,int ID);
	void MoveUpBCMessage(int type,int ID);
	void EnableMessage(int tyep,int ID);
	void DisableMessage(int tyep,int ID);

	bool InitAllSet();
	bool InitTimeSet();
	bool InitNoTimeSet();
	void InsertTreeData(int type,CString Name,int messageid);
	void ChangeTreeData(int type,CString Name,int messageid);
	CImageList m_ImageList;
	HTREEITEM RootItem,NextItem,InsertItemBC,InsertItemRT,InsertItemBC_NOtime,InsertItemBC_time,InsertItemBM
		,BCItemNo[MAXMESSAGECOUNT],BCItem[MAXMESSAGECOUNT],RTItem[32],InsertItemIO;
	CProject(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProject)
	enum { IDD = IDD_PROJECT };
	CRxStatic	m_static01;
	CStatic	m_RTstutas;
	CStatic	m_BCstutas;
	NewTreeCtrl	m_Tree;
	CRxStatic	m_static02;
	CRxStatic	m_static03;
	CRxStatic	m_static04;
	CRxStatic	m_static05;
	CRxStatic	m_static06;
	CRxStatic	m_static07;
	CRxStatic	m_static08;
	CRxStatic	m_static09;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProject)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProject)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRunBC();
	afx_msg void OnStopBC();
	afx_msg void OnStepBC();
	afx_msg void OnRunRT();
	afx_msg void OnStopRT();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtoneEditBc();
	afx_msg void OnButtonEditRT();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECT_H__0D55505E_6294_4EDF_9D67_C143457C95D2__INCLUDED_)
