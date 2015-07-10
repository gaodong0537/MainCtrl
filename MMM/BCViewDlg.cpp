// BCViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "BCViewDlg.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCViewDlg dialog


CBCViewDlg::CBCViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBCViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBCViewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBCViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBCViewDlg)
	DDX_Control(pDX, IDC_LIST3, m_BC_MesList2);
	DDX_Control(pDX, IDC_LIST1, m_BC_MesList);
	//}}AFX_DATA_MAP
	
}


BEGIN_MESSAGE_MAP(CBCViewDlg, CDialog)
	//{{AFX_MSG_MAP(CBCViewDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkBCViewList)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST3, OnDblclkList3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCViewDlg message handlers

BOOL CBCViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	LV_COLUMN lvcolumn;

	// TODO: Add extra initialization here
	m_BC_MesList.ModifyStyle(LVS_EDITLABELS,0L);
	m_BC_MesList.ModifyStyle(0L,LVS_REPORT);
	m_BC_MesList.ModifyStyle(0L,LVS_SHOWSELALWAYS);
	m_BC_MesList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.cx = 60;
	lvcolumn.pszText = "ID号";
	m_BC_MesList.InsertColumn(0,&lvcolumn);
	lvcolumn.cx = 100;
	lvcolumn.pszText = "名称";
	m_BC_MesList.InsertColumn(1,&lvcolumn);
	lvcolumn.cx = 90;
	lvcolumn.pszText = "类型";
	m_BC_MesList.InsertColumn(2,&lvcolumn);
	lvcolumn.cx = 80;
	lvcolumn.pszText = "地址";
	m_BC_MesList.InsertColumn(3,&lvcolumn);
	lvcolumn.cx = 60;
	lvcolumn.pszText = "子地址";
	m_BC_MesList.InsertColumn(4,&lvcolumn);	
	
	lvcolumn.cx = 90;
	lvcolumn.pszText = "通道A/B";
	m_BC_MesList.InsertColumn(5,&lvcolumn);

	lvcolumn.cx = 90;
	lvcolumn.pszText = "数据字计数";
	m_BC_MesList.InsertColumn(6,&lvcolumn);
	m_BC_MesList.ListType = 1;

	lvcolumn.cx = 70;
	lvcolumn.pszText = "状态";
	m_BC_MesList.InsertColumn(7,&lvcolumn);

	m_BC_MesList2.ModifyStyle(LVS_EDITLABELS,0L);
	m_BC_MesList2.ModifyStyle(0L,LVS_REPORT);
	m_BC_MesList2.ModifyStyle(0L,LVS_SHOWSELALWAYS);
	m_BC_MesList2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.cx = 60;
	lvcolumn.pszText = "ID号";
	m_BC_MesList2.InsertColumn(0,&lvcolumn);
	lvcolumn.cx = 100;
	lvcolumn.pszText = "名称";
	m_BC_MesList2.InsertColumn(1,&lvcolumn);
	lvcolumn.cx = 90;
	lvcolumn.pszText = "类型";
	m_BC_MesList2.InsertColumn(2,&lvcolumn);
	lvcolumn.cx = 80;
	lvcolumn.pszText = "地址";
	m_BC_MesList2.InsertColumn(3,&lvcolumn);
	lvcolumn.cx = 60;
	lvcolumn.pszText = "子地址";
	m_BC_MesList2.InsertColumn(4,&lvcolumn);	
	
	lvcolumn.cx = 90;
	lvcolumn.pszText = "通道A/B";
	m_BC_MesList2.InsertColumn(5,&lvcolumn);

	lvcolumn.cx = 90;
	lvcolumn.pszText = "数据字计数";
	m_BC_MesList2.InsertColumn(6,&lvcolumn);
	m_BC_MesList2.ListType = 2;

	lvcolumn.cx = 70;
	lvcolumn.pszText = "状态";
	m_BC_MesList2.InsertColumn(7,&lvcolumn);

	int i;

	m_BC_MesList2.OnInit();
	m_BC_MesList2.type = 2;
	m_BC_MesList.OnInit();
	m_BC_MesList.type = 1;
	char str[20];
	for(i=0;i<32;i++)
	{
		sprintf(str,"数据%d",i);
		lvcolumn.pszText = str; 
		lvcolumn.cx = 70;
		m_BC_MesList.InsertColumn(8+i,&lvcolumn);
		m_BC_MesList2.InsertColumn(8+i,&lvcolumn);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CBCViewDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

void CBCViewDlg::OnDblclkBCViewList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	int select_item;
	select_item = m_BC_MesList.GetNextItem(-1,LVNI_SELECTED );
	if((select_item>=0)&&(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_stutas==0))
	{
		CMessageSet MeSetDlg;
		MeSetDlg.IniType = 1;//Edit mode
		MeSetDlg.NowAddMessageTyep = 1;
		MeSetDlg.MessageTyep = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageTyep[select_item];
		MeSetDlg.nowMessageNo = select_item;

		MeSetDlg.address = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[select_item].mess_command1.rtaddr;
		MeSetDlg.subaddr = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[select_item].mess_command1.subaddr;
		MeSetDlg.wcount = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[select_item].mess_command1.wcount;

		MeSetDlg.address2 = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[select_item].mess_command2.rtaddr;
		MeSetDlg.subaddr2 = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[select_item].mess_command2.subaddr;
		MeSetDlg.wcount2 = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[select_item].mess_command2.wcount;

		MeSetDlg.chanA_B = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].chanA_B[select_item];
		MeSetDlg.MessageName = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName[select_item];
		MeSetDlg.GapTime = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[select_item].gap_time;
		for(i=0;i<32;i++)
			MeSetDlg.InitData[i] = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[select_item].data[0][i];
		if(MeSetDlg.DoModal()==IDOK)
		{
			
		}
	}
	else
	{
		if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_stutas==1)
			MessageBox("BC运行中不能编辑消息","提示",MB_OK);
	}
	*pResult = 0;
}
void CBCViewDlg::OnDblclkList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	int select_item;
	select_item = m_BC_MesList2.GetNextItem(-1,LVNI_SELECTED );
	if(select_item>=0)
	{
		CMessageSet MeSetDlg;
		MeSetDlg.IniType = 1;//Edit mode
		MeSetDlg.NowAddMessageTyep = 2;
		MeSetDlg.MessageTyep = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageTyep_2[select_item];
		MeSetDlg.nowMessageNo = select_item;

		MeSetDlg.address = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[select_item].mess_command1.rtaddr;
		MeSetDlg.subaddr = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[select_item].mess_command1.subaddr;
		MeSetDlg.wcount = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[select_item].mess_command1.wcount;

		MeSetDlg.address2 = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[select_item].mess_command2.rtaddr;
		MeSetDlg.subaddr2 = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[select_item].mess_command2.subaddr;
		MeSetDlg.wcount2 = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[select_item].mess_command2.wcount;

		MeSetDlg.chanA_B = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].chanA_B_2[select_item];
		MeSetDlg.MessageName = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName_2[select_item];

		MeSetDlg.GapTime = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[select_item].gap_time;

		for(i=0;i<32;i++)
			MeSetDlg.InitData[i] = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[select_item].data[0][i];
		if(MeSetDlg.DoModal()==IDOK)
		{
			
		}
	}
	else
	{
		if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_stutas==1)
			MessageBox("BC运行中不能编辑消息","提示",MB_OK);
	}
	*pResult = 0;
}
void CBCViewDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	this->ShowWindow(SW_HIDE);
	//CDialog::OnCancel();
}

void CBCViewDlg::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDialog::PreSubclassWindow();
}

BOOL CBCViewDlg::PreTranslateMessage(MSG* pMsg) 
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

void CBCViewDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

void CBCViewDlg::OnSize(UINT nType, int cx, int cy) 
{
	CRect rcBounds,list1rect,list2rect;
	CDialog::OnSize(nType, cx, cy);

	if(HaveCreate!=0)
	{
		if(nType == 2) 
		{
			this->MoveWindow(MaxRect,true); ;
		}
		this->GetClientRect(rcBounds);
		list1rect = rcBounds;
		list1rect.top = rcBounds.top+5;
		list1rect.bottom = rcBounds.bottom/2;
		((CStatic  *)GetDlgItem(IDC_STATIC1))->MoveWindow(list1rect,true);
		list1rect = rcBounds;
		list1rect.top = rcBounds.top+20;
		list1rect.bottom = rcBounds.bottom/2;
		m_BC_MesList.MoveWindow(list1rect,true);


		list2rect = rcBounds;
		list2rect.top = rcBounds.bottom/2+5;
		((CStatic  *)GetDlgItem(IDC_STATIC2))->MoveWindow(list2rect,true);

		list2rect = rcBounds;
		list2rect.top = rcBounds.bottom/2+20;
		m_BC_MesList2.MoveWindow(list2rect,true);
	
		
	}
	HaveCreate = 1;
	// TODO: Add your message handler code here
	
}

void CBCViewDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}



void CBCViewDlg::MoveUpBCMessage(int type, int NowMoveID)
{
	int i;
	CString Temp_Str1,Temp_Str2,Temp_Str3;
	bool CheckBoxD1,CheckBoxD2;

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].MoveUpBCMessage(type,NowMoveID);


	if(type==1)
	{
		CheckBoxD1 = m_BC_MesList.CheckBox[NowMoveID-1].GetCheck();
		CheckBoxD2 = m_BC_MesList.CheckBox[NowMoveID].GetCheck();

		m_BC_MesList.CheckBox[NowMoveID-1].SetCheck(CheckBoxD2);
		m_BC_MesList.CheckBox[NowMoveID].SetCheck(CheckBoxD1);

		m_BC_MesList.CheckBox[NowMoveID-1].GetWindowText(Temp_Str1);
		m_BC_MesList.CheckBox[NowMoveID].GetWindowText(Temp_Str2);

		m_BC_MesList.CheckBox[NowMoveID-1].SetWindowText(Temp_Str2);
		m_BC_MesList.CheckBox[NowMoveID].SetWindowText(Temp_Str1);


		for(i=1;i<40;i++)
		{
			Temp_Str1 = m_BC_MesList.GetItemText(NowMoveID-1,i);
			Temp_Str2 = m_BC_MesList.GetItemText(NowMoveID,i);

			m_BC_MesList.SetItemText(NowMoveID-1,i,Temp_Str2);
			m_BC_MesList.SetItemText(NowMoveID,i,Temp_Str1);
		}
	}
	else
	{
		CheckBoxD1 = m_BC_MesList2.CheckBox[NowMoveID-1].GetCheck();
		CheckBoxD2 = m_BC_MesList2.CheckBox[NowMoveID].GetCheck();

		m_BC_MesList2.CheckBox[NowMoveID-1].SetCheck(CheckBoxD2);
		m_BC_MesList2.CheckBox[NowMoveID].SetCheck(CheckBoxD1);

		m_BC_MesList2.CheckBox[NowMoveID-1].GetWindowText(Temp_Str1);
		m_BC_MesList2.CheckBox[NowMoveID].GetWindowText(Temp_Str2);

		m_BC_MesList2.CheckBox[NowMoveID-1].SetWindowText(Temp_Str2);
		m_BC_MesList2.CheckBox[NowMoveID].SetWindowText(Temp_Str1);

		for(i=1;i<40;i++)
		{
			Temp_Str1 = m_BC_MesList2.GetItemText(NowMoveID-1,i);
			Temp_Str2 = m_BC_MesList2.GetItemText(NowMoveID,i);

			m_BC_MesList2.SetItemText(NowMoveID-1,i,Temp_Str2);
			m_BC_MesList2.SetItemText(NowMoveID,i,Temp_Str1);
		}

	}
	
}

void CBCViewDlg::MoveDownBCMessage(int type, int NowMoveID)
{
	int i;
	CString Temp_Str1,Temp_Str2,Temp_Str3;
	bool CheckBoxD1,CheckBoxD2;

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].MoveDownBCMessage(type,NowMoveID);

	if(type==1)
	{
		CheckBoxD1 = m_BC_MesList.CheckBox[NowMoveID+1].GetCheck();
		CheckBoxD2 = m_BC_MesList.CheckBox[NowMoveID].GetCheck();

		m_BC_MesList.CheckBox[NowMoveID+1].SetCheck(CheckBoxD2);
		m_BC_MesList.CheckBox[NowMoveID].SetCheck(CheckBoxD1);

		m_BC_MesList.CheckBox[NowMoveID+1].GetWindowText(Temp_Str1);
		m_BC_MesList.CheckBox[NowMoveID].GetWindowText(Temp_Str2);

		m_BC_MesList.CheckBox[NowMoveID+1].SetWindowText(Temp_Str2);
		m_BC_MesList.CheckBox[NowMoveID].SetWindowText(Temp_Str1);

		for(i=1;i<40;i++)
		{
			Temp_Str1 = m_BC_MesList.GetItemText(NowMoveID+1,i);
			Temp_Str2 = m_BC_MesList.GetItemText(NowMoveID,i);

			m_BC_MesList.SetItemText(NowMoveID+1,i,Temp_Str2);
			m_BC_MesList.SetItemText(NowMoveID,i,Temp_Str1);
		}
	}
	else
	{
		CheckBoxD1 = m_BC_MesList2.CheckBox[NowMoveID+1].GetCheck();
		CheckBoxD2 = m_BC_MesList2.CheckBox[NowMoveID].GetCheck();

		m_BC_MesList2.CheckBox[NowMoveID+1].SetCheck(CheckBoxD2);
		m_BC_MesList2.CheckBox[NowMoveID].SetCheck(CheckBoxD1);

		m_BC_MesList2.CheckBox[NowMoveID+1].GetWindowText(Temp_Str1);
		m_BC_MesList2.CheckBox[NowMoveID].GetWindowText(Temp_Str2);

		m_BC_MesList2.CheckBox[NowMoveID+1].SetWindowText(Temp_Str2);
		m_BC_MesList2.CheckBox[NowMoveID].SetWindowText(Temp_Str1);

		for(i=1;i<40;i++)
		{
			Temp_Str1 = m_BC_MesList2.GetItemText(NowMoveID+1,i);
			Temp_Str2 = m_BC_MesList2.GetItemText(NowMoveID,i);

			m_BC_MesList2.SetItemText(NowMoveID+1,i,Temp_Str2);
			m_BC_MesList2.SetItemText(NowMoveID,i,Temp_Str1);
		}

	}
		
}
