// FirstDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "FirstDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirstDlg dialog


CFirstDlg::CFirstDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFirstDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFirstDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFirstDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFirstDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFirstDlg, CDialog)
	//{{AFX_MSG_MAP(CFirstDlg)
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFirstDlg message handlers

BOOL CFirstDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CString str;
	int i;
	for(i=0;i<4;i++)
	{
		str.Format("%d",i+1);
		((CComboBox *)GetDlgItem(IDC_COMBO1))->InsertString(i,str);
	}
	((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(1);


	SetDlgItemText(IDC_EDIT1,"0");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFirstDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString boardStr;
	GetDlgItemText(IDC_EDIT1,boardStr);
	board=atoi(boardStr);
	Countinu = 0;
	Max_Select_Channel = ((CComboBox *)GetDlgItem(IDC_COMBO1))->GetCurSel();
	CDialog::OnOK();
}

void CFirstDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	Countinu = 1;
	CDialog::OnOK();
}

void CFirstDlg::OnEditchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	
}

void CFirstDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	int Select_Channel;
	CString m_str;
	CString boardStr;
	GetDlgItemText(IDC_EDIT1,boardStr);
	board=atoi(boardStr);

	Select_Channel = ((CComboBox *)GetDlgItem(IDC_COMBO1))->GetCurSel()+1;
	if(Select_Channel>1)
	{
		m_str.Format("确认板卡%d为%d通道1553B卡,如不是可能会导致程序异常",board,Select_Channel);
		MessageBox(m_str,"注意",MB_OK);
	}
}
