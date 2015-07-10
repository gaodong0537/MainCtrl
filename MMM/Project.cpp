// Project.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "Project.h"
#include "MainFrm.h"
#include "RTDataSet.h"
#include "Glbs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProject dialog


CProject::CProject(CWnd* pParent /*=NULL*/)
	: CDialog(CProject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProject)

	//}}AFX_DATA_INIT
}


void CProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProject)
	DDX_Control(pDX, IDC_STATIC01, m_static01);
	DDX_Control(pDX, IDC_STATICRTST, m_RTstutas);
	DDX_Control(pDX, IDC_STATICBCST, m_BCstutas);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	DDX_Control(pDX, IDC_STATIC02, m_static02);
	DDX_Control(pDX, IDC_STATIC03, m_static03);
	DDX_Control(pDX, IDC_STATIC04, m_static04);
	DDX_Control(pDX, IDC_STATIC05, m_static05);
	DDX_Control(pDX, IDC_STATIC06, m_static06);
	DDX_Control(pDX, IDC_STATIC07, m_static07);
	DDX_Control(pDX, IDC_STATIC08, m_static08);
	DDX_Control(pDX, IDC_STATIC09, m_static09);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON1, m_RunBC);
	DDX_Control(pDX, IDC_BUTTON2, m_StopBC);
	DDX_Control(pDX, IDC_BUTTON3, m_StepBC);
	DDX_Control(pDX, IDC_BUTTON22, m_EditBC);

	DDX_Control(pDX, IDC_BUTTON4, m_RunRT);
	DDX_Control(pDX, IDC_BUTTON5, m_StopRT);
	DDX_Control(pDX, IDC_BUTTON23, m_EditRT);
}


BEGIN_MESSAGE_MAP(CProject, CDialog)
	//{{AFX_MSG_MAP(CProject)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, OnRclickTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, OnClickTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_BN_CLICKED(IDC_BUTTON1, OnRunBC)
	ON_BN_CLICKED(IDC_BUTTON2, OnStopBC)
	ON_BN_CLICKED(IDC_BUTTON3, OnStepBC)
	ON_BN_CLICKED(IDC_BUTTON4, OnRunRT)
	ON_BN_CLICKED(IDC_BUTTON5, OnStopRT)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON22, OnButtoneEditBc)
	ON_BN_CLICKED(IDC_BUTTON23, OnButtonEditRT)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProject message handlers

BOOL CProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ImageList.Create(16,16,ILC_COLOR32|ILC_MASK,0,0);
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE4)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE1)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE3)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE2)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE5)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE6)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE7)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE8)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE9)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE10)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE11)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_TREEIMAGE12)));
	
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_SAVE)));
	m_ImageList.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_BCDIS)));
	
	
/*	m_ImageList32.Create(32,32,ILC_COLOR32|ILC_MASK,0,0);
	m_ImageList32.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON1)));
	m_ImageList32.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON2)));
	m_ImageList32.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON3)));
	m_ImageList32.Add(::LoadIcon(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON4)));

*/

	//this->m_static01.SetBkColor(RGB(237,246,255));
	this->m_static01.SetFont("黑体");    //字体
	this->m_static01.SetFontSize(13);     //字体大小
	this->m_static01.SetFontStyle(true,true,false);    //字体风格
	this->m_static01.SetTextColor(RGB(100,108,255));    //字体颜色
	this->m_static01.SetShadow(true,RGB(32,32,32),2,45);  //设置阴影


	//this->m_static09.SetBkColor(RGB(237,246,255));
	this->m_static09.SetFont("黑体");    //字体
	this->m_static09.SetFontSize(13);     //字体大小
	this->m_static09.SetFontStyle(true,true,false);    //字体风格
	this->m_static09.SetTextColor(RGB(100,108,255));    //字体颜色
	this->m_static09.SetShadow(true,RGB(32,32,32),2,45);  //设置阴影

	this->m_Tree.SetImageList(&m_ImageList,TVSIL_NORMAL);

	
	RootItem=m_Tree.InsertItem("1553B配置工程",2,2,TVI_ROOT);
	m_Tree.SetItemImage(RootItem,7, 7 );
	NextItem=m_Tree.GetChildItem(TVI_ROOT);
	
	

	
	InsertItemBC = m_Tree.InsertItem("总线控制器-BC",1,1,NextItem);

	InsertItemBC_time = m_Tree.InsertItem("BC周期消息",1,1,InsertItemBC);
	m_Tree.SetItemImage(InsertItemBC_time,9, 9 );
	InsertItemBC_NOtime = m_Tree.InsertItem("BC非周期消息",1,1,InsertItemBC);
	m_Tree.SetItemImage(InsertItemBC_NOtime,10, 10 );
	m_Tree.Expand(InsertItemBC,TVE_EXPAND);

	m_Tree.SetItemImage(InsertItemBC,1, 1 );
	InsertItemRT = m_Tree.InsertItem("远程终端-RTs",1,1,NextItem);
	m_Tree.SetItemImage(InsertItemRT,2, 2 );
	InsertItemBM = m_Tree.InsertItem("总线监视器-BM",1,1,NextItem);
	m_Tree.SetItemImage(InsertItemBM,5, 5 );

	m_Tree.Expand(RootItem,TVE_EXPAND);
//	InsertItemIO = m_Tree.InsertItem("数字量I/O",1,1,NextItem);
//	m_Tree.SetItemImage(InsertItemIO,8, 8);

	m_RunBC.SetIcon(IDI_RUN1,IDI_RUN2);
	m_RunBC.DrawBorder(FALSE);
	m_RunBC.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_RunBC.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_RunBC.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_RunBC.SetTooltipText("运行BC",true);

	
	m_StopBC.SetIcon(IDI_STOP1,IDI_STOP2);
	m_StopBC.DrawBorder(FALSE);
	m_StopBC.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_StopBC.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_StopBC.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_StopBC.SetTooltipText("停止BC",true);
	
	m_EditBC.SetIcon(IDI_EXIT1,IDI_EXIT2);
	m_EditBC.DrawBorder(FALSE);
	m_EditBC.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_EditBC.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_EditBC.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_EditBC.SetTooltipText("编辑BC",true);

	m_StepBC.SetIcon(IDI_RUN1,IDI_RUN2);
	m_StepBC.DrawBorder(FALSE);
	m_StepBC.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_StepBC.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_StepBC.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_StepBC.SetTooltipText("单次运行BC",true);

	m_RunRT.SetIcon(IDI_RUN1,IDI_RUN2);
	m_RunRT.DrawBorder(FALSE);
	m_RunRT.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_RunRT.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_RunRT.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_RunRT.SetTooltipText("运行RT",true);

	
	m_StopRT.SetIcon(IDI_STOP1,IDI_STOP2);
	m_StopRT.DrawBorder(FALSE);
	m_StopRT.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_StopRT.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_StopRT.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_StopRT.SetTooltipText("停止RT",true);

	m_EditRT.SetIcon(IDI_EXIT1,IDI_EXIT2);
	m_EditRT.DrawBorder(FALSE);
	m_EditRT.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_EditRT.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_EditRT.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_EditRT.SetTooltipText("编辑RT",true);


	SetTimer(0,400,NULL);

	ReadFlag = true;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CProject::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

void CProject::OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
void CProject::EnableMessage(int tyep,int ID)
{
	if(tyep==1)
		m_Tree.SetItemImage(BCItem[ID],11, 11 );
	else
		m_Tree.SetItemImage(BCItemNo[ID],11, 11 );
}
void CProject::DisableMessage(int tyep,int ID)
{
	if(tyep==1)
		m_Tree.SetItemImage(BCItem[ID],13, 13 );
	else
		m_Tree.SetItemImage(BCItemNo[ID],13, 13 );
}
void CProject::InsertTreeData(int type, CString Name,int messageid)
{
	if (type==10)//插入BC周期节点
	{
		 BCItem[messageid] = m_Tree.InsertItem(Name,1,1,InsertItemBC_time);
		 m_Tree.SetItemImage(BCItem[messageid],11, 11 );
		 m_Tree.Expand(InsertItemBC_time,TVE_EXPAND);
	}
	if (type==11)//插入BC非周期节点
	{
		 BCItemNo[messageid] = m_Tree.InsertItem(Name,1,1,InsertItemBC_NOtime);
		 m_Tree.SetItemImage(BCItemNo[messageid],11, 11 );
		 m_Tree.Expand(InsertItemBC_NOtime,TVE_EXPAND);
	}
	else if(type==1)//插入RT节点
	{
		RTItem[messageid]=m_Tree.InsertItem(Name,1,1,InsertItemRT);
		m_Tree.SetItemImage(RTItem[messageid],6, 6 );
		m_Tree.Expand(InsertItemRT,TVE_EXPAND);
	}
}
void CProject::ChangeTreeData(int type, CString Name,int messageid)
{
	if (type==10)//更改节点名称
	{
		 m_Tree.SetItemText(BCItem[messageid],Name);

	}
	else if (type==11)//更改节点名称
	{
		 m_Tree.SetItemText(BCItemNo[messageid],Name);

	}
	else if(type==1)//更改节点RT名称
	{
		m_Tree.SetItemText(RTItem[messageid],Name);
		m_Tree.Expand(InsertItemRT,TVE_EXPAND);
	}
}
void CProject::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString str_cmp;
	int i;
	HTREEITEM SeleItem = m_Tree.GetNextItem(TVI_ROOT,TVGN_CARET);
	CString Data_file = m_Tree.GetItemText(SeleItem);
	CString Parent_Name = m_Tree.GetItemText(m_Tree.GetParentItem(SeleItem));
	if((Data_file=="BC周期消息")||(Data_file=="BC非周期消息"))
	{
		CMainFrame *m_pMainWnd;
		m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].ShowWindow(SW_SHOW);
	}
	else if(Data_file=="远程终端-RTs")
	{

		CRTDataSet RTSetDlg;
		RTSetDlg.IniType = 1;//
		RTSetDlg.RTAdress = 1;//
		RTSetDlg.SubAdress = 1;//
		if(RTSetDlg.DoModal()==IDOK)
		{
		}
	}
	else if(Parent_Name=="远程终端-RTs")
	{
		for(i=0;i<32;i++)
		{
			str_cmp.Format("RT%2d",i);
			if(str_cmp==Data_file)
			{
				
				break;
			}
		}
	//	CRTDataSet RTSetDlg;
	//	RTSetDlg.IniType = 0;//
	//	RTSetDlg.RTAdress = i;//
	//	if(RTSetDlg.DoModal()==IDOK)
		{

		}

	}
	else if(Data_file=="总线监视器-BM")
	{
		CMainFrame *m_pMainWnd;
		m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
		m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].ShowWindow(SW_SHOWNA);
		

	}
	*pResult = 0;
}
bool CProject::InitTimeSet()
{
	HTREEITEM hItem ;

	hItem = m_Tree.GetChildItem(InsertItemBC_time);
	while (hItem!=NULL)
	{
		m_Tree.DeleteItem(hItem);
		hItem = m_Tree.GetChildItem(InsertItemBC_time);
	}
	return true;

}
bool CProject::InitNoTimeSet()
{
	HTREEITEM hItem ;

	hItem = m_Tree.GetChildItem(InsertItemBC_NOtime);
	while (hItem!=NULL)
	{
		m_Tree.DeleteItem(hItem);
		hItem = m_Tree.GetChildItem(InsertItemBC_NOtime);
	}
	return true;
}
bool CProject::InitAllSet()
{
	HTREEITEM hItem ;

	hItem = m_Tree.GetChildItem(InsertItemBC_time);
	while (hItem!=NULL)
	{
		m_Tree.DeleteItem(hItem);
		hItem = m_Tree.GetChildItem(InsertItemBC_time);
	}
	hItem = m_Tree.GetChildItem(InsertItemBC_NOtime);
	while (hItem!=NULL)
	{
		m_Tree.DeleteItem(hItem);
		hItem = m_Tree.GetChildItem(InsertItemBC_NOtime);
	}

	hItem = m_Tree.GetChildItem(InsertItemRT);
	while (hItem!=NULL)
	{
		m_Tree.DeleteItem(hItem);
		hItem = m_Tree.GetChildItem(InsertItemRT);
	}
	return true;
}
void CProject::MoveUpBCMessage(int type,int ID)
{
	HTREEITEM tempItem1,tempItem2;
	CString Str1,Str2;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	if(type==1)
	{
		//if(ID>0)
		{
			

			tempItem1 = BCItem[ID-1];
			tempItem2 = BCItem[ID];
			
			Str1 = m_Tree.GetItemText(BCItem[ID-1]);
			Str2 = m_Tree.GetItemText(BCItem[ID]);

			BCItem[ID-1] = tempItem2;
			BCItem[ID] = tempItem1;

			m_Tree.DeleteItem(tempItem1);

			BCItem[ID] = m_Tree.InsertItem(Str1, InsertItemBC_time, tempItem2);
			m_Tree.SetItemImage(BCItem[ID],11, 11 );
			

			//m_Tree.SetItemText(BCItem[ID-1],Str1);
			//m_Tree.SetItemText(BCItem[ID],Str2);

			
		}
	}
	else if(type==2)
	{
		//if(ID>0)
		{


			tempItem1 = BCItemNo[ID-1];
			tempItem2 = BCItemNo[ID];
			
			Str1 = m_Tree.GetItemText(BCItemNo[ID-1]);
			Str2 = m_Tree.GetItemText(BCItemNo[ID]);

			BCItemNo[ID-1] = tempItem2;
			BCItemNo[ID] = tempItem1;

			m_Tree.DeleteItem(tempItem1);

			BCItemNo[ID] = m_Tree.InsertItem(Str1, InsertItemBC_NOtime, tempItem2);
			m_Tree.SetItemImage(BCItemNo[ID],11, 11 );

		}

	}
}

void CProject::MoveDownBCMessage(int type,int ID)
{
	HTREEITEM tempItem1,tempItem2;
	CString Str1,Str2;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	if(type==1)
	{
		//if((ID>=0)&&(ID<m_pMainWnd->MessageData1553.BC_MessageMaxCount))
		{
			tempItem1 = BCItem[ID];
			tempItem2 = BCItem[ID+1];
			
			Str1 = m_Tree.GetItemText(BCItem[ID]);
			Str2 = m_Tree.GetItemText(BCItem[ID+1]);

			BCItem[ID] = tempItem2;
			BCItem[ID+1] = tempItem1;

			m_Tree.DeleteItem(tempItem1);

			BCItem[ID+1] = m_Tree.InsertItem(Str1, InsertItemBC_time, tempItem2);
			m_Tree.SetItemImage(BCItem[ID+1],11, 11 );

			
		}
	}
	else if(type==2)
	{
		//if((ID>=0)&&(ID<m_pMainWnd->MessageData1553.BC_MessageMaxCount_2))
		{
			tempItem1 = BCItemNo[ID];
			tempItem2 = BCItemNo[ID+1];
			
			Str1 = m_Tree.GetItemText(BCItemNo[ID]);
			Str2 = m_Tree.GetItemText(BCItemNo[ID+1]);

			BCItemNo[ID] = tempItem2;
			BCItemNo[ID+1] = tempItem1;

			m_Tree.DeleteItem(tempItem1);

			BCItemNo[ID+1] = m_Tree.InsertItem(Str1, InsertItemBC_NOtime, tempItem2);
			m_Tree.SetItemImage(BCItemNo[ID+1],11, 11 );
		}

	}
}

void CProject::OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CProject::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

BOOL CProject::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F1)
	{
		m_pMainWnd->RunBC();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F2)
	{
		m_pMainWnd->StopBC();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F3)
	{
		m_pMainWnd->StepRun();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F4)
	{
		m_pMainWnd->RunRT();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F5)
	{
		m_pMainWnd->StopRT();
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CProject::OnRunBC() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_stutas == 0)
	{
		m_pMainWnd->RunBC();
	}
}

void CProject::OnStopBC() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	//if(m_pMainWnd->MessageData1553.BC_stutas == 1)
	{
		m_pMainWnd->StopBC();
	}
}

void CProject::OnStepBC() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	m_pMainWnd->StepRun();
}

void CProject::OnRunRT() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	m_pMainWnd->RunRT();
}

void CProject::OnStopRT() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	m_pMainWnd->StopRT();
}

void CProject::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_stutas == 1) 
		m_BCstutas.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON4));
	else m_BCstutas.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON5));

	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_stutas == 1) 
		m_RTstutas.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON4));
	else m_RTstutas.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON5));

	CDialog::OnTimer(nIDEvent);
}

void CProject::SetRTIcon(int RT_ID, bool flag_val)
{
	if(flag_val)
		m_Tree.SetItemImage(RTItem[RT_ID],4, 4 );
	else m_Tree.SetItemImage(RTItem[RT_ID],6, 6 );
}

void CProject::DeleteRT(int RT_ID)
{
	m_Tree.DeleteItem(RTItem[RT_ID]);
}
/*
void CProject::OnItemexpandingTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if (pNMTreeView->action == TVE_COLLAPSE) 
	{ 
		*pResult = TRUE; 
	} 
	else { 
		*pResult = 0; 
	} 
}
*/

void CProject::OnButtoneEditBc() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	
	m_pMainWnd->InsertBCMessage();
}

void CProject::OnButtonEditRT() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	m_pMainWnd->InsertRTData();
}

void CProject::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rcWnd;
	this->GetClientRect(&rcWnd);
	CBrush brush;
	brush.CreateSolidBrush(RGB(237,246,255));
	dc.FillRect(&rcWnd,&brush);
	brush.DeleteObject();
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CProject::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect,rect2,rect3,rect4;

	int ButonLeng,ButonHight;
	int StaticLeng,StaticHight;
	int Static2Leng,Static2Hight;
	// TODO: Add your message handler code here
	this->GetClientRect(rect2);
	rect = rect2;
	if(ReadFlag==true)
	{

		rect.bottom = rect.top + (rect.bottom -rect.top)*2/3;
		//this->m_Tree.MoveWindow(rect,true);
		GetDlgItem(IDC_TREE1)->MoveWindow(rect,true);
	
		GetDlgItem(IDC_BUTTON2)->GetWindowRect(rect2);
		ButonLeng = rect2.right - rect2.left;  
		ButonHight = rect2.bottom - rect2.top;

		GetDlgItem(IDC_STATIC02)->GetWindowRect(rect2);
		StaticLeng = rect2.right - rect2.left;  
		StaticHight = rect2.bottom - rect2.top;


		GetDlgItem(IDC_STATIC01)->GetWindowRect(rect2);
		Static2Leng = rect2.right - rect2.left;  
		Static2Hight = rect2.bottom - rect2.top;
			 
		rect2.top = rect.bottom+50-Static2Hight-10;
		rect2.bottom = rect2.top + ButonHight+StaticHight+Static2Hight+15;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*2.7-5;
		rect2.right = (rect.right-rect.left)/2+rect.left+ButonLeng*3+5;
		GetDlgItem(IDC_STATICFRMAE3)->MoveWindow(rect2);


		rect2.top = rect.bottom+50-Static2Hight;
		rect2.bottom = rect.bottom+50;
		rect2.left = (rect.right-rect.left)/2+rect.left-Static2Leng*0.5;
		rect2.right = rect2.left+Static2Leng;
		GetDlgItem(IDC_STATIC01)->MoveWindow(rect2);


		rect2.top = rect.bottom+50;
		rect2.bottom = rect.bottom+50+ButonHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*2.7;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_BUTTON1)->MoveWindow(rect2);

		rect2.top = rect.bottom+50+ButonHight+2;
		rect2.bottom = rect2.top+StaticHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*2.7;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_STATIC02)->MoveWindow(rect2);


		rect2.top = rect.bottom+50;
		rect2.bottom = rect.bottom+50+ButonHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*1.7;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_BUTTON2)->MoveWindow(rect2);

		rect2.top = rect.bottom+50+ButonHight+2;
		rect2.bottom = rect2.top+StaticHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*1.7;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_STATIC03)->MoveWindow(rect2);

		
		rect2.top = rect.bottom+50;
		rect2.bottom = rect.bottom+50+ButonHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*0.7;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_BUTTON22)->MoveWindow(rect2);

		rect2.top = rect.bottom+50+ButonHight+2;
		rect2.bottom = rect2.top+StaticHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*0.7;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_STATIC04)->MoveWindow(rect2);

		rect2.top = rect.bottom+50;
		rect2.bottom = rect.bottom+50+ButonHight;
		rect2.left = (rect.right-rect.left)/2+rect.left+ButonLeng*0.3;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_BUTTON3)->MoveWindow(rect2);

		rect2.top = rect.bottom+50+ButonHight+2;
		rect2.bottom = rect2.top+StaticHight;
		rect2.left = (rect.right-rect.left)/2+rect.left+ButonLeng*0.3;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_STATIC05)->MoveWindow(rect2);

		rect2.top = rect.bottom+50;
		rect2.bottom = rect.bottom+50+ButonHight;
		rect2.left = (rect.right-rect.left)/2+rect.left+ButonLeng*2;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_STATICBCST)->MoveWindow(rect2);

		



		rect2.top = rect.bottom+50-8;
		rect2.bottom = rect.bottom+50+ButonHight+2;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*2.7-1;
		rect2.right = (rect.right-rect.left)/2+rect.left+ButonLeng*1.3+2;
		GetDlgItem(IDC_STATIC1FRAME)->MoveWindow(rect2);

		
////////////////////////////////////////////////////////////////

		rect2.top = rect.bottom+150-Static2Hight-10;
		rect2.bottom = rect2.top + ButonHight+StaticHight+Static2Hight+15;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*2-5;
		rect2.right = (rect.right-rect.left)/2+rect.left+ButonLeng*2.5+5;
		GetDlgItem(IDC_STATICFRMAE4)->MoveWindow(rect2);


		rect2.top = rect.bottom+150-Static2Hight;
		rect2.bottom = rect.bottom+150;
		rect2.left = (rect.right-rect.left)/2+rect.left-Static2Leng*0.5;
		rect2.right = rect2.left+Static2Leng;
		GetDlgItem(IDC_STATIC09)->MoveWindow(rect2);

		rect2.top = rect.bottom+150;
		rect2.bottom = rect.bottom+150+ButonHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*2;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_BUTTON4)->MoveWindow(rect2);


		rect2.top = rect.bottom+150+ButonHight+2;
		rect2.bottom = rect2.top+StaticHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*2;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_STATIC06)->MoveWindow(rect2);

		rect2.top = rect.bottom+150;
		rect2.bottom = rect.bottom+150+ButonHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*1;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_BUTTON5)->MoveWindow(rect2);

		rect2.top = rect.bottom+150+ButonHight+2;
		rect2.bottom = rect2.top+StaticHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*1;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_STATIC07)->MoveWindow(rect2);

		rect2.top = rect.bottom+150;
		rect2.bottom = rect.bottom+150+ButonHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*0;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_BUTTON23)->MoveWindow(rect2);

		rect2.top = rect.bottom+150+ButonHight+2;
		rect2.bottom = rect2.top+StaticHight;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*0;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_STATIC08)->MoveWindow(rect2);

		rect2.top = rect.bottom+150;
		rect2.bottom = rect.bottom+150+ButonHight;
		rect2.left = (rect.right-rect.left)/2+rect.left+ButonLeng*1.5;
		rect2.right = rect2.left+ButonLeng;
		GetDlgItem(IDC_STATICRTST)->MoveWindow(rect2);

		rect2.top = rect.bottom+150-8;
		rect2.bottom = rect.bottom+150+ButonHight+2;
		rect2.left = (rect.right-rect.left)/2+rect.left-ButonLeng*2-1;
		rect2.right = (rect.right-rect.left)/2+rect.left+ButonLeng*1+2;
		GetDlgItem(IDC_STATIC2FRAME)->MoveWindow(rect2);

//////////////////////////////////////////////////////
		CMainFrame *m_pMainWnd;
		m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

		m_pMainWnd->m_wndMyBar1.GetWindowRect(rect2);
		m_pMainWnd->GetClientRect(rect3);
		m_pMainWnd->m_wndStatusBar.GetWindowRect(rect4);

		m_pMainWnd->BCView[0].GetWindowRect(rect);
		rect.left= rect2.right;
		rect.top = rect2.top;
		rect.right= rect3.right-2;

		int i;
		for(i=0;i<MAX_1553BChanel;i++)
		{
			m_pMainWnd->BCView[i].MaxRect.left = rect.left;
			m_pMainWnd->BCView[i].MaxRect.right = rect.right-2;
			m_pMainWnd->BCView[i].MaxRect.top = rect2.top;
			m_pMainWnd->BCView[i].MaxRect.bottom = rect2.bottom;

			m_pMainWnd->BCView[i].MoveWindow(rect);
			m_pMainWnd->BCView[i].Invalidate(true);
		}

	


		////////////////


		m_pMainWnd->BMView[0].GetWindowRect(rect);
		rect.left= rect2.right;
		rect.right= rect3.right-2;
		rect.bottom= rect2.bottom-1;

		for(i=0;i<MAX_1553BChanel;i++)
		{
			m_pMainWnd->BMView[i].MaxRect.left = rect.left;
			m_pMainWnd->BMView[i].MaxRect.right = rect.right-2;
			m_pMainWnd->BMView[i].MaxRect.top = rect2.top;
			m_pMainWnd->BMView[i].MaxRect.bottom = rect2.bottom-1;

			m_pMainWnd->BMView[i].MoveWindow(rect);
			m_pMainWnd->BMView[i].Invalidate(true);
		}





		Invalidate(true);

	}
}
