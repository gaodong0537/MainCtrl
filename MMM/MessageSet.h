//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_MESSAGESET_H__4CBDF351_8BDC_450A_B3F5_41B5167BFC5D__INCLUDED_)
#define AFX_MESSAGESET_H__4CBDF351_8BDC_450A_B3F5_41B5167BFC5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageSet dialog

class CMessageSet : public CDialog
{
// Construction
public:
	int chartoint(char val);
	int HexToInt(CString str,int len);
	CString MessageName;

	short NowAddMessageTyep;
	int wcount_mode;
	int tran_rec_Mode;
	int IniType;
	int GapTime;
	int nowMessageNo;
	int MessageTyep;
	int InitData[32];
	int address,subaddr,wcount,address2,subaddr2,wcount2;
	int chanA_B;
	void LedShow(int type);
	int  Mode;
	CMessageSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessageSet)
	enum { IDD = IDD_DIALOG1 };
	CStatic	m_StutasRTRT;
	CStatic	m_StutasRTBC;
	CStatic	m_StutasMODE;
	CStatic	m_StutasBCRT;
	CComboBox	GBoxAddress;
	CComboBox	m_WCount;
	CComboBox	m_SubAdress;
	CComboBox	m_RTAdress;
	CComboBox	m_WCount2;
	CComboBox	m_SubAdress2;
	CComboBox	m_RTAdress2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageSet)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	virtual void OnOK();
	afx_msg void OnCheck1();
	afx_msg void OnRadio17();
	afx_msg void OnSelchangeCombo9();
	afx_msg void OnCheck4();
	afx_msg void OnCheck8();
	afx_msg void OnButtonBCRT();
	afx_msg void OnButtonRTBC();
	afx_msg void OnButtonRTRT();
	afx_msg void OnButtonMODE();
	afx_msg void OnButtonCreateRond();
	afx_msg void OnButtonCreatezero();
	afx_msg void OnButtonCreataff();
	afx_msg void OnButtonCreateadd();
	afx_msg void OnButton11();
	afx_msg void OnButton13();
	afx_msg void OnButtonOK();
	afx_msg void OnCheck7();
	afx_msg void OnCheck12();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGESET_H__4CBDF351_8BDC_450A_B3F5_41B5167BFC5D__INCLUDED_)
