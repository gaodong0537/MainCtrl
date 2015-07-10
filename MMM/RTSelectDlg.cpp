// RTSelectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "RTSelectDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTSelectDlg dialog


CRTSelectDlg::CRTSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRTSelectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRTSelectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRTSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRTSelectDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRTSelectDlg, CDialog)
	//{{AFX_MSG_MAP(CRTSelectDlg)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRTSelectDlg message handlers

BEGIN_EVENTSINK_MAP(CRTSelectDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CRTSelectDlg)
	
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/*
void CRTSelectDlg::OnClickCwboolean32() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<32;i++)
	{
		((CCWButton*)GetDlgItem(IDC_CWBOOLEAN0+i))->SetValue(true);
	}
}
*/
void CRTSelectDlg::OnOK() 
{
	// TODO: Add extra validation here
	int i;
	bool Val;
	CString inSertName;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	for(i=0;i<32;i++)
	{
		if(((CButton*)GetDlgItem(IDC_CHECK1+i))->GetCheck()==true)
		{
			if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data_Exsit[i]==false)//判断该RT是否也存在
			{
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data_Exsit[i] = true;
				inSertName.Format("RT%2d",i);
				m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].InsertTreeData(1,inSertName,i);
				NowInsetRt = i;
				m_pMainWnd->RTView[m_pMainWnd->m_now_SelectChannel][i].ShowWindow(SW_SHOW);
				m_pMainWnd->RTView[m_pMainWnd->m_now_SelectChannel][i].SetWindowText(inSertName);
			}
			else
			{
				inSertName.Format("RT%2d已存在，不能再次添加",i);
				MessageBox(inSertName,"提示", MB_OK);
			}
		}
	}
	CDialog::OnOK();
}
/*
void CRTSelectDlg::OnClickCwboolean33() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<32;i++)
	{
		((CCWButton*)GetDlgItem(IDC_CWBOOLEAN0+i))->SetValue(false);
	}
}*/



void CRTSelectDlg::OnButton12() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<32;i++)
		((CButton*)GetDlgItem(IDC_CHECK1+i))->SetCheck(true);
}

void CRTSelectDlg::OnButton13() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<32;i++)
		((CButton*)GetDlgItem(IDC_CHECK1+i))->SetCheck(false);
}

BOOL CRTSelectDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	int i;
	for(i=0;i<32;i++)
	{
		if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data_Exsit[i] == true)
		((CButton*)GetDlgItem(IDC_CHECK1+i))->SetCheck(true);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRTSelectDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
