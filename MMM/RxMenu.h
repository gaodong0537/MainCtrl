// RxMenu.h: interface for the CRxMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RXMENU_H__513BDB13_9C81_4C42_BC20_E1A6817ED0ED__INCLUDED_)
#define AFX_RXMENU_H__513BDB13_9C81_4C42_BC20_E1A6817ED0ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRxMenu:public CMenu
{
public:
	virtual void DrawItemText(CDC* pDC,UINT itemID,CRect rcWnd,bool IsSelect=false);
	virtual void DrawVCaption(CDC* pDC,CRect rcWnd,CString sCaption);
	virtual	void MeasureItem(LPMEASUREITEMSTRUCT lpMea);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	CRxMenu();
	virtual ~CRxMenu();
private:
	int m_nTitleWidth;    
	int m_nTotalHeight;
	CFont m_TextFont;
	CFont m_TitleFont;
};

#endif // !defined(AFX_RXMENU_H__513BDB13_9C81_4C42_BC20_E1A6817ED0ED__INCLUDED_)
