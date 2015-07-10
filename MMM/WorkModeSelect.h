#if !defined(AFX_WORKMODESELECT_H__23DA235B_7B47_4945_8104_ED80CF3337BB__INCLUDED_)
#define AFX_WORKMODESELECT_H__23DA235B_7B47_4945_8104_ED80CF3337BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkModeSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorkModeSelect dialog

class CWorkModeSelect : public CDialog
{
// Construction
public:
	CWorkModeSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkModeSelect)
	enum { IDD = IDD_WORKMODE };
	BOOL	m_bmmode;
	BOOL	m_rtmode;
	BOOL	m_bcmode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkModeSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWorkModeSelect)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKMODESELECT_H__23DA235B_7B47_4945_8104_ED80CF3337BB__INCLUDED_)
