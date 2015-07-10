// TabProjDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "TabProjDlg.h"
#include "MainFrm.h"
#include "Glbs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabProjDlg dialog


CTabProjDlg::CTabProjDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabProjDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabProjDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iTabProjDlgNum = 1;
}


void CTabProjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabProjDlg)
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabProjDlg, CDialog)
	//{{AFX_MSG_MAP(CTabProjDlg)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabProjDlg message handlers

BOOL CTabProjDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

BOOL CTabProjDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char m_show_str[10];
	CRect rect2;
	m_Tab.GetClientRect(rect2);


	rect2.top +=1;
	rect2.left +=1;
	rect2.right -=1;
	rect2.bottom -= 20;

	


	int i;
	for(i=0;i<MAX_1553BChanel;i++)
	{
		sprintf(m_show_str,"%dÍ¨µÀ",i);
		m_Tab.InsertItem(i,m_show_str); 

		ProjectDlg[i].ReadFlag = false;
		ProjectDlg[i].Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,50,50),this,IDD_PRODLG,NULL);
// 		ProjectDlg[i].MoveWindow(rect2,false);		
// 		ProjectDlg[i].ShowWindow(SW_SHOW);
		//ProjectDlg.ReadFlag = true;
		ProjectDlg[i].m_Tree.BCRun_flag=false;
	}

		ProjectDlg[0].ReadFlag = true;



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTabProjDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect2;

	this->GetClientRect(rect2);

	if(CreatedFlag==true)
	{
		GetDlgItem(IDC_TAB1)->MoveWindow(rect2,true);

		rect2.top +=1;
		rect2.left +=1;
		rect2.right -=1;
		rect2.bottom -= 25;

		int i;
		for(i=0;i<MAX_1553BChanel;i++)
		{
			ProjectDlg[i].MoveWindow(rect2,true);//( nType, cx, cy) ;
					ProjectDlg[i].ShowWindow(SW_SHOW);
		}

	}
}



void CTabProjDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	int i;
	for(i=0;i<MAX_1553BChanel;i++)
	{
		ProjectDlg[i].ShowWindow(SW_HIDE);
	}
	switch(m_Tab.GetCurSel())
	{
	case 0:
		ProjectDlg[0].ShowWindow(SW_SHOW);
		m_pMainWnd->ShowProject_Channel(0*m_iTabProjDlgNum);
		break;
	case 1:
		ProjectDlg[1].ShowWindow(SW_SHOW);
		m_pMainWnd->ShowProject_Channel(1*m_iTabProjDlgNum);
		break;
	case 2:
		ProjectDlg[2].ShowWindow(SW_SHOW);
		m_pMainWnd->ShowProject_Channel(2*m_iTabProjDlgNum);
		break;
	case 3:
		ProjectDlg[3].ShowWindow(SW_SHOW);
		m_pMainWnd->ShowProject_Channel(3*m_iTabProjDlgNum);
		break;

	}

	*pResult = 0;
}

void CTabProjDlg::SetTabProjDlgNum(int num)
{
	m_iTabProjDlgNum = num;
}