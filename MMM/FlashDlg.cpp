// FlashDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "FlashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlashDlg dialog


CFlashDlg::CFlashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFlashDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlashDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFlashDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlashDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFlashDlg, CDialog)
	//{{AFX_MSG_MAP(CFlashDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlashDlg message handlers

void CFlashDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	OnOK() ;
	KillTimer(0);
	CDialog::OnTimer(nIDEvent);
}

BOOL CFlashDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetTimer(0,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
