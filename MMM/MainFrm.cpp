// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "MainFrm.h"
#include "TypeDefine.h"
#include "Project.h"
#include "RTSelectDlg.h"
#include "BCPROPER.h"
#include "FirstDlg.h"
#include "RTDataSet.h"
#include "1553select.h"
//#include "RTProp.h"
#include "busapi.h"
#include <windows.h>
#include <iostream.h>
#include "Shlwapi.h"
#include "AllDefine.h"

#include "WorkModeSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW

#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCRBUTTONDOWN()
	ON_COMMAND(ID_CURRENTPR1,OpenCurrent1)
	ON_COMMAND(ID_CURRENTPR2,OpenCurrent2)
	ON_COMMAND(ID_CURRENTPR3,OpenCurrent3)
	ON_COMMAND(ID_SENDNOWMESSAGE,SendMessgeNowSelecte)
	ON_COMMAND(AFX_ID_SHOWPROJ,ShowProject)
	ON_COMMAND(ID_INSERTBCMES_TIMER,InsertTimerMessage)
	ON_COMMAND(ID_INSERTBCMES_NOTIMRE,InsertNOTimerMessage)
	ON_COMMAND(ID_INSERTBCMES, InsertBCMessage)
	ON_COMMAND(ID_DELETEBCMES, DeleteBCMessage)
	ON_COMMAND(ID_MOVEUPMESSAGE, MoveUpBCMessage)
	ON_COMMAND(ID_MOVEDOWNMESSAGE, MoveDownBCMessage)
	ON_COMMAND(ID_FILE_NEW,NewSetMessage)
	ON_COMMAND(ID_FILE_SAVE,SaveMessageSet)
	ON_COMMAND(ID_FILE_OPEN,OpenMessageSet)
	ON_COMMAND(ID_RUNBC, RunBC)
	ON_COMMAND(ID_STOPBC, StopBC)
	ON_COMMAND(ID_RUN_RT,RunRT)
	ON_COMMAND(ID_STOP_RT,StopRT)
	ON_COMMAND(ID_STEPRUNBC,StepRun)
	ON_COMMAND(ID_PROPEBC,OnProper)
	ON_COMMAND(ID_INSERT_RT,InsertRTData)
	ON_COMMAND(ID_DELETE_RT,DeleteRT)
	ON_COMMAND(AFX_ID_VIEWSHOW,ShowRTdata)
	ON_COMMAND(ID_ENABLE_RT,RT_Enable)
	ON_COMMAND(ID_DISABLE_RT,RT_Disable)
	ON_COMMAND(ID_VIEW_BC,View_BC)
	ON_COMMAND(ID_VIEW_RT,View_RT)
	ON_COMMAND(ID_VIEW_BM,View_BM)
	ON_COMMAND(ID_INSERTRTMES,EditRTdata)
	ON_COMMAND(ID_PROP_RT,CPropRT)
	ON_COMMAND(ID_MESSAGEMOVE1,MoveBCMessage)
	ON_COMMAND(ID_SENDNOTIMEBC,SendNotimeMessage)
	ON_COMMAND(AFX_ID_OPENMESSAGE,ReadMessageTeam)
	ON_COMMAND(AFX_ID_SAVEMESSAGE,SaveMessageTeam)
	ON_COMMAND(AFX_ID_ENABLEMESSAGE,EnableMessge)
	ON_COMMAND(AFX_ID_DISABLEMESSAGE,DisableMessge)
	ON_COMMAND(ID_CHANGE1553,Change1553 )
	ON_COMMAND(ID_CHANGE_MAINCTRL,ChangeMainCtrl )
	ON_WM_NCLBUTTONUP()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int i;

	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect,rect2;
	int xpos,ypos;
	xpos = ::GetSystemMetrics(SM_CXSCREEN)-3;
	ypos = ::GetSystemMetrics(SM_CYSCREEN)-3;

	
	

// 	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
// 		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
// 		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
// 	{
// 		TRACE0("Failed to create toolbar\n");
// 		return -1;      // fail to create
// 	}

/*	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
	{
		return -1;      
 }
	CImageList img;
	img.Create(32,32,ILC_COLOR24|ILC_MASK,1,1);
	img.Add(AfxGetApp()->LoadIcon(IDI_ADDTASK));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&img);
	img.Detach();
	m_wndToolBar.SetSizes(CSize(40,40),CSize(32,32)); //设置按钮和图标的大小
	m_wndToolBar.SetButtonInfo(0,ID_NEW_TASK,TBBS_BUTTON,0);
//RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);//加载工具栏 */



	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);

	FlashMenu();

	//窗口最大化
	DWORD dwMsg;
	dwMsg=SC_MAXIMIZE;
	SendMessage(WM_SYSCOMMAND,dwMsg,MAKELPARAM(xpos, ypos));


	TimeShowFlag = true;
	HightSpeedMode = false;
	CFirstDlg FirstDlg;
	BT_INT stutas;
	if(FirstDlg.DoModal()==IDOK)
	{

		MAX_1553BChanel =FirstDlg.Max_Select_Channel+1;
		if(FirstDlg.Countinu==0)
		{
			MessageData1553[0].NowCardNO = FirstDlg.board;
			stutas = MessageData1553[0].OpenHardware();

			for(i=0;i<MAX_1553BChanel;i++)
			{
				MessageData1553[i].NowCardNO = i;
				MessageData1553[i].InitMessageTeam();
				MessageData1553[i].InitBC();
				MessageData1553[i].StopBC();
				MessageData1553[i].StopRT();

			}
		}
		else
		{
			//
			//this->DestroyWindow();
			return -1; 
		}
	}
	 

	if(stutas==API_SUCCESS )
	{
		MessageBox("硬件初始化成功","提示");
	}
	else
	{
		MessageBox("硬件初始化失败，请检查","提示",MB_ICONERROR);
	}
		this->GetClientRect(rect);
/*
		ProjectDlg.Create("","",NULL,CRect(0,0,50,50),this,IDD_NEWPROJECTDLG,NULL);
		ProjectDlg.GetWindowRect(rect2);
		ProjectDlg.MoveWindow(0,72,rect2.right-rect2.left,rect2.bottom - rect2.top,false);
		ProjectDlg.ShowWindow(SW_SHOW);
*/


		
		////////////创建TAB Control，并把它加入到ControlBar中
		/// 需要注意的是:同一个ControlBar只能加入一个"一级子窗口"
		//m_TabCtrl.Create(TCS_DOWN|WS_CHILD|WS_VISIBLE,CRect(0,0,100,100),&m_wndMyBar1,125);
		/////////////这一段代码创建树型控件////////////
		/*if (!ProjectDlg.Create(WS_CHILD|WS_VISIBLE|
			TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
			CRect(0, 0, 0, 0), &m_TabCtrl, IDC_MYTREECTRL))
		{
			TRACE0("Failed to create instant bar child\n");
			return -1;
		}
		*/
		
		//CWorkModeSelect WorkModeDlg;

		//if(WorkModeDlg.DoModal()==IDOK)
		
		/*	bcmode = WorkModeDlg.m_bcmode;
			rtmode = WorkModeDlg.m_rtmode;
			bmmode = WorkModeDlg.m_bmmode;
	*/
		int ShouWith,m_Channel;
		ShouWith = (rect.right - rect2.right)/2;

		bcmode = true ;
		rtmode = true;
		bmmode = true;
		for(m_Channel =0 ;m_Channel<MAX_1553BChanel*2;m_Channel++)
		{
		
			

			BCView[m_Channel].HaveCreate = 0;
			BCView[m_Channel].MaxRect = rect;
			BCView[m_Channel].MaxRect.left = BCView[m_Channel].MaxRect.left+rect2.right;
			BCView[m_Channel].MaxRect.top = BCView[m_Channel].MaxRect.top+72;

			BCView[m_Channel].Create("","",NULL,CRect(0,0,50,50),this,IDD_NEWBCVIEW,NULL);
			BCView[m_Channel].GetWindowRect(rect2);
			rect2.right = rect2.left+ShouWith;
			//BCView[m_now_SelectChannel].MoveWindow(240,67,rect2.right-rect2.left,rect2.bottom - rect2.top,false);
			BCView[m_Channel].MoveWindow(240,72,rect.right-245,rect.bottom/2-10,false);
			
			if(bcmode) BCView[m_Channel].ShowWindow(SW_HIDE);

			BMView[m_Channel].HaveCreate = 0;
			BMView[m_Channel].MaxRect = BCView[m_Channel].MaxRect;
			int NowSelectRT;
			for(NowSelectRT=0;NowSelectRT<32;NowSelectRT++)
			{
				for(i=0;i<32;i++)
				{
					BMView[m_Channel].Exce_Flag[NowSelectRT][i] = true ;
				}
			}

			BMView[m_Channel].ModeShow = false;

			CRect tempRect;
			tempRect = rect2;
			BMView[m_Channel].Create("","",NULL,CRect(0,0,50,50),this,IDD_NEWBCVIEW,NULL);
			BMView[m_Channel].GetWindowRect(rect2);
			rect2.right = rect2.left+ShouWith;
			BMView[m_Channel].MoveWindow(240,rect.bottom/2+60,rect.right-245,rect.bottom/2-50,false);
			if(bmmode) BMView[m_Channel].ShowWindow(SW_HIDE);

			for(i=0;i<32;i++)
			{
				RTView[m_Channel][i].Create("","",NULL,CRect(0,0,50,50),this,IDD_NEWBCVIEW,NULL);
				RTView[m_Channel][i].GetWindowRect(rect2);
				RTView[m_Channel][i].MoveWindow(350+20*i,82+20*i,rect2.right-rect2.left,rect2.bottom - rect2.top,false);
				RTView[m_Channel][i].ShowWindow(SW_HIDE);
			}
		}

		if(bcmode) BCView[0].ShowWindow(SW_HIDE);
		if(bmmode) BMView[0].ShowWindow(SW_HIDE);
		///////////////////////////////////////////////

		m_now_SelectChannel = 0;
		/////////////创建控制条///////////////
		if (!m_wndMyBar1.Create(_T("工程控制栏"), this, CSize(230,500),TRUE,123))
		{
			TRACE0("Failed to create mybar\n");
				return -1;
		}
		

		Tab1553Sel.CreatedFlag = false;
		Tab1553Sel.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,50,50),&m_wndMyBar1,IDD_NEWPROJECTDLG,NULL);
		//m_TabCtrl.GetWindowRect(rect2);
		//ProjectDlg.MoveWindow(rect2,false);
		
		Tab1553Sel.ShowWindow(SW_SHOW);
		Tab1553Sel.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

		m_wndMyBar1.SetBarStyle(m_wndMyBar1.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
		m_wndMyBar1.EnableDocking(CBRS_ALIGN_LEFT );
		DockControlBar(&m_wndMyBar1,AFX_IDW_DOCKBAR_LEFT);
		Tab1553Sel.CreatedFlag = true;

		m_wndMyBar1.GetWindowRect(rect2);
		
		m_wndMyBar1.ShowWindow(SW_SHOW);
		//////////////////////////////////////////////////////
		BM_GetFlag = false;
		SetTimer(0,5,NULL);

		SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, FALSE, NULL, 0);//禁止进入品报
		return 0;

	/*
		RTView[m_now_SelectChannel][m_now_SelectChannel].Create("","",NULL,CRect(0,0,50,50),this,IDD_NEWBCVIEW,NULL);
		RTView[m_now_SelectChannel][m_now_SelectChannel].GetWindowRect(rect2);
		RTView[m_now_SelectChannel][m_now_SelectChannel].MoveWindow(260,82,rect2.right-rect2.left,rect2.bottom - rect2.top,false);
		RTView[m_now_SelectChannel][m_now_SelectChannel].ShowWindow(SW_HIDE);
	*/

//	else return false;

	
}
void CMainFrame::ShowProject_Channel(int ShowChennel)
{
	int i;

	for(i=0;i<MAX_1553BChanel;i++)
	{
		BMView[i].ShowWindow(SW_HIDE);
		BCView[i].ShowWindow(SW_HIDE);
	}
	m_now_SelectChannel = ShowChennel;
	BMView[m_now_SelectChannel].ShowWindow(SW_SHOW);
	BCView[m_now_SelectChannel].ShowWindow(SW_SHOW);
	
}
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
/*
void CMainFrame::DrawTitleBar(CDC *pDC)
{
	if (m_hWnd)
	{
		
		//准备画XP风格按钮
		CPoint point;
		CBitmap* pBitmap = new CBitmap;
		CBitmap* pOldBitmap;
		CDC* pDisplayMemDC=new CDC;
		BOOL bActive=FALSE;
        // 创建显示用设备环境
		pDisplayMemDC->CreateCompatibleDC(pDC);
		CRect rtWnd, rtTitle, rtButtons;
		// 得到当前窗口区域
		GetWindowRect(&rtWnd); 

		// 若当前活动窗口为本例程窗口，bActive=TRUE;
		if(::GetActiveWindow()==m_hWnd)
		   bActive=TRUE;	
	
		//取得标题栏的位置
		rtTitle.left = GetSystemMetrics(SM_CXFRAME);
		rtTitle.top = GetSystemMetrics(SM_CYFRAME);
		rtTitle.right = rtWnd.right - rtWnd.left - GetSystemMetrics(SM_CXFRAME)-3;
		rtTitle.bottom = rtTitle.top + GetSystemMetrics(SM_CYSIZE);

		//填充顶部框架	
		point.x = rtWnd.Width();
		point.y = GetSystemMetrics(SM_CYSIZE) + GetSystemMetrics(SM_CYFRAME)+1;
		if(bActive)
	   	    pBitmap->LoadBitmap(IDB_TITLEBARIN);
		else
			pBitmap->LoadBitmap(IDB_TITLEBAROUT);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(0,0,point.x, point.y, pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

	    //填充左侧框架
		point.x = GetSystemMetrics(SM_CXFRAME)+1;
		point.y = rtWnd.Height();
		if(bActive)
	   	    pBitmap->LoadBitmap(IDB_LEFTIN);
		else
			pBitmap->LoadBitmap(IDB_LEFTOUT);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(0,23,point.x, point.y, pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		//填充底部框架
		point.x = rtWnd.Width(); 
		point.y = GetSystemMetrics(SM_CYFRAME)+1;
		if(bActive)
	   	    pBitmap->LoadBitmap(IDB_BOTTOMIN);
		else
			pBitmap->LoadBitmap(IDB_BOTTOMOUT);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(0,rtWnd.Height()-point.y,point.x, point.y, pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();		
		
		//填充右侧框架
		point.x = GetSystemMetrics(SM_CXFRAME)+1;
		point.y = rtWnd.Height();
		if(bActive)
	   	    pBitmap->LoadBitmap(IDB_RIGHTIN);
		else
			pBitmap->LoadBitmap(IDB_RIGHTOUT);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtWnd.Width()-point.x,23,point.x, point.y, pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		//重画标题栏程序图标
		m_rtIcon.left = rtTitle.left + 3;
		m_rtIcon.top = GetSystemMetrics(SM_CYFRAME)-2;
		m_rtIcon.right = m_rtIcon.left + 19;
		m_rtIcon.bottom = m_rtIcon.top + 19;
		::DrawIconEx(pDC->m_hDC, m_rtIcon.left, m_rtIcon.top, AfxGetApp()->LoadIcon(IDR_MAINFRAME), 
		  m_rtIcon.Width(), m_rtIcon.Height(), 0, NULL, DI_NORMAL);
		m_rtIcon.OffsetRect(rtWnd.TopLeft()); 

		//重画标题栏程序标题
		int nOldMode = pDC->SetBkMode(TRANSPARENT);
		COLORREF clOldText=pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SelectStockObject(SYSTEM_FIXED_FONT);
		rtTitle.left = rtTitle.left+30; 
		rtTitle.top = GetSystemMetrics(SM_CYFRAME);
		rtTitle.bottom = rtTitle.top + 22;
		CString m_strTitle;
		GetWindowText(m_strTitle);
		m_strTitle=_T("LH-1553B演示程序");
		pDC->DrawText(m_strTitle, &rtTitle, DT_LEFT);
		pDC->SetBkMode(nOldMode);
		pDC->SetTextColor(clOldText);

		//重画关闭按钮
		rtButtons.left = rtTitle.right - 19;
		rtButtons.top = rtTitle.top-2;
		rtButtons.right = rtButtons.left + 19;
		rtButtons.bottom = rtButtons.top + 19;
		pBitmap->LoadBitmap(IDB_CLOSEOUT);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtExit = rtButtons;
		m_rtButtExit.OffsetRect(rtWnd.TopLeft()); 
		pBitmap->DeleteObject();

		//重画最大化/恢复按钮
		rtButtons.right = rtButtons.left;
		rtButtons.left = rtButtons.right - 19;
		if (IsZoomed())
			pBitmap->LoadBitmap(IDB_RESTOREOUT);
		else
			pBitmap->LoadBitmap(IDB_MAXOUT);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMax = rtButtons;
		m_rtButtMax.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();

		//重画最小化按钮
		rtButtons.right = rtButtons.left;
		rtButtons.left = rtButtons.right - 19;
		pBitmap->LoadBitmap(IDB_MINOUT);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtMin = rtButtons;
		m_rtButtMin.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();
	
		//重画帮助按钮
		rtButtons.right = rtButtons.left;
		rtButtons.left = rtButtons.right - 19;
		pBitmap->LoadBitmap(IDB_HELPOUT);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		m_rtButtHelp = rtButtons;
		m_rtButtHelp.OffsetRect(rtWnd.TopLeft());
		pBitmap->DeleteObject();
		
		// 释放资源
		ReleaseDC(pDisplayMemDC);
		ReleaseDC(pDC);
		delete pDisplayMemDC;
		delete pBitmap;
	}
}

//消息处理
LRESULT CMainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT lrst=CFrameWnd::DefWindowProc(message, wParam, lParam);
	
	if (!::IsWindow(m_hWnd))
		return lrst;
	
	if (message==WM_ACTIVATEAPP||message==WM_ACTIVATE||message == WM_SYSCOMMAND||message == WM_MOVE || message == WM_NCPAINT ||message == WM_NCACTIVATE )
	{
		CDC* pWinDC = GetWindowDC();
		if (pWinDC)
			DrawTitleBar(pWinDC); // 当有上述消息时，绘制标题栏
		ReleaseDC(pWinDC);
	}
	return lrst;
}

void CMainFrame::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (nHitTest == HTCAPTION)  //右键单击非客户区中的标题栏区
	{
		CWnd * pWnd = CWnd::FromHandle(m_hWnd);
  	    CMenu SysMenu;
	    SysMenu.Attach( ::GetSystemMenu(m_hWnd,FALSE) );
		SysMenu.TrackPopupMenu( 0, point.x, point.y, pWnd  );		
	    SysMenu.Detach();		
	}
	//CMDIFrameWnd::OnNcLButtonDblClk(nHitTest, point);
}

void CMainFrame::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC = GetWindowDC();
	CDC* pDisplayMemDC=new CDC;
	pDisplayMemDC->CreateCompatibleDC(pDC);
	CBitmap* pBitmap = new CBitmap;
	CBitmap* pOldBitmap;
	CRect rtWnd, rtButton;

	if (pDC)
	{
		// 得到当前窗口区域
		GetWindowRect(&rtWnd);

		// 重绘鼠标移动到上面时的关闭按钮
		if (m_rtButtExit.PtInRect(point))
			pBitmap->LoadBitmap(IDB_CLOSEIN);
		else
			pBitmap->LoadBitmap(IDB_CLOSEOUT);
		rtButton = m_rtButtExit;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		//最大化/恢复按钮
		if (m_rtButtMax.PtInRect(point))
		{
			if (IsZoomed())
				pBitmap->LoadBitmap(IDB_RESTOREIN);
			else
				pBitmap->LoadBitmap(IDB_MAXIN);
		}
		else
		{
			if (IsZoomed())
				pBitmap->LoadBitmap(IDB_RESTOREOUT);
			else
				pBitmap->LoadBitmap(IDB_MAXOUT);
		}
		rtButton = m_rtButtMax;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		//最小化按钮
		if (m_rtButtMin.PtInRect(point))
			pBitmap->LoadBitmap(IDB_MININ);
		else
			pBitmap->LoadBitmap(IDB_MINOUT);
		rtButton = m_rtButtMin;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		//帮助按钮
		if (m_rtButtHelp.PtInRect(point))
			pBitmap->LoadBitmap(IDB_HELPIN);
		else
			pBitmap->LoadBitmap(IDB_HELPOUT);
		rtButton = m_rtButtHelp;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
	}
	// 释放资源
	ReleaseDC(pDisplayMemDC);
	ReleaseDC(pDC);
	delete pDisplayMemDC;
	delete pBitmap;
    
	// 系统进一步处理WM_NCMOUSEMOVE消息，
	CMDIFrameWnd::OnNcMouseMove(nHitTest, point);
}

void CMainFrame::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		// 得到当前设备环境
	CDC* pDC = GetWindowDC();
	CDC* pDisplayMemDC=new CDC;
	pDisplayMemDC->CreateCompatibleDC(pDC);
	CBitmap* pBitmap = new CBitmap;
	CBitmap* pOldBitmap;
	CRect rtWnd, rtButton;
	BOOL bCanDraw=FALSE;   // 是否可以重绘按钮
	if (pDC)
	{
		GetWindowRect(&rtWnd);
	    bCanDraw=TRUE;
	}
	//检测各按钮是否被按下
	if (m_rtIcon.PtInRect(point))            // 程序图标被按下
	{
		AfxMessageBox("1553配置");
			// 释放资源
		ReleaseDC(pDisplayMemDC);
		ReleaseDC(pDC);

		delete pDisplayMemDC;
		delete pBitmap;
	}
	else if (m_rtButtHelp.PtInRect(point))   // 帮助按钮被按下
	{		
		if (bCanDraw)
		{
			pBitmap->LoadBitmap(IDB_HELPDOWN);
		    rtButton = m_rtButtHelp;
			rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
			pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
			pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
			pDisplayMemDC->SelectObject(pOldBitmap);
		    pBitmap->DeleteObject();
		}
			// 释放资源
		ReleaseDC(pDisplayMemDC);
		ReleaseDC(pDC);

		delete pDisplayMemDC;
		delete pBitmap;
		SendMessage(WM_HELP);	
	}
	else if (m_rtButtExit.PtInRect(point))   // 关闭按钮被按下
	{		
		if (bCanDraw)
		{
			pBitmap->LoadBitmap(IDB_CLOSEDOWN);
		    rtButton = m_rtButtExit;
		    rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		    pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
			pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
			pDisplayMemDC->SelectObject(pOldBitmap);
		    pBitmap->DeleteObject();

				// 释放资源
			ReleaseDC(pDisplayMemDC);
			ReleaseDC(pDC);

			delete pDisplayMemDC;
			delete pBitmap;
			SendMessage(WM_CLOSE);
		}		
	}
	else if (m_rtButtMin.PtInRect(point))    // 最小化按钮被按下
	{
		
		if (bCanDraw)
		{
			pBitmap->LoadBitmap(IDB_MINDOWN);
		    rtButton = m_rtButtMin;
			rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
			pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
			pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
			pDisplayMemDC->SelectObject(pOldBitmap);
		    pBitmap->DeleteObject();
		}
			// 释放资源
		ReleaseDC(pDisplayMemDC);
		ReleaseDC(pDC);

		delete pDisplayMemDC;
		delete pBitmap;
	    SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y));
	}
	else if (m_rtButtMax.PtInRect(point))    // 最大化/恢复按钮被按下
	{
		DWORD dwMsg;
		if (IsZoomed())
		{			
		    if (bCanDraw)
			    pBitmap->LoadBitmap(IDB_RESTOREDOWN);			
			dwMsg=SC_RESTORE;			
		}
		else
		{			
		    if (bCanDraw)
			    pBitmap->LoadBitmap(IDB_MAXDOWN);		        

			dwMsg=SC_MAXIMIZE;
		}
		rtButton = m_rtButtMax;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

			// 释放资源
		ReleaseDC(pDisplayMemDC);
		ReleaseDC(pDC);

		delete pDisplayMemDC;
		delete pBitmap;
		SendMessage(WM_SYSCOMMAND,dwMsg,MAKELPARAM(point.x, point.y));		 
	}
	else if (!IsZoomed())                   
		Default();
	else if (nHitTest&HTMENU)
		Default();

	//CMDIFrameWnd::OnNcLButtonUp(nHitTest, point);
}*//*
void CMainFrame::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		// 得到当前设备环境
	CDC* pDC = GetWindowDC();
	CDC* pDisplayMemDC=new CDC;
	pDisplayMemDC->CreateCompatibleDC(pDC);
	CBitmap* pBitmap = new CBitmap;
	CBitmap* pOldBitmap;
	CRect rtWnd, rtButton;
	BOOL bCanDraw=FALSE;   // 是否可以重绘按钮
	if (pDC)
	{
		GetWindowRect(&rtWnd);
	    bCanDraw=TRUE;
	}
	//检测各按钮是否被按下
	if (m_rtIcon.PtInRect(point))            // 程序图标被按下
	{
		//AfxMessageBox("1553配置");
			// 释放资源
		ReleaseDC(pDisplayMemDC);
		ReleaseDC(pDC);

		delete pDisplayMemDC;
		delete pBitmap;
	}
	else if (m_rtButtHelp.PtInRect(point))   // 帮助按钮被按下
	{		
		if (bCanDraw)
		{
			pBitmap->LoadBitmap(IDB_HELPDOWN);
		    rtButton = m_rtButtHelp;
			rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
			pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
			pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
			pDisplayMemDC->SelectObject(pOldBitmap);
		    pBitmap->DeleteObject();
		}
			// 释放资源
		ReleaseDC(pDisplayMemDC);
		ReleaseDC(pDC);

		delete pDisplayMemDC;
		delete pBitmap;
		//SendMessage(WM_HELP);	
	}
	else if (m_rtButtExit.PtInRect(point))   // 关闭按钮被按下
	{		
		if (bCanDraw)
		{
			pBitmap->LoadBitmap(IDB_CLOSEDOWN);
		    rtButton = m_rtButtExit;
		    rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		    pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
			pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
			pDisplayMemDC->SelectObject(pOldBitmap);
		    pBitmap->DeleteObject();

				// 释放资源
			ReleaseDC(pDisplayMemDC);
			ReleaseDC(pDC);

			delete pDisplayMemDC;
			delete pBitmap;
			//SendMessage(WM_CLOSE);
		}		
	}
	else if (m_rtButtMin.PtInRect(point))    // 最小化按钮被按下
	{
		
		if (bCanDraw)
		{
			pBitmap->LoadBitmap(IDB_MINDOWN);
		    rtButton = m_rtButtMin;
			rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
			pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
			pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
			pDisplayMemDC->SelectObject(pOldBitmap);
		    pBitmap->DeleteObject();
		}
			// 释放资源
		ReleaseDC(pDisplayMemDC);
		ReleaseDC(pDC);

		delete pDisplayMemDC;
		delete pBitmap;
	    //SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y));
	}
	else if (m_rtButtMax.PtInRect(point))    // 最大化/恢复按钮被按下
	{
		DWORD dwMsg;
		if (IsZoomed())
		{			
		    if (bCanDraw)
			    pBitmap->LoadBitmap(IDB_RESTOREDOWN);			
			dwMsg=SC_RESTORE;			
		}
		else
		{			
		    if (bCanDraw)
			    pBitmap->LoadBitmap(IDB_MAXDOWN);		        

			dwMsg=SC_MAXIMIZE;
		}
		rtButton = m_rtButtMax;
		rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap=(CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

			// 释放资源
		ReleaseDC(pDisplayMemDC);
		ReleaseDC(pDC);

		delete pDisplayMemDC;
		delete pBitmap;
		//SendMessage(WM_SYSCOMMAND,dwMsg,MAKELPARAM(point.x, point.y));		 
	}
	//else if (!IsZoomed())                   
	//	Default();
	else if (nHitTest&HTMENU)
		Default();


  
	// 若是关闭按钮被按下，WM_CLOSE只有在释放资源后才能被发送给主程序
	//if (m_rtButtExit.PtInRect(point))
	    //SendMessage(WM_CLOSE);

	//CMDIFrameWnd::OnNcLButtonDown(nHitTest, point);
}

void CMainFrame::OnNcRButtonDown(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (nHitTest == HTCAPTION)  //右键单击非客户区中的标题栏区
	{
		CWnd * pWnd = CWnd::FromHandle(m_hWnd);
  	    CMenu SysMenu;
	    SysMenu.Attach( ::GetSystemMenu(m_hWnd,FALSE) );
		SysMenu.TrackPopupMenu( 0, point.x, point.y, pWnd  );		
	    SysMenu.Detach();		
	}
	//CMDIFrameWnd::OnNcRButtonDown(nHitTest, point);
}
*/
void CMainFrame::InsertBCMessage()
{
	CMessageSet MeSetDlg;
	MeSetDlg.IniType = 0;//
	MeSetDlg.NowAddMessageTyep = NowAddMessageType;
	if((NowAddMessageType>2)||(NowAddMessageType<1))	MeSetDlg.NowAddMessageTyep = 1;
	if(MeSetDlg.DoModal()==IDOK)
	{

	}

}
void CMainFrame::InsertTimerMessage()
{
	NowAddMessageType = 1;
	CMessageSet MeSetDlg;
	MeSetDlg.IniType = 0;//
	MeSetDlg.NowAddMessageTyep = NowAddMessageType;
	if((NowAddMessageType>2)||(NowAddMessageType<1))	MeSetDlg.NowAddMessageTyep = 1;
	if(MeSetDlg.DoModal()==IDOK)
	{

	}
}
void CMainFrame::InsertNOTimerMessage()
{
	NowAddMessageType = 2;
	CMessageSet MeSetDlg;
	MeSetDlg.IniType = 0;//
	MeSetDlg.NowAddMessageTyep = NowAddMessageType;
	if((NowAddMessageType>2)||(NowAddMessageType<1))	MeSetDlg.NowAddMessageTyep = 1;
	if(MeSetDlg.DoModal()==IDOK)
	{

	}
}
void CMainFrame::EnableMessge()
{
	if(NowAddMessageType==1)//周期
	{
		if(NowdeletID>=0)//
		{
			MessageData1553[m_now_SelectChannel].EnableMessge(1,NowdeletID);
			BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(NowdeletID,7,"激活");
			TabProjDlg.ProjectDlg[m_now_SelectChannel].EnableMessage(1,NowdeletID);
		}
	}
	else//非周期
	{
		if(NowdeletID>=0)//
		{
			MessageData1553[m_now_SelectChannel].EnableMessge(2,NowdeletID);
			BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(NowdeletID,7,"激活");
			TabProjDlg.ProjectDlg[m_now_SelectChannel].EnableMessage(2,NowdeletID);
		}

	}
}
void CMainFrame::DisableMessge()
{
	if(NowAddMessageType==1)//周期
	{
		if(NowdeletID>=0)//
		{
			MessageData1553[m_now_SelectChannel].DisableMessge(1,NowdeletID);
			BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(NowdeletID,7,"无效");
			TabProjDlg.ProjectDlg[m_now_SelectChannel].DisableMessage(1,NowdeletID);
		}
	}
	else//非周期
	{
			MessageData1553[m_now_SelectChannel].DisableMessge(2,NowdeletID);
			BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(NowdeletID,7,"无效");
			TabProjDlg.ProjectDlg[m_now_SelectChannel].DisableMessage(2,NowdeletID);
	}
}
void CMainFrame::MoveBCMessage(int MessageID)
{
	CString inSertName;
	int MovetoId;
	int i;
	if(NowAddMessageType==1)//周期移动到非周期
	{
		if(NowdeletID>=0)//找到要移动的BC消息ID
		{
			MovetoId = MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2;
			
			inSertName = TabProjDlg.ProjectDlg[m_now_SelectChannel].m_Tree.GetItemText(TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItem[NowdeletID]);
			TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(11,inSertName,MovetoId);
			BCView[m_now_SelectChannel].m_BC_MesList2.InsertItem(MovetoId,"");
			
			for(i=1;i<40;i++)
			{
				inSertName = BCView[m_now_SelectChannel].m_BC_MesList.GetItemText(NowdeletID,i);
				
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(MovetoId,i,inSertName);
			}
			inSertName.Format("%2d",MovetoId);
			BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(MovetoId,0,inSertName);

			MessageData1553[m_now_SelectChannel].bc_msg_data_2[MovetoId] = MessageData1553[m_now_SelectChannel].bc_msg_data[NowdeletID];
			MessageData1553[m_now_SelectChannel].MessageName_2[MovetoId] = MessageData1553[m_now_SelectChannel].MessageName[NowdeletID];
			MessageData1553[m_now_SelectChannel].MessageTyep_2[MovetoId] = MessageData1553[m_now_SelectChannel].MessageTyep[NowdeletID];
			MessageData1553[m_now_SelectChannel].chanA_B_2[MovetoId] = MessageData1553[m_now_SelectChannel].chanA_B[NowdeletID];
			MessageData1553[m_now_SelectChannel].BCNoTiemMessageEnabel[MovetoId] = MessageData1553[m_now_SelectChannel].BCMessageEnabel[NowdeletID];
			BCView[m_now_SelectChannel].m_BC_MesList2.AddNewItem(MovetoId) ;
			BCView[m_now_SelectChannel].m_BC_MesList2.SetCheckBoxVal(MovetoId,MessageData1553[m_now_SelectChannel].BCNoTiemMessageEnabel[MovetoId]);
			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2=MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2+1;

			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount=MessageData1553[m_now_SelectChannel].BC_MessageMaxCount-1;
			TabProjDlg.ProjectDlg[m_now_SelectChannel].m_Tree.DeleteItem(TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItem[NowdeletID]);
			BCView[m_now_SelectChannel].m_BC_MesList.DeleteItem(NowdeletID);
			BCView[m_now_SelectChannel].m_BC_MesList.DeletItemCheckBox(NowdeletID);

			for(i=NowdeletID;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;i++)
			{
				MessageData1553[m_now_SelectChannel].bc_msg_data[i]=MessageData1553[m_now_SelectChannel].bc_msg_data[i+1];
				TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItem[i]=TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItem[i+1];
				inSertName.Format("%2d",i);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,0,inSertName);
			}
			//MessageData1553[m_now_SelectChannel].SetMessageTeam();//重新组织消息
		}
	}
	if(NowAddMessageType==2)//非周期移动到周期
	{
		if(NowdeletID>=0)//找到要移动的BC消息ID
		{
			MovetoId = MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;
			
			inSertName = TabProjDlg.ProjectDlg[m_now_SelectChannel].m_Tree.GetItemText(TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItemNo[NowdeletID]);
			TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(10,inSertName,MovetoId);
			BCView[m_now_SelectChannel].m_BC_MesList.InsertItem(MovetoId,"");
			for(i=1;i<40;i++)
			{
				inSertName = BCView[m_now_SelectChannel].m_BC_MesList2.GetItemText(NowdeletID,i);
				
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(MovetoId,i,inSertName);
			}
			inSertName.Format("%2d",MovetoId);
			BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(MovetoId,0,inSertName);

			MessageData1553[m_now_SelectChannel].bc_msg_data[MovetoId] = MessageData1553[m_now_SelectChannel].bc_msg_data_2[NowdeletID];
			MessageData1553[m_now_SelectChannel].MessageName[MovetoId] = MessageData1553[m_now_SelectChannel].MessageName_2[NowdeletID];
			MessageData1553[m_now_SelectChannel].MessageTyep[MovetoId] = MessageData1553[m_now_SelectChannel].MessageTyep_2[NowdeletID];
			MessageData1553[m_now_SelectChannel].chanA_B[MovetoId] = MessageData1553[m_now_SelectChannel].chanA_B_2[NowdeletID];
			MessageData1553[m_now_SelectChannel].BCMessageEnabel[MovetoId] = MessageData1553[m_now_SelectChannel].BCNoTiemMessageEnabel[NowdeletID];
			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount=MessageData1553[m_now_SelectChannel].BC_MessageMaxCount+1;
			BCView[m_now_SelectChannel].m_BC_MesList.AddNewItem(MovetoId) ;
			BCView[m_now_SelectChannel].m_BC_MesList.SetCheckBoxVal(MovetoId,MessageData1553[m_now_SelectChannel].BCMessageEnabel[MovetoId]);
			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2=MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2-1;

			TabProjDlg.ProjectDlg[m_now_SelectChannel].m_Tree.DeleteItem(TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItemNo[NowdeletID]);
			BCView[m_now_SelectChannel].m_BC_MesList2.DeleteItem(NowdeletID);
			BCView[m_now_SelectChannel].m_BC_MesList2.DeletItemCheckBox(NowdeletID);

			for(i=NowdeletID;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2;i++)
			{
				MessageData1553[m_now_SelectChannel].bc_msg_data_2[i]=MessageData1553[m_now_SelectChannel].bc_msg_data_2[i+1];
				TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItemNo[i]=TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItemNo[i+1];
				inSertName.Format("%2d",i);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,0,inSertName);
			}
			//MessageData1553[m_now_SelectChannel].SetMessageTeam();//重新组织消息
		}
	}
	TabProjDlg.ProjectDlg[m_now_SelectChannel].Invalidate(true);
}
void CMainFrame::DeleteBCMessage(int MessageID)
{
	bool findFlag;
	CString inSertName;
	int i;

	findFlag=false;
	HTREEITEM SeleItem=TabProjDlg.ProjectDlg[m_now_SelectChannel].m_Tree.GetNextItem(TVI_ROOT,TVGN_CARET);

	/*
	for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;i++)
	{
		if(ProjectDlg.BCItem[i] = SeleItem)
		{
			findFlag = true;
			deletID=i;
			break;
			
		}
	}
	*/
	if(NowAddMessageType==1)
	{
		if(NowdeletID>=0)//找到要删除的BC消息ID
		{
			
			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount=MessageData1553[m_now_SelectChannel].BC_MessageMaxCount-1;
			TabProjDlg.ProjectDlg[m_now_SelectChannel].m_Tree.DeleteItem(TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItem[NowdeletID]);
			BCView[m_now_SelectChannel].m_BC_MesList.DeleteItem(NowdeletID);
			BCView[m_now_SelectChannel].m_BC_MesList.DeletItemCheckBox(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount);

			for(i=NowdeletID;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;i++)
			{
				inSertName.Format("%2d",i);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,0,inSertName);
				MessageData1553[m_now_SelectChannel].bc_msg_data[i]=MessageData1553[m_now_SelectChannel].bc_msg_data[i+1];
				TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItem[i]=TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItem[i+1];
				MessageData1553[m_now_SelectChannel].BCMessageEnabel[i] = MessageData1553[m_now_SelectChannel].BCMessageEnabel[i+1];
				if(MessageData1553[m_now_SelectChannel].BCMessageEnabel[i]) 
				{
					BCView[m_now_SelectChannel].m_BC_MesList.CheckBox[i].SetCheck(true);
					BCView[m_now_SelectChannel].m_BC_MesList.CheckBox[i].SetWindowText("激活状态");
				}
				else
				{
					BCView[m_now_SelectChannel].m_BC_MesList.CheckBox[i].SetCheck(false);
					BCView[m_now_SelectChannel].m_BC_MesList.CheckBox[i].SetWindowText("无效状态");
				}
			}
			//MessageData1553[m_now_SelectChannel].SetMessageTeam();//重新组织消息
		}
	}
	else if(NowAddMessageType==2)
	{
		if(NowdeletID>=0)//找到要删除的BC消息ID
		{
			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2=MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2-1;
			TabProjDlg.ProjectDlg[m_now_SelectChannel].m_Tree.DeleteItem(TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItemNo[NowdeletID]);
			BCView[m_now_SelectChannel].m_BC_MesList2.DeleteItem(NowdeletID);
			BCView[m_now_SelectChannel].m_BC_MesList2.DeletItemCheckBox(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2);


			for(i=NowdeletID;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2;i++)
			{
				inSertName.Format("%2d",i);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,0,inSertName);
				MessageData1553[m_now_SelectChannel].bc_msg_data_2[i]=MessageData1553[m_now_SelectChannel].bc_msg_data_2[i+1];
				TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItemNo[i]=TabProjDlg.ProjectDlg[m_now_SelectChannel].BCItemNo[i+1];
				MessageData1553[m_now_SelectChannel].BCNoTiemMessageEnabel[i] = MessageData1553[m_now_SelectChannel].BCNoTiemMessageEnabel[i+1];

				if(MessageData1553[m_now_SelectChannel].BCNoTiemMessageEnabel[i]) 
				{
					BCView[m_now_SelectChannel].m_BC_MesList2.CheckBox[i].SetCheck(true);
					BCView[m_now_SelectChannel].m_BC_MesList2.CheckBox[i].SetWindowText("激活状态");
				}
				else
				{
					BCView[m_now_SelectChannel].m_BC_MesList2.CheckBox[i].SetCheck(false);
					BCView[m_now_SelectChannel].m_BC_MesList2.CheckBox[i].SetWindowText("无效状态");
				}
			}
			//MessageData1553[m_now_SelectChannel].SetMessageTeam();//重新组织消息
		}
	}

}
void CMainFrame::RunBC()
{
	if(MessageData1553[m_now_SelectChannel].RunBC()==1)
		TabProjDlg.ProjectDlg[m_now_SelectChannel].m_Tree.BCRun_flag=true;
}

void CMainFrame::StopBC()
{
	MessageData1553[m_now_SelectChannel].StopBC();
	TabProjDlg.ProjectDlg[m_now_SelectChannel].m_Tree.BCRun_flag=false;
}
void CMainFrame::SetRTViewData(int rtadress,int subadress,API_RT_MBUF_WRITE data,bool flag)
{
	RTView[m_now_SelectChannel][rtadress].SetRTViewData(rtadress,subadress,data,flag);
	//RTView[m_now_SelectChannel][rtadress].ShowWindow(SW_SHOWNA);
}
void CMainFrame::ReadMessageTeam()
{
	CString FileName,FilePathName,writestr;
	CString inSertName;
	char writeVale[20];
	int i,j,k;
	bool ADDflag;

	ADDflag = false;
	if(NowAddMessageType==1)
	{
		if(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount>0)
		{
			if(MessageBox("是否替换当前周期消息组","提示",MB_YESNO)==IDYES)
				ADDflag = true;
			else ADDflag = false;
		}
		else ADDflag = true;
	}
	else 
	{
		if(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2>0)
		{
			if(MessageBox("是否替换当前非周期消息组","提示",MB_YESNO)==IDYES)
				ADDflag = true;
			else ADDflag = false;
		}
		else ADDflag = true;
	}

	if(ADDflag)
	{
		CFileDialog FileSave( true,NULL,"*.bc",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
		if(FileSave.DoModal()==IDOK )
		{
			
			FileName=FileSave.GetPathName();
			if(NowAddMessageType==1)
			{
				BCView[m_now_SelectChannel].m_BC_MesList.DeleteAllItemCheckBox();
				BCView[m_now_SelectChannel].m_BC_MesList.DeleteAllItems();
				TabProjDlg.ProjectDlg[m_now_SelectChannel].InitTimeSet();

				GetPrivateProfileString("sectiontype_BC","AllBC_Count","",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].BC_MessageMaxCount=atoi(writeVale);

				for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;i++)
				{
					MessageData1553[m_now_SelectChannel].BCMessageEnabel[i] = true;
					writestr.Format("BC_retryflag%d",i);
					GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag[i], sizeof(bool),FileName);
					
					writestr.Format("BC%d",i);
					GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data[i], sizeof(API_BC_MBUF),FileName);
					
					writestr.Format("BC_type%d",i);
					GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
					MessageData1553[m_now_SelectChannel].MessageTyep[i]=atoi(writeVale);

					writestr.Format("BC_Name%d",i);
					GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
					MessageData1553[m_now_SelectChannel].MessageName[i].Format("%s",writeVale);

					writestr.Format("BC_Channel%d",i);
					GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
					MessageData1553[m_now_SelectChannel].chanA_B[i]=atoi(writeVale);

					if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==0)
						inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"BC->RT",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
					else if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==1)
						inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"RT->BC",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
					else if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2)
						inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"RT->RT",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
				
					else if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==3)
						inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"MODE",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
				

					TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(10,inSertName,i);

					//////////显示到消息BCVIEW中/////
					BCView[m_now_SelectChannel].m_BC_MesList.InsertItem(i,0);
					BCView[m_now_SelectChannel].m_BC_MesList.AddNewItem(i);

					inSertName.Format("%2d",i);

					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,0,inSertName);
					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,1,MessageData1553[m_now_SelectChannel].MessageName[i]);
					if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==0) inSertName.Format("%s","BC->RT");
					if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==1) inSertName.Format("%s","RT->BC");
					if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2) inSertName.Format("%s","RT->RT");
					if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==3) inSertName.Format("%s","MODE");
 					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,2,inSertName);

					if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command2.rtaddr);
					else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr);
					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,3,inSertName);

					if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command2.subaddr);
					else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,4,inSertName);

					if(MessageData1553[m_now_SelectChannel].chanA_B[i]==1)
						inSertName.Format("通道%S","A");
					else inSertName.Format("通道%S","B");
					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,5,inSertName);

					if(MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.wcount==0)
						inSertName.Format("%2d",32);	
					else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.wcount);
					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,6,inSertName);
					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,7,"激活");

					CString str;
					if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==0)
					for(j=0;j<32;j++)
					{
						str.Format("0X:%4X",MessageData1553[m_now_SelectChannel].bc_msg_data[i].data[0][j]);
						for(k=3;k<7;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,8+j,str);
					}
					/////////////////////////////////
					//MessageData1553[m_now_SelectChannel].SetMessageTeam();//组织消息
				}
			}
			else//读到非周期消息
			{

				BCView[m_now_SelectChannel].m_BC_MesList2.DeleteAllItemCheckBox();
				BCView[m_now_SelectChannel].m_BC_MesList2.DeleteAllItems();
				TabProjDlg.ProjectDlg[m_now_SelectChannel].InitNoTimeSet();

				GetPrivateProfileString("sectiontype_BC","AllBC_Count","",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2=atoi(writeVale);

				for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2;i++)
				{
					MessageData1553[m_now_SelectChannel].BCNoTiemMessageEnabel[i] = true;

					writestr.Format("BC_retryflag%d",i);
					GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag_2[i], sizeof(bool),FileName);
					

					writestr.Format("BC%d",i);
					GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data_2[i], sizeof(API_BC_MBUF),FileName);
					
					writestr.Format("BC_type%d",i);
					GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
					MessageData1553[m_now_SelectChannel].MessageTyep_2[i]=atoi(writeVale);

					writestr.Format("BC_Name%d",i);
					GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
					MessageData1553[m_now_SelectChannel].MessageName_2[i].Format("%s",writeVale);

					writestr.Format("BC_Channel%d",i);
					GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
					MessageData1553[m_now_SelectChannel].chanA_B_2[i]=atoi(writeVale);


					if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==0)
						inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"BC->RT",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
					else if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==1)
						inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"RT->BC",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
					else if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2)
						inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"RT->RT",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
				
					else if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==3)
						inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"MODE",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
				

					TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(11,inSertName,i);

					//////////显示到消息BCVIEW中/////
					BCView[m_now_SelectChannel].m_BC_MesList2.InsertItem(i,0);
					BCView[m_now_SelectChannel].m_BC_MesList2.AddNewItem(i);


					inSertName.Format("%2d",i);

					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,0,inSertName);
					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,1,MessageData1553[m_now_SelectChannel].MessageName_2[i]);
					if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==0) inSertName.Format("%s","BC->RT");
					if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==1) inSertName.Format("%s","RT->BC");
					if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2) inSertName.Format("%s","RT->RT");
					if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==3) inSertName.Format("%s","MODE");
 					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,2,inSertName);

					if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command2.rtaddr);
					else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr);
					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,3,inSertName);

					if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command2.subaddr);
					else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,4,inSertName);

					if(MessageData1553[m_now_SelectChannel].chanA_B_2[i]==1)
						inSertName.Format("通道%S","A");
					else inSertName.Format("通道%S","B");

					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,5,inSertName);
					
					if(MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.wcount==0)
						inSertName.Format("%2d",32);	
					else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.wcount);
					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,6,inSertName);
					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,7,"激活");
					

					CString str;
					if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==0)
					for(j=0;j<32;j++)
					{
						str.Format("0X:%4X",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].data[0][j]);
						for(k=3;k<7;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,8+j,str);
					}
					/////////////////////////////////
					//MessageData1553[m_now_SelectChannel].SetMessageTeam();//组织消息
				}

			}
		}
	}

}
void CMainFrame::SaveMessageTeam()
{
	CString FileName,FilePathName,writeVale,writestr;
	int i;
	int RT_Count;

	if(NowAddMessageType==1)
	{
		if(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount>0)
		{
			CFileDialog FileSave( false,NULL,"*.bc",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
			if(FileSave.DoModal()==IDOK )
			{
				//FilePath=FileSave.GetFolderPath();
				FileName=FileSave.GetPathName();
				CFileFind ff;
				if(ff.FindFile(FileName,0))
				{
					::DeleteFile(FileName);
				}

				///存BC周期数据
				writestr.Format("%2d",MessageData1553[m_now_SelectChannel].BC_MessageMaxCount);
				WritePrivateProfileString("sectiontype_BC","AllBC_Count",writestr,FileName);

				writestr.Format("%4d",MessageData1553[m_now_SelectChannel].FrameTimer);
				WritePrivateProfileString("sectiontype_BC","BC_FrameTimer",writestr,FileName);

				for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;i++)
				{
					writestr.Format("BC_type%d",i);
					writeVale.Format("%d",MessageData1553[m_now_SelectChannel].MessageTyep[i]);
					WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
					writestr.Format("BC_Name%d",i);
					writeVale.Format("%s",MessageData1553[m_now_SelectChannel].MessageName[i]);
					WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
					writestr.Format("BC_Channel%d",i);
					writeVale.Format("%d",MessageData1553[m_now_SelectChannel].chanA_B[i]);
					WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
					
					writestr.Format("BC%d",i);
					WritePrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data[i], sizeof(API_BC_MBUF),FileName);

					writestr.Format("BC_retryflag%d",i);
					WritePrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag[i], sizeof(bool) ,FileName);
				
				
				}
			}
		}
		else
		{
			MessageBox("没有定义消息，不能保存","提示");
		}
	}
	else//保存飞周期消息
	{
		if(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2>0)
		{
			CFileDialog FileSave( false,NULL,"*.bc",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
			if(FileSave.DoModal()==IDOK )
			{
				//FilePath=FileSave.GetFolderPath();
				FileName=FileSave.GetPathName();
				CFileFind ff;
				if(ff.FindFile(FileName,0))
				{
					::DeleteFile(FileName);
				}


				writestr.Format("%2d",MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2);
				WritePrivateProfileString("sectiontype_BC","AllBC_Count",writestr,FileName);

				for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2;i++)
				{
					writestr.Format("BC_type%d",i);
					writeVale.Format("%d",MessageData1553[m_now_SelectChannel].MessageTyep_2[i]);
					WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
					writestr.Format("BC_Name%d",i);
					writeVale.Format("%s",MessageData1553[m_now_SelectChannel].MessageName_2[i]);
					WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
					writestr.Format("BC_Channel%d",i);
					writeVale.Format("%d",MessageData1553[m_now_SelectChannel].chanA_B_2[i]);
					WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
					
					writestr.Format("BC%d",i);
					WritePrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data_2[i], sizeof(API_BC_MBUF),FileName);
				
					writestr.Format("BC_retryflag%d",i);
					WritePrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag_2[i], sizeof(bool),FileName);
				
				}
			}
		}
		else
		{
			MessageBox("没有定义消息，不能保存","提示");
		}
	}
}
void CMainFrame::InsertRTData()
{
	/*
	CRTDataSet RTSetDlg;
	RTSetDlg.IniType = 0;//
	if(RTSetDlg.DoModal()==IDOK)
	{

	}
	*/
	CRect rect,rect2,newrect;


	BCView[m_now_SelectChannel].GetWindowRect(rect);
	//RTSelectDlg.GetWindowRect(rect2);
	newrect.left = rect.left;
	newrect.top = rect.top;
	newrect.right = rect.left+rect2.right-rect2.left;
	newrect.bottom = rect.top+rect2.bottom-rect2.top;

	//RTSelectDlg.SetWindowPos(this,rect.left,rect.top,410,279,true);	
	CRTDataSet RTSelectDlg;
	RTSelectDlg.IniType = 0;
	if(RTSelectDlg.DoModal()==IDOK)
	{
/*		RTSelectDlg.GetWindowRect(rect2);
		BCView[m_now_SelectChannel].GetWindowRect(rect);
		RTSelectDlg.MoveWindow(rect.left,rect.top,rect2.right-rect2.left,rect2.bottom - rect2.top,false);
*/	}
}
BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F1)
	{
		RunBC();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F2)
	{
		StopBC();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F3)
	{
		StepRun();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F4)
	{
		RunRT();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F5)
	{
		StopRT();
	}

	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::RunRT()
{
	MessageData1553[m_now_SelectChannel].RunRT();
}

void CMainFrame::StopRT()
{
	MessageData1553[m_now_SelectChannel].StopRT();
}

void CMainFrame::RT_Enable()
{
	MessageData1553[m_now_SelectChannel].EnableRT(NowSelectRT);
	MessageData1553[m_now_SelectChannel].RT_Enable[NowSelectRT] = true;
	TabProjDlg.ProjectDlg[m_now_SelectChannel].SetRTIcon(NowSelectRT,true);
}

void CMainFrame::RT_Disable()
{
	MessageData1553[m_now_SelectChannel].DisableRT(NowSelectRT);
	MessageData1553[m_now_SelectChannel].RT_Enable[NowSelectRT] = false;
	TabProjDlg.ProjectDlg[m_now_SelectChannel].SetRTIcon(NowSelectRT,false);
}
bool CMainFrame::CheckFiltration(API_BM_MBUF messge)
{
	int i;
	short tempVal;
	for(i=0;i<MessageData1553[m_now_SelectChannel].NoShow_Stutas[256];i++)
	{
		memcpy(&tempVal,&messge.status1,sizeof(short));
		if(tempVal==MessageData1553[m_now_SelectChannel].NoShow_Stutas[i])
			return false;
	}
	if(messge.status_c1==5)
	{
		for(i=0;i<MessageData1553[m_now_SelectChannel].NoShow_Vector[256];i++)
		{
			if(messge.value[0]==MessageData1553[m_now_SelectChannel].NoShow_Vector[i])
				return false;
		}
	}

	return true;
}


void CMainFrame::ShowMessageData(int m_channelshow)
{
	int i,j,k,NowCount,ShowCount,InsertCount;
	CString str;
	WORD valefef;

	BMView[m_channelshow].m_GetMessagelist.LockWindowUpdate();
	if(GetData.MessageUnmber>0)
	{
		if(MessageData1553[m_channelshow].ShowType==1)
		{
			
			for(i=0;i<GetData.MessageUnmber;i++)  
			{ 
				if((CheckFiltration(GetData.Messagedata[i]))&&((GetData.flag[i]==true)&&(BMView[m_channelshow].Exce_Flag[GetData.Messagedata[i].command1.rtaddr][GetData.Messagedata[i].command1.subaddr])))//过滤条件
				{
					  //BC->RT
					
						//BMView[m_channelshow].m_GetMessagelist.InsertItem(0,0);
					InsertCount = GetData.ShowItem[i];
					if(InsertCount+1>BMView[m_channelshow].m_GetMessagelist.GetItemCount())
						BMView[m_channelshow].m_GetMessagelist.InsertItem(InsertCount,0);

					{
						str.Format("%2d",GetData.Messagedata[i].messno);
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,1,str);

						if(GetData.Messagedata[i].status_c1==1)
							str.Format("%s","BC->RT");
						else if(GetData.Messagedata[i].status_c1==2)
							str.Format("%s","RT->BC");
						else if(GetData.Messagedata[i].status_c1==3)
							str.Format("%s","RT->RT");
						else str.Format("%s","MODE");

						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,2,str);

						if((GetData.Messagedata[i].status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((GetData.Messagedata[i].status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,3,str);


						str.Format("%d",GetData.Messagedata[i].response1.time);
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,4,str);

						str =   MessageData1553[m_channelshow].InttoTimerStr(GetData.Messagedata[i].time.microseconds-MessageData1553[m_channelshow].firstTime);
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,5,str);

						if(GetData.Messagedata[i].status_c1==3)//RT->RT 
						{
							str.Format("%2d<-%2d",GetData.Messagedata[i].command1.rtaddr,GetData.Messagedata[i].command2.rtaddr);
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,6,str);

							str.Format("%2d<-%2d",GetData.Messagedata[i].command1.subaddr,GetData.Messagedata[i].command2.subaddr);
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,7,str);
						}
						else
						{
							str.Format("%2d",GetData.Messagedata[i].command1.rtaddr);
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,6,str);

							str.Format("%2d",GetData.Messagedata[i].command1.subaddr);
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,7,str);
						}

								
						if((GetData.Messagedata[i].status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((GetData.Messagedata[i].status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,8,str);

						if(GetData.Messagedata[i].status_c1==3)//RT->RT 
						{

							if(GetData.Messagedata[i].command2.wcount==0) ShowCount = 32;
							else  ShowCount= GetData.Messagedata[i].command2.wcount;
						}
						else
						{
							if(GetData.Messagedata[i].command1.wcount==0) ShowCount = 32;
							else  ShowCount= GetData.Messagedata[i].command1.wcount;
						}

						str.Format("%2d",ShowCount);
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,9,str);

						//memcpy(&valefef,&GetData.Messagedata[i].status1,sizeof(short));
						//valefef = MessageData1553[m_channelshow].Stutas1553ToInt(GetData.Messagedata[i].status1);
						memcpy(&valefef,&GetData.Messagedata[i].status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}

						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,10,str);

						if(GetData.Messagedata[i].status_c1>3) ShowCount = 32;
						for(j=0;j<ShowCount;j++)
						{
							str.Format("0X:%4X",GetData.Messagedata[i].value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,11+j,str);
						}

					}
					
				}
				else 
				{
					if((GetData.flag[i]==true)&&(CheckFiltration(GetData.Messagedata[i])==false))//过滤条件
					{
						InsertCount = GetData.ShowItem[i];
						if(InsertCount+1>BMView[m_channelshow].m_GetMessagelist.GetItemCount())
							BMView[m_channelshow].m_GetMessagelist.InsertItem(InsertCount,0);

						BMView[m_channelshow].m_GetMessagelist.SetItemText(i,2,"被过滤");
					}
					if( (GetData.flag[i]==true)&&(BMView[m_channelshow].Exce_Flag[GetData.Messagedata[i].command1.rtaddr][GetData.Messagedata[i].command1.subaddr]==false))
					{
						BMView[m_channelshow].m_GetMessagelist.SetItemText(i,2,"被过滤");
					}
				}
			}
		}
	}
	
	if(MessageData1553[m_channelshow].ShowType==0)
	{
		//GetData = MessageData1553[m_channelshow].GetMessageData(0);	
		if(GetData.MessageUnmber>0)
		{
			
			for(i=0;i<GetData.MessageUnmber;i++)  
			{ 
				if((CheckFiltration(GetData.Messagedata[i]))&&((BMView[m_channelshow].Exce_Flag[GetData.Messagedata[i].command1.rtaddr][GetData.Messagedata[i].command1.subaddr])))//过滤条件
				{
					//if(GetData.Messagedata[i].status_c1==1)   //BC->RT
					if(BMView[m_channelshow].m_GetMessagelist.GetItemCount()>=10000)
							BMView[m_channelshow].m_GetMessagelist.DeleteItem(0);
					{
						InsertCount = BMView[m_channelshow].m_GetMessagelist.GetItemCount();
						BMView[m_channelshow].m_GetMessagelist.InsertItem(InsertCount,0);
						BMView[m_channelshow].m_GetMessagelist.EnsureVisible( InsertCount, true );

						str.Format("%2d",GetData.Messagedata[i].messno);
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,1,str);
//add code
						if(GetData.Messagedata[i].status_c1==1)
							str.Format("%s","BC->RT");
						else if(GetData.Messagedata[i].status_c1==2)
							str.Format("%s","RT->BC");
						else if(GetData.Messagedata[i].status_c1==3)
							str.Format("%s","RT->RT");
						else if(GetData.Messagedata[i].status_c1==4)
							str.Format("%s","Non_Broadcast_Mode_With_Data_Recv");
						else if(GetData.Messagedata[i].status_c1==5)
							str.Format("%s","Non_Broadcast_Mode_With_Data_Send");
						else if(GetData.Messagedata[i].status_c1==6)
							str.Format("%s","Non_Broadcast_Mode_Non_Data");
						else if(GetData.Messagedata[i].status_c1==7)
							str.Format("%s","广播BC->RT");
						else if(GetData.Messagedata[i].status_c1==8)
							str.Format("%s","广播RT->RT");
						else if(GetData.Messagedata[i].status_c1==9)
							str.Format("%s","Broadcast_Mode_With_Data_Recv");
						else str.Format("%s","Broadcast_Mode_Non_Data");

						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,2,str);

						if((GetData.Messagedata[i].status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((GetData.Messagedata[i].status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,3,str);

						str.Format("%d",GetData.Messagedata[i].response1.time);
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,4,str);

						str =   MessageData1553[m_channelshow].InttoTimerStr(GetData.Messagedata[i].time.microseconds-MessageData1553[m_channelshow].firstTime);
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,5,str);

						

						if(GetData.Messagedata[i].status_c1==3)//RT->RT 
						{
							str.Format("%2d<-%2d",GetData.Messagedata[i].command1.rtaddr,GetData.Messagedata[i].command2.rtaddr);
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,6,str);

							str.Format("%2d<-%2d",GetData.Messagedata[i].command1.subaddr,GetData.Messagedata[i].command2.subaddr);
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,7,str);
						}
						else
						{
							str.Format("%2d",GetData.Messagedata[i].command1.rtaddr);
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,6,str);

							str.Format("%2d",GetData.Messagedata[i].command1.subaddr);
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,7,str);
						}


								
						if((GetData.Messagedata[i].status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((GetData.Messagedata[i].status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,8,str);

						
						if(GetData.Messagedata[i].status_c1==3)//RT->RT 
						{

							if(GetData.Messagedata[i].command2.wcount==0) ShowCount = 32;
							else  ShowCount= GetData.Messagedata[i].command2.wcount;
						}
						else
						{
							if(GetData.Messagedata[i].command1.wcount==0) ShowCount = 32;
							else  ShowCount= GetData.Messagedata[i].command1.wcount;
						}

						str.Format("%2d",ShowCount);
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,9,str);
						

						//memcpy(&valefef,&GetData.Messagedata[i].status1,sizeof(short));
						//valefef = MessageData1553[m_channelshow].Stutas1553ToInt(GetData.Messagedata[i].status1);
						memcpy(&valefef,&GetData.Messagedata[i].status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,10,str);

						if(GetData.Messagedata[i].status_c1>3) ShowCount = 32;
						for(j=0;j<ShowCount;j++)
						{
							str.Format("0X:%4X",GetData.Messagedata[i].value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							BMView[m_channelshow].m_GetMessagelist.SetItemText(InsertCount,11+j,str);
						}

					}
					
				}
				else 
				{
					//BMView[m_channelshow].m_GetMessagelist.SetItemText(0,1,"被过滤");
					//MessageData1553[m_channelshow].ShowLostCount++;
				}
			}
		}
	}
	BMView[m_channelshow].m_GetMessagelist.UnlockWindowUpdate();
}
void CMainFrame::GetMessageData()
{	
	int i,j,NowCount;
	CString str;

	for(i=0;i<MAX_1553BChanel;i++)//收4个通道的数据并显示
	{
		if(MessageData1553[i].ShowType==1)
		{
			GetData = MessageData1553[i].GetMessageData(1);
			if((GetData.MessageUnmber>0)&&(TimeShowFlag))
			{
				ShowMessageData(i);
			}
		}
		else
		{
			GetData = MessageData1553[i].GetMessageData(0);	
			if((GetData.MessageUnmber>0)&&(TimeShowFlag))
			{
				ShowMessageData(i);
			}
		}
	}
	GetData.MessageUnmber = 0;
}
void CMainFrame::FlashMenu()
{
	CString writestr;
	char writeVale[200];
	int ProjectCount,i;

	GetPrivateProfileString("sectiontype_BCProject","ProjectCount","0",writeVale,18,"C:\\ManCtrlB.ini");
	ProjectCount = atoi(writeVale);	

	CMenu*   pMenu   =   this-> GetMenu();     //这里永远为空
           // pMenu->ModifyMenu(ID_FILE_NEW, MF_BYCOMMAND , ID_FILE_NEW, strConnectTitle);


	for(i=0;i<ProjectCount;i++)
	{
		writestr.Format("BCProject%d",i);
		GetPrivateProfileString("sectiontype_BCProject",writestr,"",writeVale,200,"C:\\ManCtrlB.ini");

		writestr = writeVale;
		pMenu->ModifyMenu(ID_CURRENTPR1+i,MF_BYCOMMAND| MF_STRING,ID_CURRENTPR1+i,writestr);
	}
	for(ProjectCount=0;i<3;i++)
	{
		pMenu->ModifyMenu(ID_CURRENTPR1+i,MF_BYCOMMAND| MF_STRING,ID_CURRENTPR1+i,writestr);
	}
}

void CMainFrame::FlashConfigProject(CString FileStr)//更新最近打开文件
{
	CString writestr;
	char writeVale[300];
	int ProjectCount,i;

	GetPrivateProfileString("sectiontype_BCProject","ProjectCount","0",writeVale,18,"C:\\ManCtrlB.ini");
	ProjectCount = atoi(writeVale);	

	if(ProjectCount==3)
	{
		for(i=0;i<2;i++)
		{
			writestr.Format("BCProject%d",i+1);
			GetPrivateProfileString("sectiontype_BCProject",writestr,"0",writeVale,300,"C:\\ManCtrlB.ini");

			writestr.Format("BCProject%d",i);
			WritePrivateProfileString("sectiontype_BCProject",writestr,writeVale,"C:\\ManCtrlB.ini");

		}
	}
	

	

	writestr.Format("BCProject%d",ProjectCount-1);
	WritePrivateProfileString("sectiontype_BCProject",writestr,FileStr,"C:\\ManCtrlB.ini");

	if(ProjectCount<3) ProjectCount++;
	writestr.Format("%d",ProjectCount);
	WritePrivateProfileString("sectiontype_BCProject","ProjectCount",writestr,"C:\\ManCtrlB.ini");
	
}
void CMainFrame::ReadMessageSet(CString FileNameGet)
{
	CString FileName,FilePathName,writestr;
	CString inSertName;
	char writeVale[20];
	int i,j,k;

	if(FileNameGet=="")
	{
		CFileDialog FileSave( true,NULL,"*.zhp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
		if(FileSave.DoModal()==IDOK )
		{
			FileName=FileSave.GetPathName();
			SetWindowText(FileName);
			
			FlashConfigProject(FileName);
			

			GetPrivateProfileString("sectiontype_BC","AllBC_Count","",writeVale,18,FileName);
			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount=atoi(writeVale);

			GetPrivateProfileString("sectiontype_BC","BC_FrameTimer","100",writeVale,18,FileName);
			GetPrivateProfileStruct("sectiontype_BC","BC_RetryFlag",&MessageData1553[m_now_SelectChannel].wRetry, sizeof(BT_U16BIT),FileName);
			if(MessageData1553[m_now_SelectChannel].FrameTimer != atoi(writeVale))
			{
				MessageData1553[m_now_SelectChannel].FrameTimer = atoi(writeVale);
				MessageData1553[m_now_SelectChannel].InitBC();
			}

			for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;i++)
			{
				MessageData1553[m_now_SelectChannel].BCMessageEnabel[i] = true;
				writestr.Format("BC_retryflag%d",i);
				GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag[i], sizeof(bool),FileName);
					

				writestr.Format("BC%d",i);
				GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data[i], sizeof(API_BC_MBUF),FileName);
				
				writestr.Format("BC_type%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].MessageTyep[i]=atoi(writeVale);

				writestr.Format("BC_Name%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].MessageName[i].Format("%s",writeVale);

				writestr.Format("BC_Channel%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].chanA_B[i]=atoi(writeVale);

				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==0)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"BC->RT",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
				else if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==1)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"RT->BC",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
				else if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"RT->RT",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
			
				else if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==3)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"MODE",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);

				TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(10,inSertName,i);

				//////////显示到消息BCVIEW中/////
				BCView[m_now_SelectChannel].m_BC_MesList.InsertItem(i,0);
				BCView[m_now_SelectChannel].m_BC_MesList.AddNewItem(i);
				inSertName.Format("%2d",i);

				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,0,inSertName);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,1,MessageData1553[m_now_SelectChannel].MessageName[i]);
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==0) inSertName.Format("%s","BC->RT");
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==1) inSertName.Format("%s","RT->BC");
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2) inSertName.Format("%s","RT->RT");
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==3) inSertName.Format("%s","MODE");
 				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,2,inSertName);

				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command2.rtaddr);
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,3,inSertName);

				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command2.subaddr);
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,4,inSertName);

				if(MessageData1553[m_now_SelectChannel].chanA_B[i]==1)
					inSertName.Format("通道%S","A");
				else inSertName.Format("通道%S","B");
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,5,inSertName);

				if(MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.wcount==0)
					inSertName.Format("%2d",32);	
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.wcount);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,6,inSertName);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,7,"激活");

				CString str;
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==0)
				for(j=0;j<32;j++)
				{
					str.Format("0X:%4X",MessageData1553[m_now_SelectChannel].bc_msg_data[i].data[0][j]);
					for(k=3;k<7;k++)
					{
						if(str.GetAt(k)==' ') str.SetAt(k,'0');
					}
					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,8+j,str);
				}
				/////////////////////////////////
				//MessageData1553[m_now_SelectChannel].SetMessageTeam();//组织消息
			}
			///////////////////////////////////////////////
			GetPrivateProfileString("sectiontype_BC","AllBC_CountNOtime","",writeVale,18,FileName);
			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2=atoi(writeVale);

			GetPrivateProfileString("sectiontype_BC","BC_FrameTimer","100",writeVale,18,FileName);

			for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2;i++)
			{
				writestr.Format("BC_retryflagNOtime%d",i);
				GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag_2[i], sizeof(bool),FileName);
					
				writestr.Format("BCNOtime%d",i);
				GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data_2[i], sizeof(API_BC_MBUF),FileName);
				
				writestr.Format("BC_typeNOtime%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].MessageTyep_2[i]=atoi(writeVale);

				writestr.Format("BC_NameNOtime%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].MessageName_2[i].Format("%s",writeVale);

				writestr.Format("BC_ChannelNOtime%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].chanA_B_2[i]=atoi(writeVale);

				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==0)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"BC->RT",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
				else if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==1)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"RT->BC",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
				else if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"RT->RT",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
			
				else if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==3)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"MODE",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
		
				TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(11,inSertName,i);

				//////////显示到消息BCVIEW中/////
				BCView[m_now_SelectChannel].m_BC_MesList2.InsertItem(i,0);
				BCView[m_now_SelectChannel].m_BC_MesList2.AddNewItem(i);
				inSertName.Format("%2d",i);

				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,0,inSertName);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,1,MessageData1553[m_now_SelectChannel].MessageName_2[i]);
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==0) inSertName.Format("%s","BC->RT");
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==1) inSertName.Format("%s","RT->BC");
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2) inSertName.Format("%s","RT->RT");
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==3) inSertName.Format("%s","MODE");
 				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,2,inSertName);

				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command2.rtaddr);
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,3,inSertName);

				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command2.subaddr);
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,4,inSertName);

				if(MessageData1553[m_now_SelectChannel].chanA_B_2[i]==1)
					inSertName.Format("通道%S","A");
				else inSertName.Format("通道%S","B");

				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,5,inSertName);
				
				if(MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.wcount==0)
					inSertName.Format("%2d",32);	
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.wcount);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,6,inSertName);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,7,"激活");

				CString str;
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==0)
				for(j=0;j<32;j++)
				{
					str.Format("0X:%4X",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].data[0][j]);
					for(k=3;k<7;k++)
					{
						if(str.GetAt(k)==' ') str.SetAt(k,'0');
					}
					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,8+j,str);
				}
				/////////////////////////////////
				//MessageData1553[m_now_SelectChannel].SetMessageTeam();//组织消息
			}
			///////////////////////////////////////////////////////
			GetPrivateProfileStruct("sectiontype_RT","RTEXSIT",&MessageData1553[m_now_SelectChannel].RT_Data_Exsit, sizeof(bool)*32,FileName);
			writestr.Format("RT_Enable%d",i);
			GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].RT_Enable, sizeof(bool)*32,FileName);
			writestr.Format("RT_VectorArra%d",i);
			GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].VectorArra, sizeof(Vector_ArrayType)*32,FileName);
							
			for(i=0;i<32;i++)
			{
				
				if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i])
				{
					writestr.Format("RT%d",i);
					GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].RT_Data[i], sizeof(RT_DataType),FileName);
	/*
					writestr.Format("RT_status%d",i);
					GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].rtstatus[i], sizeof(BT_U16BIT),FileName);
	*/				

					if(MessageData1553[m_now_SelectChannel].RT_Data[i].VectorSetFlag==true)
						MessageData1553[m_now_SelectChannel].RT_WriteVectorWord(0, i, 0, 1, 0, MessageData1553[m_now_SelectChannel].RT_Data[i].VectorWord);
					if(MessageData1553[m_now_SelectChannel].RT_Data[i].StatusSetFlag==true)
						MessageData1553[m_now_SelectChannel].RT_WriteStatusWord(0, i, 0, 0, 0, MessageData1553[m_now_SelectChannel].RT_Data[i].StatusWord,1);

					writestr.Format("RT_VectorArra%d",i);
					GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].VectorArra[i], sizeof(Vector_ArrayType),FileName);

					inSertName.Format("RT%2d",i);
					TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(1,inSertName,i);
					//RTView[m_now_SelectChannel][i].ShowWindow(SW_SHOW);
					RTView[m_now_SelectChannel][i].SetWindowText(inSertName);
			
					Invalidate();
					for(j=0;j<32;j++)
					{
						if(MessageData1553[m_now_SelectChannel].RT_Data[i].SubSetFlag[j])
						{
							MessageData1553[m_now_SelectChannel].WriteRTData(i,j,0);
							SetRTViewData(i,j,MessageData1553[m_now_SelectChannel].RT_Data[i].msg_buffer_write[j],true);
							
						}
					}
				}
				if(MessageData1553[m_now_SelectChannel].RT_Enable[i])
				{
					MessageData1553[m_now_SelectChannel].EnableRT(i);
					MessageData1553[m_now_SelectChannel].RT_Enable[i] = true;
					TabProjDlg.ProjectDlg[m_now_SelectChannel].SetRTIcon(i,true);
				}
				else
				{
					MessageData1553[m_now_SelectChannel].DisableRT(i);
					MessageData1553[m_now_SelectChannel].RT_Enable[i] = false;
					TabProjDlg.ProjectDlg[m_now_SelectChannel].SetRTIcon(i,false);
				}
			}
			//////////////////////////////////////////////
		}
	
	}
	else
	{
		{
			FileName=FileNameGet;
			SetWindowText(FileName);
			
			FlashConfigProject(FileName);
			

			GetPrivateProfileString("sectiontype_BC","AllBC_Count","",writeVale,18,FileName);
			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount=atoi(writeVale);

			GetPrivateProfileString("sectiontype_BC","BC_FrameTimer","100",writeVale,18,FileName);
			GetPrivateProfileStruct("sectiontype_BC","BC_RetryFlag",&MessageData1553[m_now_SelectChannel].wRetry, sizeof(BT_U16BIT),FileName);
			if(MessageData1553[m_now_SelectChannel].FrameTimer != atoi(writeVale))
			{
				MessageData1553[m_now_SelectChannel].FrameTimer = atoi(writeVale);
				MessageData1553[m_now_SelectChannel].InitBC();
			}

			for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;i++)
			{
				MessageData1553[m_now_SelectChannel].BCMessageEnabel[i] = true;
				writestr.Format("BC_retryflag%d",i);
				GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag[i], sizeof(bool),FileName);
					

				writestr.Format("BC%d",i);
				GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data[i], sizeof(API_BC_MBUF),FileName);
				
				writestr.Format("BC_type%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].MessageTyep[i]=atoi(writeVale);

				writestr.Format("BC_Name%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].MessageName[i].Format("%s",writeVale);

				writestr.Format("BC_Channel%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].chanA_B[i]=atoi(writeVale);

				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==0)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"BC->RT",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
				else if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==1)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"RT->BC",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
				else if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"RT->RT",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
			
				else if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==3)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName[i],"MODE",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);

				TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(10,inSertName,i);

				//////////显示到消息BCVIEW中/////
				BCView[m_now_SelectChannel].m_BC_MesList.InsertItem(i,0);
				BCView[m_now_SelectChannel].m_BC_MesList.AddNewItem(i);
				inSertName.Format("%2d",i);

				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,0,inSertName);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,1,MessageData1553[m_now_SelectChannel].MessageName[i]);
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==0) inSertName.Format("%s","BC->RT");
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==1) inSertName.Format("%s","RT->BC");
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2) inSertName.Format("%s","RT->RT");
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==3) inSertName.Format("%s","MODE");
 				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,2,inSertName);

				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command2.rtaddr);
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.rtaddr);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,3,inSertName);

				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr,MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command2.subaddr);
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.subaddr);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,4,inSertName);

				if(MessageData1553[m_now_SelectChannel].chanA_B[i]==1)
					inSertName.Format("通道%S","A");
				else inSertName.Format("通道%S","B");
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,5,inSertName);

				if(MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.wcount==0)
					inSertName.Format("%2d",32);	
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data[i].mess_command1.wcount);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,6,inSertName);
				BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,7,"激活");

				CString str;
				if(MessageData1553[m_now_SelectChannel].MessageTyep[i]==0)
				for(j=0;j<32;j++)
				{
					str.Format("0X:%4X",MessageData1553[m_now_SelectChannel].bc_msg_data[i].data[0][j]);
					for(k=3;k<7;k++)
					{
						if(str.GetAt(k)==' ') str.SetAt(k,'0');
					}
					BCView[m_now_SelectChannel].m_BC_MesList.SetItemText(i,8+j,str);
				}
				/////////////////////////////////
				//MessageData1553[m_now_SelectChannel].SetMessageTeam();//组织消息
			}
			///////////////////////////////////////////////
			GetPrivateProfileString("sectiontype_BC","AllBC_CountNOtime","",writeVale,18,FileName);
			MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2=atoi(writeVale);

			GetPrivateProfileString("sectiontype_BC","BC_FrameTimer","100",writeVale,18,FileName);

			for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2;i++)
			{
				writestr.Format("BC_retryflagNOtime%d",i);
				GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag_2[i], sizeof(bool),FileName);
					
				writestr.Format("BCNOtime%d",i);
				GetPrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data_2[i], sizeof(API_BC_MBUF),FileName);
				
				writestr.Format("BC_typeNOtime%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].MessageTyep_2[i]=atoi(writeVale);

				writestr.Format("BC_NameNOtime%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].MessageName_2[i].Format("%s",writeVale);

				writestr.Format("BC_ChannelNOtime%d",i);
				GetPrivateProfileString("sectiontype_BC",writestr,"",writeVale,18,FileName);
				MessageData1553[m_now_SelectChannel].chanA_B_2[i]=atoi(writeVale);

				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==0)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"BC->RT",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
				else if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==1)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"RT->BC",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
				else if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"RT->RT",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
			
				else if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==3)
					inSertName.Format("%s-%s:rt%2d-sub%2d",MessageData1553[m_now_SelectChannel].MessageName_2[i],"MODE",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
		
				TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(11,inSertName,i);

				//////////显示到消息BCVIEW中/////
				BCView[m_now_SelectChannel].m_BC_MesList2.InsertItem(i,0);
				BCView[m_now_SelectChannel].m_BC_MesList2.AddNewItem(i);
				inSertName.Format("%2d",i);

				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,0,inSertName);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,1,MessageData1553[m_now_SelectChannel].MessageName_2[i]);
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==0) inSertName.Format("%s","BC->RT");
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==1) inSertName.Format("%s","RT->BC");
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2) inSertName.Format("%s","RT->RT");
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==3) inSertName.Format("%s","MODE");
 				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,2,inSertName);

				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command2.rtaddr);
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.rtaddr);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,3,inSertName);

				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==2) inSertName.Format("%2d/%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr,MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command2.subaddr);
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.subaddr);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,4,inSertName);

				if(MessageData1553[m_now_SelectChannel].chanA_B_2[i]==1)
					inSertName.Format("通道%S","A");
				else inSertName.Format("通道%S","B");

				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,5,inSertName);
				
				if(MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.wcount==0)
					inSertName.Format("%2d",32);	
				else inSertName.Format("%2d",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].mess_command1.wcount);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,6,inSertName);
				BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,7,"激活");

				CString str;
				if(MessageData1553[m_now_SelectChannel].MessageTyep_2[i]==0)
				for(j=0;j<32;j++)
				{
					str.Format("0X:%4X",MessageData1553[m_now_SelectChannel].bc_msg_data_2[i].data[0][j]);
					for(k=3;k<7;k++)
					{
						if(str.GetAt(k)==' ') str.SetAt(k,'0');
					}
					BCView[m_now_SelectChannel].m_BC_MesList2.SetItemText(i,8+j,str);
				}
				/////////////////////////////////
				//MessageData1553[m_now_SelectChannel].SetMessageTeam();//组织消息
			}
			///////////////////////////////////////////////////////
			GetPrivateProfileStruct("sectiontype_RT","RTEXSIT",&MessageData1553[m_now_SelectChannel].RT_Data_Exsit, sizeof(bool)*32,FileName);
			writestr.Format("RT_Enable%d",i);
			GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].RT_Enable, sizeof(bool)*32,FileName);
			writestr.Format("RT_VectorArra%d",i);
			GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].VectorArra, sizeof(Vector_ArrayType)*32,FileName);
							
			for(i=0;i<32;i++)
			{
				
				if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i])
				{
					writestr.Format("RT%d",i);
					GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].RT_Data[i], sizeof(RT_DataType),FileName);
	/*
					writestr.Format("RT_status%d",i);
					GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].rtstatus[i], sizeof(BT_U16BIT),FileName);
	*/				

					if(MessageData1553[m_now_SelectChannel].RT_Data[i].VectorSetFlag==true)
						MessageData1553[m_now_SelectChannel].RT_WriteVectorWord(0, i, 0, 1, 0, MessageData1553[m_now_SelectChannel].RT_Data[i].VectorWord);
					if(MessageData1553[m_now_SelectChannel].RT_Data[i].StatusSetFlag==true)
						MessageData1553[m_now_SelectChannel].RT_WriteStatusWord(0, i, 0, 0, 0, MessageData1553[m_now_SelectChannel].RT_Data[i].StatusWord,1);

					writestr.Format("RT_VectorArra%d",i);
					GetPrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].VectorArra[i], sizeof(Vector_ArrayType),FileName);

					inSertName.Format("RT%2d",i);
					TabProjDlg.ProjectDlg[m_now_SelectChannel].InsertTreeData(1,inSertName,i);
					//RTView[m_now_SelectChannel][i].ShowWindow(SW_SHOW);
					RTView[m_now_SelectChannel][i].SetWindowText(inSertName);
			
					Invalidate();
					for(j=0;j<32;j++)
					{
						if(MessageData1553[m_now_SelectChannel].RT_Data[i].SubSetFlag[j])
						{
							MessageData1553[m_now_SelectChannel].WriteRTData(i,j,0);
							SetRTViewData(i,j,MessageData1553[m_now_SelectChannel].RT_Data[i].msg_buffer_write[j],true);
							
						}
					}
				}
				if(MessageData1553[m_now_SelectChannel].RT_Enable[i])
				{
					MessageData1553[m_now_SelectChannel].EnableRT(i);
					MessageData1553[m_now_SelectChannel].RT_Enable[i] = true;
					TabProjDlg.ProjectDlg[m_now_SelectChannel].SetRTIcon(i,true);
				}
				else
				{
					MessageData1553[m_now_SelectChannel].DisableRT(i);
					MessageData1553[m_now_SelectChannel].RT_Enable[i] = false;
					TabProjDlg.ProjectDlg[m_now_SelectChannel].SetRTIcon(i,false);
				}
			}
			//////////////////////////////////////////////
		}
	
	}
}
bool CMainFrame::SaveMessageSet()
{
	CString FileName,FilePathName,writeVale,writestr;
	int i;
	int RT_Count;

	RT_Count = 0;

	for(i=0;i<32;i++)
	{
		if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i]) RT_Count++;
	}
	if((MessageData1553[m_now_SelectChannel].BC_MessageMaxCount>0)||(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2>0)||(RT_Count>0))
	{
		CFileDialog FileSave( false,NULL,"*.zhp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
		if(FileSave.DoModal()==IDOK )
		{
			//FilePath=FileSave.GetFolderPath();
			
			FileName=FileSave.GetPathName();
			SetWindowText(FileName);
			CFileFind ff;
			if(ff.FindFile(FileName,0))
			{
				::DeleteFile(FileName);
			}

			WritePrivateProfileStruct("sectiontype_BC","BC_RetryFlag",&MessageData1553[m_now_SelectChannel].wRetry, sizeof(BT_U16BIT),FileName);
			///存BC周期数据
			writestr.Format("%2d",MessageData1553[m_now_SelectChannel].BC_MessageMaxCount);
			WritePrivateProfileString("sectiontype_BC","AllBC_Count",writestr,FileName);

			writestr.Format("%4d",MessageData1553[m_now_SelectChannel].FrameTimer);
			WritePrivateProfileString("sectiontype_BC","BC_FrameTimer",writestr,FileName);


			for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;i++)
			{
				writestr.Format("BC_type%d",i);
				writeVale.Format("%d",MessageData1553[m_now_SelectChannel].MessageTyep[i]);
				WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
				writestr.Format("BC_Name%d",i);
				writeVale.Format("%s",MessageData1553[m_now_SelectChannel].MessageName[i]);
				WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
				writestr.Format("BC_Channel%d",i);
				writeVale.Format("%d",MessageData1553[m_now_SelectChannel].chanA_B[i]);
				WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
				
				writestr.Format("BC%d",i);
				WritePrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data[i], sizeof(API_BC_MBUF),FileName);
			
				writestr.Format("BC_retryflag%d",i);
				WritePrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag[i], sizeof(bool),FileName);
			

			}
			///存BC非周期数据
			writestr.Format("%2d",MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2);
			WritePrivateProfileString("sectiontype_BC","AllBC_CountNOtime",writestr,FileName);

			for(i=0;i<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2;i++)
			{
				writestr.Format("BC_typeNOtime%d",i);
				writeVale.Format("%d",MessageData1553[m_now_SelectChannel].MessageTyep_2[i]);
				WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
				writestr.Format("BC_NameNOtime%d",i);
				writeVale.Format("%s",MessageData1553[m_now_SelectChannel].MessageName_2[i]);
				WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
				writestr.Format("BC_ChannelNOtime%d",i);
				writeVale.Format("%d",MessageData1553[m_now_SelectChannel].chanA_B_2[i]);
				WritePrivateProfileString("sectiontype_BC",writestr,writeVale,FileName);
				
				writestr.Format("BCNOtime%d",i);
				WritePrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].bc_msg_data_2[i], sizeof(API_BC_MBUF),FileName);
			
				writestr.Format("BC_retryflagNOtime%d",i);
				WritePrivateProfileStruct("sectiontype_BC",writestr,&MessageData1553[m_now_SelectChannel].BCRetry_Flag_2[i], sizeof(bool),FileName);
			
			}

			/////////////////////RT///
			WritePrivateProfileStruct("sectiontype_RT","RTEXSIT",&MessageData1553[m_now_SelectChannel].RT_Data_Exsit, sizeof(bool)*32,FileName);
			writestr.Format("RT_Enable%d",i);
			WritePrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].RT_Enable, sizeof(bool)*32,FileName);
			writestr.Format("RT_VectorArra%d",i);
			WritePrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].VectorArra[i], sizeof(Vector_ArrayType),FileName);
						
			for(i=0;i<32;i++)
			{
				if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i])
				{
					writestr.Format("RT%d",i);
					WritePrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].RT_Data[i], sizeof(RT_DataType),FileName);
					writestr.Format("RT_status%d",i);
					WritePrivateProfileStruct("sectiontype_RT",writestr,&MessageData1553[m_now_SelectChannel].rtstatus[i], sizeof(BT_U16BIT),FileName);
				}
				
			}



			return true;
		}
		else return false;
	}
	else 
	{
		MessageBox("没有设置BC消息或RT数据\N不能保存","提示",MB_OK);
		return false;
	}

}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	GetMessageData();

	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnDestroy() 
{
/*	int i,h;
	CFileFind FindFile  ;

	KillTimer(15);
	
	if(MessageBox("是否保存当前工程","提示",MB_YESNO)==IDYES)
	{
		SaveMessageSet();	
	}

	Sleep(500);
	if(BMView[m_now_SelectChannel].ReadDataFlag==true)
	{
		
		FindFile.Close();
		//MessageData1553[m_now_SelectChannel].Out1553();
		MessageData1553[m_now_SelectChannel].FileRead.Close();
		MessageData1553[m_now_SelectChannel].FileWrite.Close();
		BMView[m_now_SelectChannel].DestroyWindow();
		BCView[m_now_SelectChannel].DestroyWindow();
		for(i=0;i<500;i++)
		{
			h=i;
		}

		Sleep(500);
	//	this->DestroyWindow();
		CMDIFrameWnd::OnDestroy();

	}
	else
	{

		BM_NoGetData();
		
		if(FindFile.FindFile(MessageData1553[m_now_SelectChannel].FileNameTempSave,0))
		{
			if(MessageBox("是否保存BM收到的消息","提示",MB_YESNO)==IDYES)
			{
				BMView[m_now_SelectChannel].OnSaveData();
			}
		}

		

		FindFile.Close();
		MessageData1553[m_now_SelectChannel].Out1553();
		MessageData1553[m_now_SelectChannel].FileRead.Close();
		MessageData1553[m_now_SelectChannel].FileWrite.Close();
		BMView[m_now_SelectChannel].DestroyWindow();
		
		Sleep(500);
	//	this->DestroyWindow();
		CMDIFrameWnd::OnDestroy();
	}
	
	*/

	CMDIFrameWnd::OnDestroy();
	// TODO: Add your message handler code here
	
}
void CMainFrame::OpenCurrent1()
{
	CString FileName,FilePathName,writeVale,writestr,FileNameGet;
	int i,returnval;
	int RT_Count;
	char writeVale2[300];

	RT_Count = 0;

	writestr.Format("BCProject%d",0);
	GetPrivateProfileString("sectiontype_BCProject",writestr,"",writeVale2,300,"C:\\ManCtrlB.ini");

	FileNameGet = writeVale2;

	for(i=0;i<32;i++)
	{
		if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i]) RT_Count++;
	}
	if((MessageData1553[m_now_SelectChannel].BC_MessageMaxCount>0)||(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2>0)||(RT_Count>0))
	{
		returnval=MessageBox("是否保存当前消息组","提示",MB_YESNOCANCEL);
		if(returnval==IDYES)
		{
			if(SaveMessageSet()==true)//保存成功
			{
				InitAllSet();
				ReadMessageSet(FileNameGet);
			}
			else
			{

			}
		}
		if(returnval==IDNO)
		{
			InitAllSet();
			ReadMessageSet(FileNameGet);
		}
	}
	else 
	{
		ReadMessageSet(FileNameGet);
	}
}
void CMainFrame::OpenCurrent2()
{
	CString FileName,FilePathName,writeVale,writestr,FileNameGet;
	int i,returnval;
	int RT_Count;
	char writeVale2[300];

	RT_Count = 0;

	writestr.Format("BCProject%d",1);
	GetPrivateProfileString("sectiontype_BCProject",writestr,"",writeVale2,300,"C:\\ManCtrlB.ini");

	FileNameGet = writeVale2;

	for(i=0;i<32;i++)
	{
		if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i]) RT_Count++;
	}
	if((MessageData1553[m_now_SelectChannel].BC_MessageMaxCount>0)||(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2>0)||(RT_Count>0))
	{
		returnval=MessageBox("是否保存当前消息组","提示",MB_YESNOCANCEL);
		if(returnval==IDYES)
		{
			if(SaveMessageSet()==true)//保存成功
			{
				InitAllSet();
				ReadMessageSet(FileNameGet);
			}
			else
			{

			}
		}
		if(returnval==IDNO)
		{
			InitAllSet();
			ReadMessageSet(FileNameGet);
		}
	}
	else 
	{
		ReadMessageSet(FileNameGet);
	}
}

void CMainFrame::OpenCurrent3()
{
	CString FileName,FilePathName,writeVale,writestr,FileNameGet;
	int i,returnval;
	int RT_Count;
	char writeVale2[300];

	RT_Count = 0;

	writestr.Format("BCProject%d",2);
	GetPrivateProfileString("sectiontype_BCProject",writestr,"",writeVale2,300,"C:\\ManCtrlB.ini");

	FileNameGet = writeVale2;

	for(i=0;i<32;i++)
	{
		if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i]) RT_Count++;
	}
	if((MessageData1553[m_now_SelectChannel].BC_MessageMaxCount>0)||(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2>0)||(RT_Count>0))
	{
		returnval=MessageBox("是否保存当前消息组","提示",MB_YESNOCANCEL);
		if(returnval==IDYES)
		{
			if(SaveMessageSet()==true)//保存成功
			{
				InitAllSet();
				ReadMessageSet(FileNameGet);
			}
			else
			{

			}
		}
		if(returnval==IDNO)
		{
			InitAllSet();
			ReadMessageSet(FileNameGet);
		}
	}
	else 
	{
		ReadMessageSet(FileNameGet);
	}
}

void CMainFrame::OpenMessageSet()
{
	CString FileName,FilePathName,writeVale,writestr;
	int i,returnval;
	int RT_Count;

	RT_Count = 0;

	for(i=0;i<32;i++)
	{
		if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i]) RT_Count++;
	}
	if((MessageData1553[m_now_SelectChannel].BC_MessageMaxCount>0)||(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2>0)||(RT_Count>0))
	{
		returnval=MessageBox("是否保存当前消息组","提示",MB_YESNOCANCEL);
		if(returnval==IDYES)
		{
			if(SaveMessageSet()==true)//保存成功
			{
				InitAllSet();
				ReadMessageSet("");
			}
			else
			{

			}
		}
		if(returnval==IDNO)
		{
			InitAllSet();
			ReadMessageSet("");
		}
	}
	else 
	{
		ReadMessageSet("");
	}

}

void CMainFrame::InitAllSet()
{
	
	int i,j;
	
	CWorkModeSelect WorkModeDlg;

	//if(WorkModeDlg.DoModal()==IDOK)
	{
	//	bcmode = WorkModeDlg.m_bcmode;
	//	rtmode = WorkModeDlg.m_rtmode;
	//	bmmode = WorkModeDlg.m_bmmode;

	bcmode = true;
	rtmode = true;
	bmmode = true;

		BCView[m_now_SelectChannel].m_BC_MesList.DeleteAllItemCheckBox();
		BCView[m_now_SelectChannel].m_BC_MesList.DeleteAllItems();

		BCView[m_now_SelectChannel].m_BC_MesList2.DeleteAllItemCheckBox();
		BCView[m_now_SelectChannel].m_BC_MesList2.DeleteAllItems();
		
		for(i=0;i<32;i++)
		{
			RTView[m_now_SelectChannel][i].ShowWindow(SW_HIDE);
			RTView[m_now_SelectChannel][i].m_RT_DataList.DeleteAllItems();
			for(j=0;j<32;j++)
				RTView[m_now_SelectChannel][i].SubAdressShow[j] = false;
		}
		
		MessageData1553[m_now_SelectChannel].InitMessageTeam();
		TabProjDlg.ProjectDlg[m_now_SelectChannel].InitAllSet();
		BMView[m_now_SelectChannel].InitBM();

	}
}



void CMainFrame::StepRun()
{
	StopBC();
	MessageData1553[m_now_SelectChannel].StepRun();
}

void CMainFrame::OnProper()
{
	CBCPROPER	BCProperDlg;
	BCProperDlg.Maxcount=MessageData1553[m_now_SelectChannel].BC_MessageMaxCount;
	BCProperDlg.frameTime = MessageData1553[m_now_SelectChannel].FrameTimer;
	BCProperDlg.GrapTime = MessageData1553[m_now_SelectChannel].GrapTimer;
	BCProperDlg.multiple_retryval = MessageData1553[m_now_SelectChannel].BC_RetryVal;
	BCProperDlg.wRetry = MessageData1553[m_now_SelectChannel].wRetry;
	if(BCProperDlg.DoModal()==IDOK)
	{
		MessageData1553[m_now_SelectChannel].FrameTimer = BCProperDlg.frameTime;
		//MessageData1553[m_now_SelectChannel].GrapTimer = BCProperDlg.GrapTime;
		MessageData1553[m_now_SelectChannel].BC_RetryVal = BCProperDlg.multiple_retryval;
		MessageData1553[m_now_SelectChannel].wRetry = BCProperDlg.wRetry;
		MessageData1553[m_now_SelectChannel].InitBC();
	}

}

void CMainFrame::NewSetMessage()
{
	CString FileName,FilePathName,writeVale,writestr;
	int i,returnval;
	int RT_Count;

	RT_Count = 0;

	if(MessageData1553[m_now_SelectChannel].BC_stutas==0)
	{
		for(i=0;i<32;i++)
		{
			if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i]) RT_Count++;
		}
		if((MessageData1553[m_now_SelectChannel].BC_MessageMaxCount>0)||(MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2>0)||(RT_Count>0))
		{
			returnval=MessageBox("是否保存当前消息组","提示",MB_YESNOCANCEL);
			if(returnval==IDYES)
			{
				if(SaveMessageSet()==true)//保存成功
				{
					InitAllSet();
					SetWindowText("新建工程");
				}
				else
				{

				}
			}
			if(returnval==IDNO)
			{
				InitAllSet();
				SetWindowText("新建工程");
			}
		}
		else 
		{
			SetWindowText("新建工程");
		}
	}
	else
	{
		MessageBox("新建前请先停止BC","提示",MB_ICONSTOP);
	}
}



void CMainFrame::View_BC()
{
	if(bcmode)BCView[m_now_SelectChannel].ShowWindow(SW_SHOWNA);
}

void CMainFrame::View_BM()
{
	if(bmmode)BMView[m_now_SelectChannel].ShowWindow(SW_SHOWNA);
}

void CMainFrame::View_RT()
{
	int i;
	if(rtmode)
	for(i=0;i<32;i++)
	{
		if(MessageData1553[m_now_SelectChannel].RT_Data_Exsit[i]==true)
		{
			RTView[m_now_SelectChannel][i].ShowWindow(SW_SHOWNA);
		}
	}


}
void CMainFrame::DeleteRT()
{

	{
		MessageData1553[m_now_SelectChannel].DeleteRT(NowSelectRT);
		RTView[m_now_SelectChannel][NowSelectRT].DeleteRT();
		TabProjDlg.ProjectDlg[m_now_SelectChannel].DeleteRT(NowSelectRT);
		RTView[m_now_SelectChannel][NowSelectRT].ShowWindow(SW_HIDE);
	}

}
void CMainFrame::ShowRTdata()
{
	RTView[m_now_SelectChannel][NowSelectRT].ShowWindow(SW_SHOW);
}

void CMainFrame::BM_GetData()
{
	BM_GetFlag = true;
	SetTimer(0,50,NULL);
}

void CMainFrame::BM_NoGetData()
{
	BM_GetFlag = false;
	KillTimer(0);
}



void CMainFrame::EditRTdata()
{
	CRTDataSet RTSetDlg;
	RTSetDlg.IniType = 0;//
	RTSetDlg.RTAdress = NowSelectRT;//
	if(RTSetDlg.DoModal()==IDOK)
	{

	}
}

void CMainFrame::CPropRT()
{
	//CRTProp RT_PropDlg;
	
	//RT_PropDlg.DoModal();
}

void CMainFrame::SendNotimeMessage()
{
	MessageData1553[m_now_SelectChannel].SendNotimeMessage();
}
void CMainFrame::ShowProject()
{
	//m_wndMyBar1.ShowWindow(SW_SHOW);
	ShowControlBar(&m_wndMyBar1, !m_wndMyBar1.IsVisible(), FALSE);
}

void CMainFrame::SendMessgeNowSelecte(int TypeMessage, int MessageID)//单次发送选择消息
{
	if(NowAddMessageType==1)//周期消息
	{
		if(NowdeletID>=0)//找到要删除的BC消息ID
		{
			MessageData1553[m_now_SelectChannel].SendNowSelecteMessage(1,NowdeletID);
		}
	}
	else if(NowAddMessageType==2)//非周期消息
	{
		if(NowdeletID>=0)//找到要删除的BC消息ID
		{
			MessageData1553[m_now_SelectChannel].SendNowSelecteMessage(2,NowdeletID);
		}
	}
}

void CMainFrame::MoveDownBCMessage()
{
	if(NowAddMessageType==1)//周期消息
	{
		if(NowdeletID<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount-1)//找到要删除的BC消息ID
		{
			MessageData1553[m_now_SelectChannel].MoveDownBCMessage(1,NowdeletID);
			BCView[m_now_SelectChannel].MoveDownBCMessage(1,NowdeletID);
			//ProjectDlg.MoveDownBCMessage(1,NowdeletID);
		}
	}
	else	if(NowAddMessageType==2)//非周期消息
	{
		if(NowdeletID<MessageData1553[m_now_SelectChannel].BC_MessageMaxCount_2-1)//找到要删除的BC消息ID
		{
			MessageData1553[m_now_SelectChannel].MoveDownBCMessage(2,NowdeletID);
			BCView[m_now_SelectChannel].MoveDownBCMessage(2,NowdeletID);
			//ProjectDlg.MoveDownBCMessage(2,NowdeletID);
		}
	}
}

void CMainFrame::MoveUpBCMessage()
{
	if(NowAddMessageType==1)//周期消息
	{
		if(NowdeletID>=1)//找到要删除的BC消息ID
		{
			MessageData1553[m_now_SelectChannel].MoveUpBCMessage(1,NowdeletID);
			BCView[m_now_SelectChannel].MoveUpBCMessage(1,NowdeletID);
			//ProjectDlg.MoveUpBCMessage(1,NowdeletID);
		}
	}
	else	if(NowAddMessageType==2)//非周期消息
	{
		if(NowdeletID>=1)//找到要删除的BC消息ID
		{
			MessageData1553[m_now_SelectChannel].MoveUpBCMessage(2,NowdeletID);
			BCView[m_now_SelectChannel].MoveUpBCMessage(2,NowdeletID);
			//ProjectDlg.MoveUpBCMessage(2,NowdeletID);
		}
	}
}

void CMainFrame::MoveBCMessageto(int tyep, int fp, int lp)
{
	int i;

	if(tyep==1)//周期消息
	{
		if(fp>lp)
		{
			for(i=fp;i>lp;i--)
			{
				MessageData1553[m_now_SelectChannel].MoveUpBCMessage(1,i);
				BCView[m_now_SelectChannel].MoveUpBCMessage(1,i);
			}
		}
		else if(fp<lp)
		{
			for(i=fp;i<lp;i++)
			{
				MessageData1553[m_now_SelectChannel].MoveDownBCMessage(1,i);
				BCView[m_now_SelectChannel].MoveDownBCMessage(1,i);
			}
		}
	}
	else	if(tyep==2)//非周期消息
	{
		if(fp>lp)
		{
			for(i=fp;i>lp;i--)
			{
				MessageData1553[m_now_SelectChannel].MoveUpBCMessage(2,i);
				BCView[m_now_SelectChannel].MoveUpBCMessage(2,i);
			}
		}
		else if(fp<lp)
		{
			for(i=fp;i<lp;i++)
			{
				MessageData1553[m_now_SelectChannel].MoveDownBCMessage(2,i);
				BCView[m_now_SelectChannel].MoveDownBCMessage(2,i);
			}
		}
	}
}

void CMainFrame::Change1553()
{


	::SetMenu(m_hWnd,hMenuMain);
	m_wndMyBar1.ShowWindow(SW_SHOW);
	Tab1553Sel.ShowWindow(SW_SHOW);
	

}
void CMainFrame::ChangeMainCtrl()
{
	::SetMenu(m_hWnd ,hMenuMainCtrl);
	m_wndMyBar1.ShowWindow(SW_HIDE);
	Tab1553Sel.ShowWindow(SW_HIDE);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIFrameWnd::OnSize(nType, cx, cy);
	
	hMenuMain = ::LoadMenu((HINSTANCE)GetWindowLong(m_hWnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDR_MAINFRAME));
	hMenuMainCtrl = ::LoadMenu((HINSTANCE)GetWindowLong(m_hWnd,GWL_HINSTANCE),MAKEINTRESOURCE(IDR_MENU_MAINCTRL));	// TODO: Add your message handler code here
		::SetMenu(m_hWnd ,hMenuMainCtrl);
}
