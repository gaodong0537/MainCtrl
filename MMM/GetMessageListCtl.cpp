// GetMessageListCtl.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "GetMessageListCtl.h"
#include "BMview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GetMessageListCtl

GetMessageListCtl::GetMessageListCtl()
{
}

GetMessageListCtl::~GetMessageListCtl()
{
}


BEGIN_MESSAGE_MAP(GetMessageListCtl, CListCtrl)
	//{{AFX_MSG_MAP(GetMessageListCtl)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GetMessageListCtl message handlers

void GetMessageListCtl::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	NowPoint = point;
	((CBMview*)this->GetParent())->HideDataDlg();
	CListCtrl::OnMouseMove(nFlags, point);
}

void GetMessageListCtl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
/*	int SelectID;
	LVFINDINFO FindVal;
	FindVal.flags = LVFI_NEARESTXY;
    FindVal.psz = "";
    FindVal.lParam = NULL;
    FindVal.pt = OldPoint;
    FindVal.vkDirection = NULL;

	if(OldPoint==NowPoint)//Êó±êÍ£Ö¹
	{
		FindVal.pt = NowPoint;
		SelectID = this->FindItem(&FindVal,-1);
	}
	OldPoint = NewPoint;

	NewPoint = NowPoint;
*/	CListCtrl::OnTimer(nIDEvent);
}

int GetMessageListCtl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
void GetMessageListCtl::Init()
{
	OldPoint.x = 0;
	OldPoint.y = 0;

	this->SetTimer(0,100,NULL);
}

void GetMessageListCtl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListCtrl::OnLButtonUp(nFlags, point);
	
}

void GetMessageListCtl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListCtrl::OnLButtonDown(nFlags, point);
}

void GetMessageListCtl::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	((CBMview*)this->GetParent())->OnButtonDown();
	*pResult = 0;
}
