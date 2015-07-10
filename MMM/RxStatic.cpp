// RxStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "RxStatic.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRxStatic

CRxStatic::CRxStatic()
{
	 m_lpFont="宋体";
	 m_nSize=9;
	 m_FontColor=RGB(0,0,0);
	 m_BkColor=CLARITY;
	 m_bItalic=false;
	 m_bBold=false;
	 m_bUnderline=false;
	 m_dwCharacter=CHINESE;
	 m_bIsShadow=false;
	 m_ShadowColor=RGB(32,32,32);
	 m_nInterval=3;
	 m_nAngle=45;

}

CRxStatic::~CRxStatic()
{
}


BEGIN_MESSAGE_MAP(CRxStatic, CStatic)
	//{{AFX_MSG_MAP(CRxStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRxStatic message handlers

void CRxStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CFont font;
	int nBold;
	if(m_bBold==true)
		nBold=FW_BOLD;
	else
		nBold=FW_NORMAL;
	LOGFONT lgFont;
	lgFont.lfCharSet=m_dwCharacter;
	lgFont.lfClipPrecision=0;
	lgFont.lfEscapement=0;
	strcpy(lgFont.lfFaceName,m_lpFont);
	lgFont.lfHeight=m_nSize+3;
	lgFont.lfItalic=m_bItalic;
	lgFont.lfOrientation=0;
	lgFont.lfOutPrecision=0;
	lgFont.lfPitchAndFamily=2;
	lgFont.lfQuality=0;
	lgFont.lfStrikeOut=0;
	lgFont.lfUnderline=m_bUnderline;
	lgFont.lfWeight=nBold;
	lgFont.lfWidth=0;
	font.CreateFontIndirect(&lgFont);
	CFont* pFont;
	pFont=dc.SelectObject(&font);
	CString sCaption;
	CRect rcWnd;
	this->GetClientRect(&rcWnd);
	this->GetWindowText(sCaption);
	DWORD dwStyle,dwDCStyle;
	dwStyle=this->GetStyle();
	if(dwStyle&SS_CENTER==SS_CENTER )//居中显示
		dwDCStyle=DT_CENTER;
	if(dwStyle&SS_SIMPLE ==SS_SIMPLE)   //单行
		dwDCStyle=dwDCStyle|DT_SINGLELINE|DT_VCENTER;
	if(m_bIsShadow==true)  //阴影
	{
		//根据角度计算出阴影位置
		float fx=cos(m_nAngle)*m_nInterval;
		float fy=sin(m_nAngle)*m_nInterval;
		CRect rcShadow;
		rcShadow=rcWnd;
		rcShadow.left=(float)rcShadow.left+fx;
		rcShadow.right=(float)rcShadow.right+fx;
		rcShadow.top=(float)rcShadow.top+fy;
		rcShadow.bottom=(float)rcShadow.bottom +fy;
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_ShadowColor);
		dc.DrawText(sCaption,rcShadow,dwDCStyle);
	}
		dc.SetBkMode(OPAQUE);
	if(m_BkColor==CLARITY)
		dc.SetBkMode(TRANSPARENT);
	else
		dc.SetBkColor(m_BkColor);
	dc.SetTextColor(m_FontColor);
	dc.DrawText(sCaption,rcWnd,dwDCStyle);
	font.DeleteObject();
	dc.SelectObject(pFont);
	// Do not call CStatic::OnPaint() for painting messages
}

void CRxStatic::SetFont(CString sFontName,DWORD lpLanguage)
{
	m_lpFont=sFontName;	
	m_dwCharacter=lpLanguage;
}

void CRxStatic::SetFontSize(int nSize)
{
	m_nSize=nSize;
}

void CRxStatic::SetTextColor(COLORREF dwColor)
{
	m_FontColor=dwColor;
}

void CRxStatic::SetBkColor(COLORREF dwColor)
{
	m_BkColor=dwColor;
}

void CRxStatic::SetFontStyle(bool bItalic,bool bBold,bool bUnderline)
{
	m_bItalic=bItalic;
	m_bBold=bBold;
	m_bUnderline=bUnderline;
}

void CRxStatic::SetShadow(bool bShadow,COLORREF cShadowColor,int nInterval,int nAngle)
{
	m_bIsShadow=bShadow;
	m_ShadowColor=cShadowColor;
	m_nInterval=nInterval;
	m_nAngle=nAngle;
}
