// NewTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "NewTreeCtrl.h"
#include "RTDataSet.h"
#include "MainFrm.h"
//#include "IODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NewTreeCtrl

NewTreeCtrl::NewTreeCtrl()
{
}

NewTreeCtrl::~NewTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(NewTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(NewTreeCtrl)
	ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_WM_RBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewTreeCtrl message handlers

void NewTreeCtrl::InitMenu(int menuid ,int type,int del_flag)
{
	static char menuText[10][40];
	CString strItem;
	menu.DestroyMenu();
	if(menu.m_hMenu==NULL)	
	{
		HMENU hSubMenu=NULL;
		CMenu tempMenu;
		if(tempMenu.LoadMenu(IDR_POPUP_BC))
		{
		if((hSubMenu=::GetSubMenu(tempMenu.m_hMenu,0))!=NULL)			
			{
				tempMenu.RemoveMenu(0,MF_BYPOSITION);
				menu.Attach(hSubMenu);
		        ASSERT(menu.m_hMenu==hSubMenu);
				if(::IsMenu(menu.m_hMenu))
				{
					int i=menu.GetMenuItemCount();
					memset(menuText,0,10*40);
					 for(i-=1;i>=0;i--)
					 {
						menu.GetMenuString(i,strItem,MF_BYPOSITION);
						menu.ModifyMenu(i,MF_BYPOSITION|MF_OWNERDRAW|menu.GetMenuState(i,MF_BYPOSITION),menu.GetMenuItemID(i),strItem);
					 }
				}
			}
		}
	}

}
void NewTreeCtrl::OnContextMenu(CWnd *, CPoint point, int type,int del_flag)
{
	
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
		if(type==0)
			VERIFY(menu.LoadMenu(IDR_POPUP_BC));
		if(type==1)
			VERIFY(menu.LoadMenu(IDR_POPUP_BC2));
		else if(type==2)
			VERIFY(menu.LoadMenu(IDR_POPUP_RT));
		else if(type==3)
			VERIFY(menu.LoadMenu(IDR_POPUP_RT_SET));

//		InitMenu(0 ,type, del_flag);

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

/*		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();
*/
		pWndPopupOwner = &m_pMainWnd->m_wndMyBar1;
		//pPopup->EnableMenuItem(AFX_ID_BLOWUP,MF_GRAYED);
		
		if(type==0)
		{
			m_pMainWnd->NowAddMessageType=1;
			if(BCRun_flag)
			{
				pPopup->EnableMenuItem(ID_INSERTBCMES,MF_GRAYED);
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_GRAYED);
				pPopup->EnableMenuItem(ID_MESSAGEMOVE1,MF_GRAYED);
				pPopup->EnableMenuItem(ID_PROPEBC,MF_GRAYED);

				pPopup->ModifyMenu(ID_RUNBC,MF_BYCOMMAND,ID_RUNBC,">运行");
				pPopup->ModifyMenu(ID_STOPBC,MF_BYCOMMAND,ID_STOPBC," 停止");
				del_flag  = 0;
			}
			else
			{
				pPopup->ModifyMenu(ID_RUNBC,MF_BYCOMMAND,ID_RUNBC," 运行");
				pPopup->ModifyMenu(ID_STOPBC,MF_BYCOMMAND,ID_STOPBC,">停止");

				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_GRAYED);
				pPopup->EnableMenuItem(ID_MESSAGEMOVE1,MF_GRAYED);
			}
			if(del_flag==0)
			{
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_GRAYED);
				pPopup->EnableMenuItem(ID_MESSAGEMOVE1,MF_GRAYED);

				
			}
			else if(del_flag==1)
			{
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_ENABLED);
				pPopup->EnableMenuItem(ID_MESSAGEMOVE1,MF_ENABLED);
			}
		}
		if(type==1)
		{
			m_pMainWnd->NowAddMessageType=2;
			if(BCRun_flag)
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
			}
			else if(del_flag==1)
			{
				pPopup->EnableMenuItem(ID_DELETEBCMES,MF_ENABLED);
				pPopup->EnableMenuItem(ID_MESSAGEMOVE1,MF_ENABLED);
			}
		}
		if(type==2)
		{
			if(del_flag==1)
			{
				pPopup->EnableMenuItem(ID_INSERT_RT,MF_GRAYED);
			}
			else
			{
				pPopup->EnableMenuItem(ID_INSERT_RT,MF_ENABLED);
			}
		}
		if(type==3)
		{
			if(del_flag==1)
			{
				pPopup->EnableMenuItem(ID_DELETE_RT,MF_GRAYED);
				pPopup->EnableMenuItem(ID_INSERTRTMES,MF_GRAYED);
			}
			else
			{
				pPopup->EnableMenuItem(ID_DELETE_RT,MF_ENABLED);
				pPopup->EnableMenuItem(ID_INSERTRTMES,MF_ENABLED);
			}
		}

		if((type==0)||(type==1))
		{
			if(m_pMainWnd->bcmode)
			{
				pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,
				pWndPopupOwner);
			}
			else
			{
				MessageBox("BC方式无效","注意");
			}
		}
		if(type==2)
		{	
			if(m_pMainWnd->rtmode)
			{
				
				pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,
				pWndPopupOwner);
			}
			else
			{
				MessageBox("RT方式无效","注意");
			}
		}
		if(type==3)
		{	
			if(m_pMainWnd->rtmode)
			{
				
				pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,
				pWndPopupOwner);
			}
			else
			{
				MessageBox("RT方式无效","注意");
			}
		}

}

void NewTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int i;
	bool flag;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	Nowpoint = point;
	
	

	CTreeCtrl::OnRButtonDown(nFlags, point);
	
}
void NewTreeCtrl::RClickSelectItem(CPoint point)
{
	
	
}
void NewTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//	NowClickItem = finditem(this->GetRootItem(),point);
//	CString str_item;
//	str_item = this->GetItemText(NowClickItem);
//
	ExPandFlag = true;
	CTreeCtrl::OnLButtonDown(nFlags, point);
}
HTREEITEM NewTreeCtrl::finditem(HTREEITEM item, CPoint  point)   
{  
	CRect rect;
	HTREEITEM  hfind;  
	if(item ==  NULL) //空树，直接返回NULL 
	   return  NULL;  
	while(item!=NULL)  //遍历查找
	{  
		this->GetItemRect(item,rect,0);
		if(rect.PtInRect(point))//当前节点即所需查找节点
		{
//			HTREEITEM  ParentItem = this->GetParentItem(this->GetNextItem(TVI_ROOT,TVGN_CARET));
//			CString str_item;
//			str_item = this->GetItemText(ParentItem);
			SelectItem(item);
			//Select(item,TVGN_DROPHILITE );	
			//this->Expand(ParentItem,TVE_EXPAND);
			return   item;  
		}
	   //查找当前节点的子节点
	   if(ItemHasChildren(item))  
	   {  
			item   =   this->GetChildItem(item); 
			hfind   =   finditem(item,point);//递归调用查找子节点下节点  
			if(hfind!=NULL)  
			{  
				return  hfind;  
			}  
			else   
			item = this->GetNextSiblingItem(item);  //子节点中未发现所需节点，继续查找兄弟节点
	   }  
	   else//若无子节点，继续查找兄弟节点
	   {   
		   item = this->GetNextSiblingItem(item);  
	   }  

	}  
	return item;  

}


BOOL NewTreeCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
/*	MSG pMsg2;
	if(pMsg->message==WM_RBUTTONDOWN&&pMsg->wParam==MK_RBUTTON)
	{
		memcpy(&pMsg2,pMsg,sizeof(MSG));
		//pMsg2 = pMsg;
		pMsg2.message=WM_RBUTTONUP;
		pMsg2.wParam==MK_RBUTTON;
		//PeekMessage(&pMsg2,NULL,0,0,PM_REMOVE);
		CTreeCtrl::PreTranslateMessage (&pMsg2);
		//return PeekMessage(pMsg);
	}
*/		return CTreeCtrl::PreTranslateMessage(pMsg);

}

void NewTreeCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	bool flag;

	NowClickItem = finditem(this->GetRootItem(),Nowpoint);
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	//HTREEITEM SeleItem=this->GetNextItem(TVI_ROOT,TVGN_CARET);
	HTREEITEM SeleItem=NowClickItem;
	
	m_pMainWnd->NowdeletID=-1;
	flag = false;
	for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_MessageMaxCount;i++)
	{
		if(m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].BCItem[i] == SeleItem)
		{
			m_pMainWnd->NowdeletID=i;
			flag = true;
			break;
			
		}
	}
	if(flag==false)
	for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_MessageMaxCount_2;i++)
	{
		if(m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].BCItemNo[i] == SeleItem)
		{
			m_pMainWnd->NowdeletID=i;
			flag = true;
			break;
			
		}
	}


	CString str_cmp,Parent_Name;
	CRect rect;
	//SeleItem = this->GetNextItem(TVI_ROOT,TVGN_CARET);
	GetItemRect(SeleItem,rect,0);
	if(rect.PtInRect(Nowpoint))
	{
		if((SeleItem!=NULL))
		{
			
			HTREEITEM parentItem = this->GetParentItem(SeleItem);
			CString Data_file = this->GetItemText(SeleItem);
			Parent_Name = this->GetItemText(this->GetParentItem(SeleItem));
			if(Data_file=="BC周期消息")
			{
				OnContextMenu(this,Nowpoint,0,0);
			}
			if(Data_file=="BC非周期消息")
			{
				OnContextMenu(this,Nowpoint,1,0);
			}
			else if(Parent_Name=="BC周期消息")
			{
				OnContextMenu(this,Nowpoint,0,1);
			}
			else if(Parent_Name=="BC非周期消息")
			{
				OnContextMenu(this,Nowpoint,1,1);
			}
			else if(Data_file=="远程终端-RTs")
			{
				OnContextMenu(this,Nowpoint,2,0);
			}
			else if(Parent_Name=="远程终端-RTs")
			{
				for(i=0;i<32;i++)
				{
					str_cmp.Format("RT%2d",i);
					if(str_cmp==Data_file)
					{
						m_pMainWnd->NowSelectRT = i;
						break;
					}
				}
				OnContextMenu(this,Nowpoint,3,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_stutas);
			}
			//CString Data_file2 = m_Tree.GetItemText(m_Tree.GetParentItem(parentItem));
		}
	}
	*pResult = 0;
}

void NewTreeCtrl::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CTreeCtrl::OnRButtonDblClk(nFlags, point);
}

void NewTreeCtrl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void NewTreeCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ExPandFlag = false;
	CTreeCtrl::OnRButtonUp(nFlags, point);
}


void NewTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString str_cmp,Parent_Name;
	int i;

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	

	HTREEITEM SeleItem = this->GetNextItem(TVI_ROOT,TVGN_CARET);

	if((SeleItem!=NULL))
	{
		HTREEITEM parentItem = this->GetParentItem(SeleItem);
		CString Data_file = this->GetItemText(SeleItem);
		Parent_Name = this->GetItemText(this->GetParentItem(SeleItem));
		if((Parent_Name=="BC非周期消息")||(Parent_Name=="BC非周期消息"))
		{
			m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].ShowWindow(SW_SHOWNA);
		}
		else if(Parent_Name=="远程终端-RTs")
		{
			for(i=0;i<32;i++)
			{
				if(SeleItem == m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].RTItem[i])
				{
					//m_pMainWnd->RTView[i].ShowWindow(SW_SHOWNA);
					CRTDataSet RTSetDlg;
					RTSetDlg.IniType = 1;//
					RTSetDlg.RTAdress = i;//
					RTSetDlg.SubAdress = 1;//
					RTSetDlg.DoModal();
					break;
				}
			}
		}
		else if(Data_file=="数字量I/O")
		{
		//	CIODlg dlg;
		//	dlg.DoModal();

		}
	}

	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}

void NewTreeCtrl::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	if(ExPandFlag)
	{
	}
	else
	{
		HTREEITEM SeleItem = this->GetNextItem(TVI_ROOT,TVGN_CARET);

		CString str_item;
		str_item = this->GetItemText(SeleItem);

		if((str_item=="Bus Controller-BC")||(str_item=="RTs")||(str_item=="Config 1553 project")||(str_item=="Bus Monitor"))
		{
			*pResult = 0;	
		}
		else 
		{
		
			if (pNMTreeView->action == TVE_COLLAPSE) 
			{ 
				*pResult = TRUE; 
			} 
			else 
			{ 
				*pResult = 0; 
			} 
		}	
	}
	
	ExPandFlag = false;
}



void NewTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void NewTreeCtrl::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void NewTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	ExPandFlag = false;
	*pResult = 0;
}
