// RTListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "RTListCtrl.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTListCtrl

CRTListCtrl::CRTListCtrl()
{
}

CRTListCtrl::~CRTListCtrl()
{
}


BEGIN_MESSAGE_MAP(CRTListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CRTListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRTListCtrl message handlers

void CRTListCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int i;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	CString strName,strName2;
	this->GetParent()->GetWindowText(strName2);
	for(i=0;i<32;i++)
	{
		strName.Format("RT%2d",i);
		if(strName==strName2)
		{
			m_pMainWnd->NowSelectRT = i;
			break;
		}
	}
	OnContextMenu(this,NowPoint);
	*pResult = 0;
}
void CRTListCtrl::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	NowPoint = point;
	CListCtrl::OnRButtonUp(nFlags, point);
}

void CRTListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	NowPoint = point;

	CListCtrl::OnRButtonDown(nFlags, point);
}

void CRTListCtrl::OnContextMenu(CWnd *, CPoint point)
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
		VERIFY(menu.LoadMenu(IDR_POPUP_RT_SET));


//		InitMenu(0 ,type, del_flag);

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		//pPopup->EnableMenuItem(AFX_ID_BLOWUP,MF_GRAYED);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,pWndPopupOwner);

}


