#if !defined(AFX_BMVIEW_H__1925BD04_924D_4856_A12F_32E4D97CB18D__INCLUDED_)
#define AFX_BMVIEW_H__1925BD04_924D_4856_A12F_32E4D97CB18D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BMview.h : header file
//
#include "BtnST.h"
#include "GetMessageListCtl.h"
#include "DataShowDlg.h"
#include "afxmt.h"
/////////////////////////////////////////////////////////////////////////////
// CBMview dialog

class CBMview : public CDialog
{
// Construction
public:

	HWND s_hWnd;
	
	bool ModeShow;
	CRect MaxRect;
	CRect rect2,rect;
	int HaveCreate;
	DataShowDlg DataDlg;
	CPoint NowPoint;

	CButtonST m_Save;
	CButtonST m_Open;
	CButtonST m_Add;
	CButtonST m_Get;
	CButtonST m_ShowMode;
	CButtonST m_ClearView;

	HANDLE hThread;

	DWORD ThreadID;

	
	int MessageCountRead;
	CString FileNameReadFile;

	 void OnSaveData();
	static void ReadDataFunc();
	bool firstflag;
	bool ReadDataFlag;
	bool CountiuFlag;
	HANDLE Thread;
	static UINT ReadDataFuncThre(LPVOID lpV);

	bool Exce_Flag[32][32];
	int read_firstTime;

	int messCount;

	CString InttoTimerStr(unsigned int val);
	CString InttoTimerStr_1(unsigned int val);
	static void ShowMessageData(CBMview* m,API_BM_MBUF Messagedata);
	
	void InitBM();
	void ShowDataDlg(int SelID);
	void HideDataDlg();
	void ShowModeChange(bool mode);
	void OnButtonDown();
	void ShowReadData(API_BM_MBUF Messagedata,int firstTime);
	
	void OnButton7();
	CBMview(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBMview)
	enum { IDD = IDD_BMMESSAGEVIEW };
	GetMessageListCtl	m_GetMessagelist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBMview)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBMview)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnReadData();
	afx_msg void OnShowMode();
	afx_msg void OnGetData();
	afx_msg void OnButton3();
	afx_msg void OnClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonShowMode();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnButton6();
	afx_msg void OnDestroy();
	afx_msg void OnGetdispinfoList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClearview();
	afx_msg void OnButton9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMVIEW_H__1925BD04_924D_4856_A12F_32E4D97CB18D__INCLUDED_)
