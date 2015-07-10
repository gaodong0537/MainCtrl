// RxMenu.cpp: implementation of the CRxMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Flash.h"
#include "RxMenu.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRxMenu::CRxMenu()
{
	m_nTitleWidth=0;
	m_nTotalHeight=0;
	//��ʼ������
	LOGFONT logFont;
	logFont.lfCharSet=134;
	logFont.lfClipPrecision=0;
	logFont.lfEscapement=0;
	strcpy(logFont.lfFaceName,"����");
	logFont.lfHeight=12;
	logFont.lfItalic=0;
	logFont.lfOrientation=0;
	logFont.lfOutPrecision=0;
	logFont.lfPitchAndFamily=2;
	logFont.lfQuality=0;
	logFont.lfStrikeOut=0;
	logFont.lfUnderline=0;
	logFont.lfWeight=400;
	logFont.lfWidth=0;
	m_TextFont.CreateFontIndirect(&logFont);
	logFont.lfWeight=400;
	strcpy(logFont.lfFaceName,"����ϸ��");
	logFont.lfHeight=15;
	logFont.lfOrientation=900;
	logFont.lfEscapement=900;
	m_TitleFont.CreateFontIndirect(&logFont);
}

CRxMenu::~CRxMenu()
{
  m_TextFont.DeleteObject();
  m_TitleFont.DeleteObject();

}

void CRxMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CString sText = lpDrawItemStruct->itemData;
	CRect rcTmp;
	rcTmp=lpDrawItemStruct->rcItem;
	lpDrawItemStruct->rcItem.left=lpDrawItemStruct->rcItem.left+m_nTitleWidth;//�ճ��������
	if (lpDrawItemStruct->itemAction & ODA_DRAWENTIRE && !(lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		//��䱳��
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem,RGB(243,243,243));
		//������Ŀ
		DrawItemText(pDC,lpDrawItemStruct->itemID,CRect(lpDrawItemStruct->rcItem));
		int ItemCount=::GetMenuItemCount((HMENU)lpDrawItemStruct->hwndItem);
		UINT FistID=::GetMenuItemID((HMENU)lpDrawItemStruct->hwndItem,0);
		if(lpDrawItemStruct->itemID==FistID)//����ˢ����ʾ��һ��Ŀʱ�������������
		{
			if(!(lpDrawItemStruct->itemAction&ODA_SELECT))
				DrawVCaption(pDC,CRect(0,0,m_nTitleWidth,m_nTotalHeight),"  ");
		}
	}

	if ((lpDrawItemStruct->itemState & ODS_SELECTED) &&(lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{	//����ѡ��״̬
		CPen pen;
		pen.CreatePen(PS_SOLID,1,RGB(49,106,197));
		CPen* pPen;
		pPen=pDC->SelectObject(&pen);
	  	pDC->Rectangle(&lpDrawItemStruct->rcItem);
		pDC->SelectObject(pPen);
		pen.DeleteObject();
		rcTmp.top=lpDrawItemStruct->rcItem.top+1;
		rcTmp.bottom=lpDrawItemStruct->rcItem.bottom-1;
		rcTmp.left=lpDrawItemStruct->rcItem.left+1;
		rcTmp.right=lpDrawItemStruct->rcItem.right-1;
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITITEM);
		CDC tmpDC;
		tmpDC.CreateCompatibleDC(pDC);
		tmpDC.SelectObject(&bmp);
		BITMAP bmpstr;
		bmp.GetBitmap(&bmpstr);
		pDC->StretchBlt(rcTmp.left,rcTmp.top,rcTmp.Width(),rcTmp.Height(),&tmpDC,0,0,bmpstr.bmWidth,bmpstr.bmHeight,SRCCOPY);
		tmpDC.DeleteDC();
		bmp.DeleteObject();
		DrawItemText(pDC,lpDrawItemStruct->itemID,CRect(lpDrawItemStruct->rcItem),TRUE);
	}

	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) &&(lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		//����ȡ��ѡ��״̬
		pDC->FillSolidRect(&lpDrawItemStruct->rcItem,RGB(243,243,243));
		DrawItemText(pDC,lpDrawItemStruct->itemID,CRect(lpDrawItemStruct->rcItem));
	}
	
}

void CRxMenu::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItem)
{
	CDC *pDC= AfxGetApp()->m_pMainWnd->GetDC();
	m_TextFont.m_hObject!=NULL;
	CFont* oldFont=NULL;
	//������������ʾ�ַ�������˵���Ϣ
	if(!m_nTitleWidth)
	{
		TEXTMETRIC TextMetr; 
		oldFont = pDC->SelectObject(&m_TitleFont); 
		pDC->GetTextMetrics(&TextMetr);
		m_nTitleWidth=TextMetr.tmHeight+10;    //�����ʾ���ڵĿ��
		pDC->SelectObject(oldFont); 
	}
     oldFont = pDC->SelectObject(&m_TextFont); 	 
	 CSize itemSize;
	 if(strlen((char*)lpMeasureItem->itemData))//�����ı��ĳ���
	 {
		itemSize=pDC->GetTextExtent((char*)lpMeasureItem->itemData,lstrlen((char*)lpMeasureItem->itemData)); 
        lpMeasureItem->itemWidth = itemSize.cx+m_nTitleWidth+10; 
        lpMeasureItem->itemHeight = itemSize.cy+10; 
	 }
	 else
		lpMeasureItem->itemHeight=12;
		//�ۼӸ߶�
	m_nTotalHeight=m_nTotalHeight+lpMeasureItem->itemHeight;
    pDC->SelectObject(oldFont); 
    AfxGetApp()->m_pMainWnd->ReleaseDC(pDC);
	//ͳ�Ƴ��˵��߶�	
}

void CRxMenu::DrawVCaption(CDC *pDC, CRect rcWnd,CString sCaption)
{
	//��������������
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITLEFT);
	CDC tmpDC;
	tmpDC.CreateCompatibleDC(pDC);
	tmpDC.SelectObject(&bmp);
	BITMAP bmpstr;
	bmp.GetBitmap(&bmpstr);
	pDC->StretchBlt(0,0,rcWnd.Width(),rcWnd.Height(),&tmpDC,0,0,bmpstr.bmWidth,bmpstr.bmHeight,SRCCOPY);
	tmpDC.DeleteDC();
	bmp.DeleteObject();
	//������������
	CFont* pFont=pDC->SelectObject(&m_TitleFont);
	pDC->SetTextColor(RGB(51,106,198));
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(rcWnd.left+6,rcWnd.bottom-5,sCaption);
	pDC->SelectObject(pFont);
}

void CRxMenu::DrawItemText(CDC *pDC,UINT itemID, CRect rcWnd, bool IsSelect)
{
	UINT itemState=GetMenuState(itemID,MF_BYCOMMAND);
	CString sText;
	GetMenuString(itemID,sText,MF_BYCOMMAND);
	if(itemState&MF_SEPARATOR)
	{	//��ʾ�ָ���
		pDC->FillSolidRect(&rcWnd,RGB(234,234,234));			
		pDC->Draw3dRect(&CRect(rcWnd.left+2,rcWnd.top+rcWnd.Height()/2,rcWnd.right,rcWnd.top+rcWnd.Height()/2+2),::GetSysColor(COLOR_BTNSHADOW),::GetSysColor(COLOR_BTNHIGHLIGHT));
		return;
	}
	if(sText.IsEmpty())
		return;
  	pDC->SetBkMode(TRANSPARENT);
  	CFont* oldFont = pDC->SelectObject (&m_TextFont);  
	if(itemState&MF_GRAYED)
	{
		if(!IsSelect)
		{
			pDC->FillSolidRect(&rcWnd,RGB(192,230,238));			
			pDC->DrawText(sText,-1,&rcWnd,DT_VCENTER | DT_CENTER | DT_SINGLELINE);			
		}
		pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
    }
	else if(IsSelect)
	{
		pDC->SetTextColor(RGB(0,0,0));	
	}
	else
		pDC->FillSolidRect(&rcWnd,RGB(234,234,234));			
	pDC->DrawText(sText,-1,&rcWnd,DT_VCENTER | DT_CENTER | DT_SINGLELINE);	
	pDC->SelectObject(oldFont);	
	
}
