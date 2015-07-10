// 1553select.cpp : implementation file
//

#include "stdafx.h"
#include "manctrl.h"
#include "1553select.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C1553select dialog


C1553select::C1553select(CWnd* pParent /*=NULL*/)
	: CDialog(C1553select::IDD, pParent)
{
	//{{AFX_DATA_INIT(C1553select)
	//}}AFX_DATA_INIT
}


void C1553select::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C1553select)
	DDX_Control(pDX, IDC_TAB_1553B, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C1553select, CDialog)
	//{{AFX_MSG_MAP(C1553select)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_1553B, OnSelchangeTab1553b)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C1553select message handlers



BOOL C1553select::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

		m_Tab.InsertItem(0,_T("外部1553B")); 
		m_Tab.InsertItem(1,_T("内部1553B")); 
		int i;
		for(i=0; i < 2; ++i)
		{
			ProjectTabDlg[i].CreatedFlag = false;
			ProjectTabDlg[i].Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,50,50),this,IDD_CONTROLDIALOG,NULL);
			ProjectTabDlg[i].ModifyStyleEx(0, WS_EX_CLIENTEDGE);
			ProjectTabDlg[i].CreatedFlag = true;
		}
		

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void C1553select::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect2;
	
	this->GetClientRect(rect2);
	
	if(CreatedFlag==true)
	{

		m_Tab.MoveWindow(rect2,true);
		
		rect2.top +=1;
		rect2.left +=1;
		rect2.right -=1;
		rect2.bottom -= 25;
		
		int i;
		for(i=0;i<2;i++)
		{
			ProjectTabDlg[i].MoveWindow(rect2,true);//( nType, cx, cy) ;
			ProjectTabDlg[i].ShowWindow(SW_SHOW);
		}
		
	}
}
void C1553select::OnSelchangeTab1553b(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	
	int i;
	for(i=0;i<2;i++)
	{
		ProjectTabDlg[i].ShowWindow(SW_HIDE);
	}
	switch(m_Tab.GetCurSel())
	{
	case 0:
		ProjectTabDlg[0].ShowWindow(SW_SHOW);
		ProjectTabDlg[0].SetTabProjDlgNum(1);
	//	m_pMainWnd->ShowProject_Channel(0);
		break;
	case 1:
		ProjectTabDlg[1].ShowWindow(SW_SHOW);
		ProjectTabDlg[1].SetTabProjDlgNum(2);
	//	m_pMainWnd->ShowProject_Channel(1);
		break;

		
	}

	*pResult = 0;
}

BOOL C1553select::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

		// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(IDD, pParentWnd);
}
