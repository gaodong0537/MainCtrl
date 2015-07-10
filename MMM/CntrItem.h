// CntrItem.h : interface of the CMy1553CntrItem class
//

#if !defined(AFX_CNTRITEM_H__FFB93D36_777A_4ED1_BE5F_0991A0833D4B__INCLUDED_)
#define AFX_CNTRITEM_H__FFB93D36_777A_4ED1_BE5F_0991A0833D4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMy1553Doc;
class CMy1553View;

class CMy1553CntrItem : public COleClientItem
{
	DECLARE_SERIAL(CMy1553CntrItem)

// Constructors
public:
	CMy1553CntrItem(CMy1553Doc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CMy1553Doc* GetDocument()
		{ return (CMy1553Doc*)COleClientItem::GetDocument(); }
	CMy1553View* GetActiveView()
		{ return (CMy1553View*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1553CntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CMy1553CntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__FFB93D36_777A_4ED1_BE5F_0991A0833D4B__INCLUDED_)
