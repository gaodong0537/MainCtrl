// CntrItem.cpp : implementation of the CMy1553CntrItem class
//

#include "stdafx.h"
#include "ManCtrl.h"

#include "ManCtrlDoc.h"
#include "ManCtrlView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy1553CntrItem implementation

IMPLEMENT_SERIAL(CMy1553CntrItem, COleClientItem, 0)

CMy1553CntrItem::CMy1553CntrItem(CMy1553Doc* pContainer)
	: COleClientItem(pContainer)
{
	// TODO: add one-time construction code here
	
}

CMy1553CntrItem::~CMy1553CntrItem()
{
	// TODO: add cleanup code here
	
}

void CMy1553CntrItem::OnChange(OLE_NOTIFICATION nCode, DWORD dwParam)
{
	ASSERT_VALID(this);

	COleClientItem::OnChange(nCode, dwParam);

	// When an item is being edited (either in-place or fully open)
	//  it sends OnChange notifications for changes in the state of the
	//  item or visual appearance of its content.

	// TODO: invalidate the item by calling UpdateAllViews
	//  (with hints appropriate to your application)

	GetDocument()->UpdateAllViews(NULL);
		// for now just update ALL views/no hints
}

BOOL CMy1553CntrItem::OnChangeItemPosition(const CRect& rectPos)
{
	ASSERT_VALID(this);

	// During in-place activation CMy1553CntrItem::OnChangeItemPosition
	//  is called by the server to change the position of the in-place
	//  window.  Usually, this is a result of the data in the server
	//  document changing such that the extent has changed or as a result
	//  of in-place resizing.
	//
	// The default here is to call the base class, which will call
	//  COleClientItem::SetItemRects to move the item
	//  to the new position.

	if (!COleClientItem::OnChangeItemPosition(rectPos))
		return FALSE;

	// TODO: update any cache you may have of the item's rectangle/extent

	return TRUE;
}

void CMy1553CntrItem::OnGetItemPosition(CRect& rPosition)
{
	ASSERT_VALID(this);

	// During in-place activation, CMy1553CntrItem::OnGetItemPosition
	//  will be called to determine the location of this item.  The default
	//  implementation created from AppWizard simply returns a hard-coded
	//  rectangle.  Usually, this rectangle would reflect the current
	//  position of the item relative to the view used for activation.
	//  You can obtain the view by calling CMy1553CntrItem::GetActiveView.

	// TODO: return correct rectangle (in pixels) in rPosition

	rPosition.SetRect(10, 10, 210, 210);
}

void CMy1553CntrItem::OnActivate()
{
    // Allow only one inplace activate item per frame
    CMy1553View* pView = GetActiveView();
    ASSERT_VALID(pView);
    COleClientItem* pItem = GetDocument()->GetInPlaceActiveItem(pView);
    if (pItem != NULL && pItem != this)
        pItem->Close();
    
    COleClientItem::OnActivate();
}

void CMy1553CntrItem::OnDeactivateUI(BOOL bUndoable)
{
	COleClientItem::OnDeactivateUI(bUndoable);

    // Hide the object if it is not an outside-in object
    DWORD dwMisc = 0;
    m_lpObject->GetMiscStatus(GetDrawAspect(), &dwMisc);
    if (dwMisc & OLEMISC_INSIDEOUT)
        DoVerb(OLEIVERB_HIDE, NULL);
}

void CMy1553CntrItem::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	// Call base class first to read in COleClientItem data.
	// Since this sets up the m_pDocument pointer returned from
	//  CMy1553CntrItem::GetDocument, it is a good idea to call
	//  the base class Serialize first.
	COleClientItem::Serialize(ar);

	// now store/retrieve data specific to CMy1553CntrItem
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMy1553CntrItem diagnostics

#ifdef _DEBUG
void CMy1553CntrItem::AssertValid() const
{
	COleClientItem::AssertValid();
}

void CMy1553CntrItem::Dump(CDumpContext& dc) const
{
	COleClientItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
