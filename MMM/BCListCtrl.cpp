// BCListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "BCListCtrl.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCListCtrl

CBCListCtrl::CBCListCtrl()
{
}

CBCListCtrl::~CBCListCtrl()
{
}


BEGIN_MESSAGE_MAP(CBCListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CBCListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_NOTIFY_REFLECT(LVN_INSERTITEM, OnInsertitem)
	ON_WM_DELETEITEM()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_COMMAND(ID_CHECKBOX,CheckValChange)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCListCtrl message handlers

void CBCListCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	m_pMainWnd->NowdeletID=this->GetNextItem(-1,LVNI_SELECTED);
	if(m_pMainWnd->NowdeletID>=0) del_flag = 1;
	else del_flag = 0;
		OnContextMenu(this,NowPoint);
	*pResult = 0;
}
void CBCListCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	NowPoint = point;
	CListCtrl::OnRButtonUp(nFlags, point);
}

void CBCListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	NowPoint = point;

	CListCtrl::OnRButtonDown(nFlags, point);
}
void CBCListCtrl::CheckValChange()
{
	int i;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	for(i=0;i<this->GetItemCount();i++)
	{
		if(CheckBoxCreateFlag[i]==true)
		{

			if(type==1)//周期消息
			{
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCMessageEnabel[i] = CheckBox[i].GetCheck();	
			}
			if(type==2)//非周期消息
			{
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCNoTiemMessageEnabel[i] = CheckBox[i].GetCheck();
			}

			if(CheckBox[i].GetCheck())
			{
				CheckBox[i].SetWindowText("激活状态");
				
			}
			else
			{
				CheckBox[i].SetWindowText("无效状态");
			}
		}
	}
}
void CBCListCtrl::AddNewItem(int ID) 
{
	// TODO: Add your message handler code here and/or call default
	int style = WS_CHILD|WS_CLIPSIBLINGS|WS_BORDER|BS_AUTOCHECKBOX;
	CRect rect;
	CFont *Font;
	this->GetSubItemRect(ID,7,LVIR_LABEL,rect);
	if(CheckBoxCreateFlag[ID]==false)
	{
		Font = this->GetFont();
		
		CheckBox[ID].Create("激活状态",style,rect,this,ID_CHECKBOX);
		CheckBox[ID].SetFont(Font,true);
		CheckBoxCreateFlag[ID]=true;

	}	
	CheckBox[ID].SetCheck(true);
	CheckBox[ID].SetWindowText("激活状态");	
	
	CheckBox[ID].MoveWindow(rect);
	CheckBox[ID].ShowWindow(SW_SHOW);

}
void CBCListCtrl::DeletItemCheckBox(int ID)
{
	int i,allCount;
	allCount = this ->GetItemCount();
	for(i=ID;i<allCount;i++)
	{
		CheckBox[i].SetCheck(CheckBox[i+1].GetCheck());
		if(CheckBox[i].GetCheck())
			CheckBox[i].SetWindowText("激活状态");
		else 
			CheckBox[i].SetWindowText("无效状态");
	}
	if(CheckBoxCreateFlag[allCount]==true)
	{
		CheckBox[allCount].ShowWindow(SW_HIDE);
	}
} 
void CBCListCtrl::SetCheckBoxVal(int ID,bool val) 
{
	CheckBox[ID].SetCheck(val);
	if(val)
	{
		CheckBox[ID].SetWindowText("激活状态");
	}
	else 
	{
		CheckBox[ID].SetWindowText("无效状态");
	}
}

void CBCListCtrl::OnContextMenu(CWnd *, CPoint point)
{
	CMenu menu;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

		if (point.x == -1 && point.y == -1){
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5,5);
		}
		else
		{
			ClientToScreen(&point);//.Offset(50, 146);
		}
	
		menu.DestroyMenu();
		m_pMainWnd->NowAddMessageType = ListType;
		if(ListType==1)
		{
			
			VERIFY(menu.LoadMenu(IDR_POPUP_BC));
	//		InitMenu(0 ,type, del_flag);
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			CWnd* pWndPopupOwner = this;

			while (pWndPopupOwner->GetStyle() & WS_CHILD)
				pWndPopupOwner = pWndPopupOwner->GetParent();

			//pPopup->EnableMenuItem(AFX_ID_BLOWUP,MF_GRAYED);
		
			if(m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].m_Tree.BCRun_flag)
			{
				pPopup->EnableMenuItem(ID_INSERTBCMES,MF_GRAYED);
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_GRAYED);

				pPopup->EnableMenuItem(ID_MOVEUPMESSAGE,MF_GRAYED);
				pPopup->EnableMenuItem(ID_MOVEDOWNMESSAGE,MF_GRAYED);

				pPopup->EnableMenuItem(ID_PROPEBC,MF_GRAYED);
				pPopup->EnableMenuItem(AFX_ID_OPENMESSAGE,MF_GRAYED);
				//pPopup->EnableMenuItem(AFX_ID_ENABLEMESSAGE,MF_GRAYED);
				//pPopup->EnableMenuItem(AFX_ID_DISABLEMESSAGE,MF_GRAYED);

				pPopup->ModifyMenu(ID_RUNBC,MF_BYCOMMAND,ID_RUNBC,">运行");
				pPopup->ModifyMenu(ID_STOPBC,MF_BYCOMMAND,ID_STOPBC," 停止");
				del_flag  = 0;
			}
			else
			{
				pPopup->EnableMenuItem(ID_INSERTBCMES,MF_ENABLED);
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_ENABLED);

				pPopup->EnableMenuItem(ID_MOVEUPMESSAGE,MF_ENABLED);
				pPopup->EnableMenuItem(ID_MOVEDOWNMESSAGE,MF_ENABLED);

				pPopup->EnableMenuItem(ID_PROPEBC,MF_ENABLED);
				pPopup->EnableMenuItem(AFX_ID_OPENMESSAGE,MF_ENABLED);

				//pPopup->EnableMenuItem(AFX_ID_ENABLEMESSAGE,MF_ENABLED);
				//pPopup->EnableMenuItem(AFX_ID_DISABLEMESSAGE,MF_ENABLED);

				pPopup->ModifyMenu(ID_RUNBC,MF_BYCOMMAND,ID_RUNBC," 运行");
				pPopup->ModifyMenu(ID_STOPBC,MF_BYCOMMAND,ID_STOPBC,">停止");
			}
			if(del_flag==0)
			{
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_GRAYED);
				pPopup->EnableMenuItem(ID_MESSAGEMOVE1,MF_GRAYED);

				pPopup->EnableMenuItem(ID_MOVEUPMESSAGE,MF_GRAYED);
				pPopup->EnableMenuItem(ID_MOVEDOWNMESSAGE,MF_GRAYED);

				//pPopup->EnableMenuItem(AFX_ID_ENABLEMESSAGE,MF_GRAYED);
				//pPopup->EnableMenuItem(AFX_ID_DISABLEMESSAGE,MF_GRAYED);
			}
			else if(del_flag==1)
			{
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_ENABLED);
				pPopup->EnableMenuItem(ID_MESSAGEMOVE1,MF_ENABLED);

				pPopup->EnableMenuItem(ID_MOVEUPMESSAGE,MF_ENABLED);
				pPopup->EnableMenuItem(ID_MOVEDOWNMESSAGE,MF_ENABLED);

				//pPopup->EnableMenuItem(AFX_ID_ENABLEMESSAGE,MF_ENABLED);
				//pPopup->EnableMenuItem(AFX_ID_DISABLEMESSAGE,MF_ENABLED);
			}

			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,pWndPopupOwner);
		}
		else if(ListType==2)
		{
			VERIFY(menu.LoadMenu(IDR_POPUP_BC2));
	//		InitMenu(0 ,type, del_flag);
			CMenu* pPopup = menu.GetSubMenu(0);
			ASSERT(pPopup != NULL);
			CWnd* pWndPopupOwner = this;

			while (pWndPopupOwner->GetStyle() & WS_CHILD)
				pWndPopupOwner = pWndPopupOwner->GetParent();

			//pPopup->EnableMenuItem(AFX_ID_BLOWUP,MF_GRAYED);
		
			if(m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].m_Tree.BCRun_flag)
			{
				pPopup->EnableMenuItem(ID_INSERTBCMES,MF_GRAYED);
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_GRAYED);
				
				

				pPopup->EnableMenuItem(ID_PROPEBC,MF_GRAYED);
				del_flag  = 0;
			}
			else
			{
				pPopup->EnableMenuItem(ID_INSERTBCMES,MF_ENABLED);
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_ENABLED);
				pPopup->EnableMenuItem(ID_PROPEBC,MF_ENABLED);
			}
			if(del_flag==0)
			{
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_GRAYED);
				pPopup->EnableMenuItem(ID_MESSAGEMOVE1,MF_GRAYED);

				pPopup->EnableMenuItem(ID_MOVEUPMESSAGE,MF_GRAYED);
				pPopup->EnableMenuItem(ID_MOVEDOWNMESSAGE,MF_GRAYED);
			}
			else if(del_flag==1)
			{
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_ENABLED);
				pPopup->EnableMenuItem(ID_MESSAGEMOVE1,MF_ENABLED);

				pPopup->EnableMenuItem(ID_MOVEUPMESSAGE,MF_ENABLED);
				pPopup->EnableMenuItem(ID_MOVEDOWNMESSAGE,MF_ENABLED);
			}

			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,pWndPopupOwner);
		}
}


int CBCListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	int i;
	// TODO: Add your specialized creation code here
	
	return 0;
}
void CBCListCtrl::OnInit()
{
	int i;
	
	for(i=0;i<MAXMESSAGECOUNT;i++)
	{
		CheckBoxCreateFlag[i] = false;
		
	}
	
}
void CBCListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	//SetTimer(22,200,NULL);
	int ID;
	CRect rect;
	for(ID=0;ID<MAXMESSAGECOUNT;ID++)
	{
		this->GetSubItemRect(ID,7,LVIR_LABEL,rect);
		if(CheckBoxCreateFlag[ID]==true)
		{
			

		
			CheckBox[ID].MoveWindow(rect);
			CheckBox[ID].ShowWindow(SW_SHOW);
		}
	}
	Invalidate(false);
	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CBCListCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	/*int ID;
	CRect rect;
	for(ID=0;ID<MAXMESSAGECOUNT;ID++)
	{
		this->GetSubItemRect(ID,7,LVIR_LABEL,rect);
		if(CheckBoxCreateFlag[ID]==true)
		{
			

		
			CheckBox[ID].MoveWindow(rect);
			CheckBox[ID].ShowWindow(SW_SHOW);
		}
	}
	*/
	CListCtrl::OnTimer(nIDEvent);
}

void CBCListCtrl::OnInsertitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CBCListCtrl::OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListCtrl::OnDeleteItem(nIDCtl, lpDeleteItemStruct);
}

void CBCListCtrl::DeleteAllItemCheckBox()
{
	int i;
	for(i=0;i<this->GetItemCount();i++)
	{
		if(CheckBoxCreateFlag[i]==true)
		{
			CheckBox[i].ShowWindow(SW_HIDE);
		}
	}
}

void CBCListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	LVHITTESTINFO testinfo;
	LDonwFlag = true;
	testinfo.pt.x = point.x;
	testinfo.pt.y = point.y;
	testinfo.flags = LVHT_ONITEMLABEL;

	if(this->SubItemHitTest(&testinfo)>=0)
	{
		FirstSelectRow = testinfo.iItem;
	}



	CListCtrl::OnLButtonDown(nFlags, point);
}

void CBCListCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	LVHITTESTINFO testinfo;

	testinfo.pt.x = point.x;
	testinfo.pt.y = point.y;
	testinfo.flags = LVHT_ONITEMLABEL;

	if(this->SubItemHitTest(&testinfo)>=0)
	{
		LastSelectRow = testinfo.iItem;
	

		if((FirstSelectRow>=0)&&(LastSelectRow>=0))
		{
			m_pMainWnd->MoveBCMessageto(type,FirstSelectRow,LastSelectRow);
		}
	}
	CListCtrl::OnLButtonUp(nFlags, point);
}

void CBCListCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CPoint point;
	
	point = LDonwUPpoint;
	
	LDonwFlag = false;
	*pResult = 0;
}

void CBCListCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(LDonwFlag)
	{
		LDonwUPpoint = point;
	}
	CListCtrl::OnMouseMove(nFlags, point);
}
