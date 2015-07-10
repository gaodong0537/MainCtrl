#if !defined(AFX_DATASHOWDLG_H__5519A8D2_F00D_4512_AC5D_107E82E402AB__INCLUDED_)
#define AFX_DATASHOWDLG_H__5519A8D2_F00D_4512_AC5D_107E82E402AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataShowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DataShowDlg dialog

class DataShowDlg : public CDialog
{
// Construction
public:
	int chartoint(char val);
	int HexToInt(CString str,int len);
	void ShowVal(int SelectID);
	CString FileNameTempSave;
	DataShowDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DataShowDlg)
	enum { IDD = IDD_SHOWDATA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DataShowDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DataShowDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASHOWDLG_H__5519A8D2_F00D_4512_AC5D_107E82E402AB__INCLUDED_)
