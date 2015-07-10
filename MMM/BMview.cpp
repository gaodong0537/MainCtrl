// BMview.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "BMview.h"
#include "MainFrm.h"
#include "MonitorConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CBMview dialog


CBMview::CBMview(CWnd* pParent /*=NULL*/)
	: CDialog(CBMview::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBMview)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBMview::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBMview)
	DDX_Control(pDX, IDC_LIST2, m_GetMessagelist);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BUTTON1, m_Save);
	DDX_Control(pDX, IDC_BUTTON2, m_Open);
	DDX_Control(pDX, IDC_BUTTON3, m_Add);
	DDX_Control(pDX, IDC_BUTTON5, m_Get);
	DDX_Control(pDX, IDC_BUTTON22,m_ShowMode);
	DDX_Control(pDX, IDC_BUTTON8,m_ClearView);
}


BEGIN_MESSAGE_MAP(CBMview, CDialog)
	//{{AFX_MSG_MAP(CBMview)
	ON_WM_HSCROLL()
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON2, OnReadData)
	ON_BN_CLICKED(IDC_BUTTON4, OnShowMode)
	ON_BN_CLICKED(IDC_BUTTON5, OnGetData)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, OnClickList2)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON22, OnButtonShowMode)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST2, OnGetdispinfoList2)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON8, OnClearview)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON1, OnSaveData)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBMview message handlers

BOOL CBMview::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	
	return CDialog::Create(IDD, pParentWnd);
}

void CBMview::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CBMview::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	LV_COLUMN lvcolumn;

	// TODO: Add extra initialization here
	m_GetMessagelist.ModifyStyle(LVS_EDITLABELS,0L);
	m_GetMessagelist.ModifyStyle(0L,LVS_REPORT);
	m_GetMessagelist.ModifyStyle(0L,LVS_SHOWSELALWAYS);
	m_GetMessagelist.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	m_GetMessagelist.Init();
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.cx = 1;
	lvcolumn.pszText = "";
	m_GetMessagelist.InsertColumn(0,&lvcolumn);

	lvcolumn.cx = 70;
	lvcolumn.pszText = "消息ID";
	m_GetMessagelist.InsertColumn(1,&lvcolumn);

	lvcolumn.cx = 70;
	lvcolumn.pszText = "消息类型";
	m_GetMessagelist.InsertColumn(2,&lvcolumn);

	lvcolumn.cx = 110;
	lvcolumn.pszText = "消息状态";
	m_GetMessagelist.InsertColumn(3,&lvcolumn);

	lvcolumn.cx =100;
	lvcolumn.pszText = "响应时间(us)";
	m_GetMessagelist.InsertColumn(4,&lvcolumn);

	lvcolumn.cx =200;
	lvcolumn.pszText = "时标(时:分:秒-毫秒:微秒)";
	m_GetMessagelist.InsertColumn(5,&lvcolumn);



	lvcolumn.cx = 55;
	lvcolumn.pszText = "地址";
	m_GetMessagelist.InsertColumn(6,&lvcolumn);
	lvcolumn.cx = 55;
	lvcolumn.pszText = "子地址";
	m_GetMessagelist.InsertColumn(7,&lvcolumn);

	lvcolumn.cx = 60;
	lvcolumn.pszText = "通道";
	m_GetMessagelist.InsertColumn(8,&lvcolumn);

	lvcolumn.cx = 90;
	lvcolumn.pszText = "数据个数";
	m_GetMessagelist.InsertColumn(9,&lvcolumn);

	lvcolumn.cx = 80;
	lvcolumn.pszText = "状态字";
	m_GetMessagelist.InsertColumn(10,&lvcolumn);

	int i;
	char str[20];
	for(i=0;i<32;i++)
	{
		sprintf(str,"数据%d",i);
		lvcolumn.pszText = str; 
		lvcolumn.cx = 70;
		m_GetMessagelist.InsertColumn(11+i,&lvcolumn);
	}

	

	m_Save.SetIcon(IDI_SAVE,IDI_SAVE);
	m_Save.DrawBorder(true);
	m_Save.OffsetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_Save.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 128, 0));

	m_Save.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(237,246,255));
	m_Save.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(237,246,255));
	m_Save.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(237,246,255));


	m_Save.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_Save.SetTooltipText("保存数据");
	m_Save.SetShowText(true);
	m_Save.SetFlat(false,false);


	m_Open.SetIcon(IDI_READ,IDI_READ);
	m_Open.DrawBorder(true);
	m_Open.OffsetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_Open.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 128, 0));

	m_Open.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(237,246,255));
	m_Open.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(237,246,255));
	m_Open.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(237,246,255));

	m_Open.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_Open.SetTooltipText("读出数据");
	m_Open.SetShowText(true);
	m_Open.SetFlat(false,false);

	m_Add.SetIcon(IDI_ADD,IDI_ADD);
	m_Add.DrawBorder(true);
	m_Add.OffsetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_Add.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 128, 0));
	m_Add.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(237,246,255));
	m_Add.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(237,246,255));
	m_Add.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(237,246,255));
	m_Add.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_Add.SetTooltipText("读出数据");
	m_Add.SetShowText(true);
	m_Add.SetFlat(false,false);

	m_Get.SetIcon(IDI_GET,IDI_GET);
	m_Get.DrawBorder(true);
	m_Get.OffsetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_Get.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 128, 0));
	m_Get.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(237,246,255));
	m_Get.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(237,246,255));
	m_Get.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(237,246,255));
	m_Get.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_Get.SetTooltipText("暂停接收");
	m_Get.SetShowText(true);
	m_Get.SetFlat(false,false);

	m_ShowMode.SetIcon(IDI_ICON7,IDI_ICON7);
	m_ShowMode.DrawBorder(true);
	m_ShowMode.OffsetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_ShowMode.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 128, 0));
	m_ShowMode.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(237,246,255));
	m_ShowMode.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(237,246,255));
	m_ShowMode.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(237,246,255));
	m_ShowMode.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_ShowMode.SetTooltipText("更改");
	m_ShowMode.SetShowText(true);
	m_ShowMode.SetFlat(false,false);

	m_ClearView.SetIcon(IDI_ICON8,IDI_ICON8);
	m_ClearView.DrawBorder(true);
	m_ClearView.OffsetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_ClearView.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 128, 0));
	m_ClearView.SetColor(CButtonST::BTNST_COLOR_BK_IN, RGB(237,246,255));
	m_ClearView.SetColor(CButtonST::BTNST_COLOR_BK_OUT, RGB(237,246,255));
	m_ClearView.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, RGB(237,246,255));
	m_ClearView.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_ClearView.SetTooltipText("更改");
	m_ClearView.SetShowText(true);
	m_ClearView.SetFlat(false,false);

	

	((CButton*)(GetDlgItem(IDC_CHECK1)))->SetCheck(true);

	OnShowMode();
	
	DataDlg.Create("","",NULL,CRect(0,0,50,50),this,IDD_SHOWDATA,NULL);
	DataDlg.GetWindowRect(rect);
	//DataDlg.MoveWindow(1,1,rect2.right,rect2.bottom,false);
	DataDlg.ShowWindow(SW_HIDE);

	
	ReadDataFlag = false;
	messCount = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CBMview::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F1)
	{
		m_pMainWnd->RunBC();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F2)
	{
		m_pMainWnd->StopBC();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F3)
	{
		m_pMainWnd->StepRun();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F4)
	{
		m_pMainWnd->RunRT();
	}
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_F5)
	{
		m_pMainWnd->StopRT();
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CBMview::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

void CBMview::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void CBMview::OnSize(UINT nType, int cx, int cy) 
{
	CRect rcBounds,rect1,rect2;
	CDialog::OnSize(nType, cx, cy);

	if(HaveCreate!=0)
	{
		if(nType == 2) 
		{
			this->MoveWindow(MaxRect,true); ;
		}
		ShowModeChange(ModeShow);
		/*
		this->GetClientRect(rcBounds);
		
		rect1 = rcBounds;
		rect1.bottom=rect1.bottom/2;
		rect1.right = rect1.right -110;


		rect2 = rcBounds;
		rect2.top=rect2.bottom/2;
		rect2.right = rect2.right -110;

		m_SendMessagelist.MoveWindow(rect1,true);
		m_GetMessagelist.MoveWindow(rect2,true);

		rect1 = rcBounds;
		rect1.left = rect1.right -  90-5;
		rect1.right = rect1.right - 5;

		rect1.top = rect1.top + 1;
		rect1.bottom = rect1.bottom - 5; 
		GetDlgItem(IDC_STATICNA)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 80-10;
		rect1.right = rect1.right - 10;

		rect1.top = rect1.top + 40;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_BUTTON1)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 80-10;
		rect1.right = rect1.right - 10;

		rect1.top = rect1.top + 80;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_BUTTON2)->MoveWindow(rect1,true);


		rect1 = rcBounds;
		rect1.left = rect1.right - 80-10;
		rect1.right = rect1.right -10;

		rect1.top = rect1.top + 120;
		rect1.bottom = rect1.top + 50; 
		GetDlgItem(IDC_BUTTON3)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 100-10;
		rect1.right = rect1.right - 85-10;

		rect1.top = rect1.bottom/2 -50;
		rect1.bottom = rect1.top + 50; 
		GetDlgItem(IDC_BUTTON4)->MoveWindow(rect1,true);
		*/
		
	}
	HaveCreate = 1;
	// TODO: Add your message handler code here
	
}

void CBMview::OnSaveData() 
{
	// TODO: Add your control notification handler code here

	CString FileName,FilePathName,writestr;
	int i,j;
	char writeVale[40];
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	if(m_pMainWnd->BM_GetFlag==false)
	{
		CFileDialog FileSave( false,NULL,"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
		if(FileSave.DoModal()==IDOK )
		{
			FileName=FileSave.GetPathName();
			CopyFile("C:\\MessageTemp.dat",FileName,false );
			MessageBox("保存完成","提示");
			///存发送数据
	/*
			writestr.Format("%2d",m_GetMessagelist.GetItemCount());
			WritePrivateProfileString("SectionGetData","All_Count",writestr,FileName);
			for(i=0;i<m_GetMessagelist.GetItemCount();i++)
			{
				
				for(j=0;j<37;j++)
				{
					m_GetMessagelist.GetItemText(i,j,writeVale,40);
					writestr.Format("value%2d%2d",i,j);
					WritePrivateProfileString("SectionGetData",writestr,writeVale,FileName);
				}
				
			}
	*/

		}

	}
	else
	{
		MessageBox("数据接收中,不能保存数据，\n请先停止接收再保存");
	}
}

void CBMview::OnReadData() 
{
	// TODO: Add your control notification handler code here

	//strwrite.Format("%d",firstTime);
		//::CreateThread(ReadDataFuncThre,s_hWnd,THREAD_PRIORITY_ABOVE_NORMAL);	
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	firstflag = true;
	ReadDataFlag = true;
	CountiuFlag = true;
	GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW	);
	GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);

	m_pMainWnd->BM_NoGetData();
	m_Get.SetWindowText("继续接收");

	GetDlgItem(IDC_BUTTON22)->EnableWindow(false	);
	GetDlgItem(IDC_BUTTON5)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false	);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(false);


	Thread =  ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ReadDataFuncThre,this,0,&ThreadID);
	
	//ReadDataFunc() ;
		
}

UINT CBMview::ReadDataFuncThre(LPVOID lpV)
{

//	ReadDataFunc() ;

	CString FileName,FilePathName,writestr,strwrite;
	int i,j,MessageCountRead;
	int temp ;
	char writeVale[100];
	CFileFind FF;
	CFileException e;
	int find ;
	int iCount_Static;
	int firstTime;

	CFile FileRead;
	//Message_DataType GetData;	

	API_BM_MBUF Messagedata;

	CBMview *m_now_Handle = (CBMview*)lpV;



	CFileDialog FileSave( true,NULL,"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
	if(FileSave.DoModal()==IDOK )
	{
		FileName=FileSave.GetPathName();
		//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileNameNowWorkSave = FileName;
		m_now_Handle->m_GetMessagelist.DeleteAllItems();
		
		FileRead.Open(FileName,CFile::modeRead|CFile::shareDenyNone  , &e);
		find = FileRead.Read(&firstTime,sizeof(int));
		//strwrite.Format("%d",firstTime);
		iCount_Static = 0;
		while((find>0)&&(m_now_Handle->ReadDataFlag))
		{
			if(m_now_Handle->CountiuFlag)
			{
			
				//for(iCount_Static=0;iCount_Static<MessageCountRead;iCount_Static++)
				
				iCount_Static++;
				find = FileRead.Read(&Messagedata,sizeof(API_BM_MBUF));
				if(find==sizeof(API_BM_MBUF))
				{
					m_now_Handle->ShowReadData(Messagedata,firstTime);

					strwrite.Format("数据总数:%d",iCount_Static);
					m_now_Handle->SetDlgItemText(IDC_GETCOUNT,strwrite);
					
				}
			}
		}
		FileRead.Close();
	}
	

	//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetRedraw(true);

	m_now_Handle->GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE	);
	m_now_Handle->GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);
	m_now_Handle->GetDlgItem(IDC_BUTTON22)->EnableWindow(true	);
	m_now_Handle->GetDlgItem(IDC_BUTTON5)->EnableWindow(true);
	m_now_Handle->GetDlgItem(IDC_BUTTON1)->EnableWindow(true	);
	m_now_Handle->GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	m_now_Handle->GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	::AfxEndThread(0);
	return 0;
}

void CBMview::ReadDataFunc() 
{
		CString FileName,FilePathName,writestr,strwrite;
	int i,j,MessageCountRead;
	int temp ;
	char writeVale[100];
	CFileFind FF;
	CFileException e;
	int find ;
	int iCount_Static;
	int firstTime;

	//Message_DataType GetData;	

	API_BM_MBUF Messagedata;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();


	CFileDialog FileSave( true,NULL,"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
	if(FileSave.DoModal()==IDOK )
	{
		FileName=FileSave.GetPathName();
		//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileNameNowWorkSave = FileName;
		m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.DeleteAllItems();
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.Close();
		find = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.Open(FileName,CFile::modeRead|CFile::shareDenyNone  , &e);
		find = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.Read(&firstTime,sizeof(int));
		//strwrite.Format("%d",firstTime);
		iCount_Static = 0;
		while((find>0)&&(m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].ReadDataFlag))
		{
			if(m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].CountiuFlag)
			{
			
				//for(iCount_Static=0;iCount_Static<MessageCountRead;iCount_Static++)
				
				iCount_Static++;
				find = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.Read(&Messagedata,sizeof(API_BM_MBUF));
				if(find==sizeof(API_BM_MBUF))
				{
					m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].ShowReadData(Messagedata,firstTime);

					strwrite.Format("数据总数:%d",iCount_Static);
					m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].SetDlgItemText(IDC_GETCOUNT,strwrite);
					
				}
			}
		}
	
	}
}
CString CBMview::InttoTimerStr_1(unsigned int val)
{
   CString retrundata;
   int i;
   
   int hour,minu,second,msecond,usecond,usecondvl;
	

   usecondvl =  val %10;
   usecond =  (val /1) % 1000;
   
   
   msecond =  (val /1000) %1000;
   second =  (val /1000000)%60 ;
	minu  = (val /60000000)%60;
	hour =  (val /(60000000*60))%60; 
	retrundata.Format("%2d:%2d:%2d:-%3d:%3d",	hour,minu,second,msecond,usecond);
	for(i=0;i<retrundata.GetLength();i++)
	{
		if(retrundata.GetAt(i)==' ') retrundata.SetAt(i,'0');
	}
	return retrundata;
	
}

void CBMview::ShowReadData(API_BM_MBUF Messagedata,int firstTime)
{
	int i,j,k,NowCount,ShowCount,InsertCount;
	CString str;
	WORD valefef;

	InsertCount =  m_GetMessagelist.GetItemCount();
	 m_GetMessagelist.InsertItem(InsertCount,0);
	 m_GetMessagelist.EnsureVisible( InsertCount, true );

	str.Format("%2d",Messagedata.messno);
	 m_GetMessagelist.SetItemText(InsertCount,1,str);

	if(Messagedata.status_c1==1)
		str.Format("%s","BC->RT");
	else if(Messagedata.status_c1==2)
		str.Format("%s","RT->BC");
	else if(Messagedata.status_c1==3)
		str.Format("%s","RT->RT");
	else str.Format("%s","MODE");

	 m_GetMessagelist.SetItemText(InsertCount,2,str);

	if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
	{
	  str.Format("%s","消息无响应错误");//消息状态
	}
	else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
	{
	  str.Format("%s","状态响应时间超时错误");
	}
	else  str.Format("%s","正常");
	 m_GetMessagelist.SetItemText(InsertCount,3,str);

	str.Format("%d",Messagedata.response1.time);
	 m_GetMessagelist.SetItemText(InsertCount,4,str);

	str =   InttoTimerStr_1(Messagedata.time.microseconds-firstTime);
	 m_GetMessagelist.SetItemText(InsertCount,5,str);

	

	if(Messagedata.status_c1==3)//RT->RT 
	{
		str.Format("%2d<-%2d",Messagedata.command1.rtaddr,Messagedata.command2.rtaddr);
		 m_GetMessagelist.SetItemText(InsertCount,6,str);

		str.Format("%2d<-%2d",Messagedata.command1.subaddr,Messagedata.command2.subaddr);
		 m_GetMessagelist.SetItemText(InsertCount,7,str);
	}
	else
	{
		str.Format("%2d",Messagedata.command1.rtaddr);
		 m_GetMessagelist.SetItemText(InsertCount,6,str);

		str.Format("%2d",Messagedata.command1.subaddr);
		 m_GetMessagelist.SetItemText(InsertCount,7,str);
	}


			
	if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
		str.Format("%s","B通道");//通道 
	if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
			str.Format("%s","A通道");//通道
	 m_GetMessagelist.SetItemText(InsertCount,8,str);

	
	if(Messagedata.status_c1==3)//RT->RT 
	{

		if(Messagedata.command2.wcount==0) ShowCount = 32;
		else  ShowCount= Messagedata.command2.wcount;
	}
	else
	{
		if(Messagedata.command1.wcount==0) ShowCount = 32;
		else  ShowCount= Messagedata.command1.wcount;
	}

	str.Format("%2d",ShowCount);
	 m_GetMessagelist.SetItemText(InsertCount,9,str);
	

	//memcpy(&valefef,&Messagedata.status1,sizeof(short));
	//valefef = MessageData1553[m_channelshow].Stutas1553ToInt(Messagedata.status1);
	memcpy(&valefef,&Messagedata.status1,sizeof(short));
	str.Format("%4X",valefef);
	for(k=0;k<4;k++) 
	{
		if(str.GetAt(k)==' ') str.SetAt(k,'0');
	}
	 m_GetMessagelist.SetItemText(InsertCount,10,str);

	if(Messagedata.status_c1>3) ShowCount = 32;
	for(j=0;j<ShowCount;j++)
	{
		str.Format("0X:%4X",Messagedata.value[j]);
		for(k=3;k<7;k++) 
		{
			if(str.GetAt(k)==' ') str.SetAt(k,'0');
		}
		 m_GetMessagelist.SetItemText(InsertCount,11+j,str);
	}
}
/*
void CBMview::ReadDataFunc() 
{
		CString FileName,FilePathName,writestr,strwrite;
	int i,j,MessageCountRead;
	int temp ;
	char writeVale[100];
	CFileFind FF;
	CFileException e;
	int find ,filesize;
	int iCount_Static;
	CString str;

	Message_DataType GetData;	
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	API_BM_MBUF Messagedata;

	CFileDialog FileSave( true,NULL,"*.dat",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
	if(FileSave.DoModal()==IDOK )
	{
		FileName=FileSave.GetPathName();
		//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileNameNowWorkSave = FileName;
		m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.DeleteAllItems();
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.Close();
		find = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.Open(FileName,CFile::modeRead|CFile::shareDenyNone  , &e);
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.SeekToBegin( );
		filesize = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.SeekToEnd( );
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.SeekToBegin( );
		find = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.Read(&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].firstTime,sizeof(int));
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowType==0;

		//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetRedraw(FALSE); 
		//strwrite.Format("%d",firstTime);
		iCount_Static = 0;
		iCount_Static = (filesize-sizeof(int))/sizeof(API_BM_MBUF);

		i = 0;
		
		//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemCount(540);
		//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(540,"");

		if(find==4)
		while((i<iCount_Static)&&(m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].ReadDataFlag))
		{
			if(m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].CountiuFlag)
			{
				i++;
				//m_pMainWnd->GetData.flag[0] = true;
				//m_pMainWnd->GetData.MessageUnmber = 1;
				//m_pMainWnd->ShowMessageData();
				if(m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].firstflag)
				{
					m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].read_firstTime = Messagedata.time.microseconds;
					m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].firstflag = false;
				}
				m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,"");
				strwrite.Format("数据总数:%d;%.1f%c",i,float(i*100.0/iCount_Static),'%');
				m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].SetDlgItemText(IDC_GETCOUNT,strwrite);	
			}
		}
	}
}*/
CString CBMview::InttoTimerStr(static unsigned int val)
{
   CString retrundata;
   int i;
   int hour,minu,second,msecond,usecond,usecondvl;

   usecondvl =  val %10;
   usecond =  (val /1) % 1000;
      
   msecond =  (val /1000) %1000;
   second =  (val /1000000)%60 ;
	minu  = (val /60000000)%60;
	hour =  (val /(60000000*60))%60; 
	retrundata.Format("%2d:%2d:%2d:-%3d:%3d",	hour,minu,second,msecond,usecond);
	for(i=0;i<retrundata.GetLength();i++)
	{
		if(retrundata.GetAt(i)==' ') retrundata.SetAt(i,'0');
	}
	return retrundata;
	
}

void CBMview::ShowMessageData(CBMview* m,API_BM_MBUF Messagedata)
{
	int i,j,k,NowCount,ShowCount;
	CString str;
	short valefef;

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	//if(GetData.MessageUnmber>0)
	{
		if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowType==1)
		{
			//for(i=0;i<GetData.MessageUnmber;i++)  
			{ 
			///	if((CheckFiltration(Messagedata))&&((GetData.flag[i]==true)&&(BMView.Exce_Flag[Messagedata.command1.rtaddr][Messagedata.command1.subaddr])))//过滤条件
				{
					if(Messagedata.status_c1==1)   //BC->RT
					{
						//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","BC->RT");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);


						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

								
						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);

						for(j=0;j<ShowCount;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,10+j,str);
						}

					}
					else if(Messagedata.status_c1==2)   //RT->BC
					{

						//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","RT->BC");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);

						for(j=0;j<ShowCount;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,10+j,str);
						}
					}
					else if(Messagedata.status_c1==3)   //RT->RT
					{
						//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","RT->RT");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("1:%2d;2:%2d;",Messagedata.command1.rtaddr,Messagedata.command2.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("1:%2d;2:%2d;",Messagedata.command1.subaddr,Messagedata.command2.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);


						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);

						for(j=0;j<ShowCount;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,10+j,str);
						}
					}
					else if(Messagedata.status_c1==4)   //Non_Broadcast_Mode_With_Data_Recv
					{
						//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","Non_Broadcast_Mode_With_Data_Recv");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);

						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,10+j,str);
						}
					}
					else if(Messagedata.status_c1==5)   //Non_Broadcast_Mode_With_Data_Send
					{
						//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(i,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","Non_Broadcast_Mode_With_Data_Send");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);

						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,10+j,str);
						}
					}
					else if(Messagedata.status_c1==6)   //Non_Broadcast_Mode_Non_Data
					{
						//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","Non_Broadcast_Mode_Non_Data");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);

						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,10+j,str);
						}
					}
					else if(Messagedata.status_c1==7)   //Broadcast_BC_To_RT
					{
					//	m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","Broadcast_BC_To_RT");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);


						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);

						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,10+j,str);
						}
					}
					else if(Messagedata.status_c1==8)   //Broadcast_RT_To_RT
					{
						//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","Broadcast_RT_To_RT");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);
						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("1:%2d;2:%2d;",Messagedata.command1.rtaddr,Messagedata.command2.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("1:%2d;2:%2d;",Messagedata.command1.subaddr,Messagedata.command2.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);
						
						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
					else if(Messagedata.status_c1==9)   //Broadcast_Mode_With_Data_Recv
					{
					//	m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","Broadcast_Mode_With_Data_Recv");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);
						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);
						
						for(j=0;j<Messagedata.command1.wcount;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,10+j,str);
						}
					}
					else if(Messagedata.status_c1==10)   //Broadcast_Mode_Non_Data
					{
						//m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,0,str);

						str.Format("%s","Broadcast_Mode_Non_Data");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,7,str);

						
						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,9,str);
						
						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(i,10+j,str);
						}
					}
				}
				
			}
		}
	}
	
	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowType==0)
	{
		//GetData = MessageData1553.GetMessageData(0);	
///		if(GetData.MessageUnmber>0)
		{
			
	//		for(i=0;i<GetData.MessageUnmber;i++)  
			{ 
//				if((CheckFiltration(Messagedata))&&((BMView.Exce_Flag[Messagedata.command1.rtaddr][Messagedata.command1.subaddr])))//过滤条件
				{
					if(Messagedata.status_c1==1)   //BC->RT
					{
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","BC->RT");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

								
						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);

						
						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);
						

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);

						for(j=0;j<ShowCount;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}

					}
					else if(Messagedata.status_c1==2)   //RT->BC
					{

						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","RT->BC");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);


						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);

						for(j=0;j<ShowCount;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
					else if(Messagedata.status_c1==3)   //RT->RT
					{
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","RT->RT");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("1:%2d;2:%2d;",Messagedata.command1.rtaddr,Messagedata.command2.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("1:%2d;2:%2d;",Messagedata.command1.subaddr,Messagedata.command2.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);

						for(j=0;j<ShowCount;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
					else if(Messagedata.status_c1==4)   //Non_Broadcast_Mode_With_Data_Recv
					{
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","MODE");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);

						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
					else if(Messagedata.status_c1==5)   //Non_Broadcast_Mode_With_Data_Send
					{
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","Non_Broadcast_Mode_With_Data_Send");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);

						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
					else if(Messagedata.status_c1==6)   //Non_Broadcast_Mode_Non_Data
					{
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","Non_Broadcast_Mode_Non_Data");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);

				
						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);
						
						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
					else if(Messagedata.status_c1==7)   //Broadcast_BC_To_RT
					{
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","Broadcast_BC_To_RT");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);


						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);

						
						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);
						
						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
					else if(Messagedata.status_c1==8)   //Broadcast_RT_To_RT
					{
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","Broadcast_RT_To_RT");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);
						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("1:%2d;2:%2d;",Messagedata.command1.rtaddr,Messagedata.command2.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("1:%2d;2:%2d;",Messagedata.command1.subaddr,Messagedata.command2.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);

						
						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);
						
						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
					else if(Messagedata.status_c1==9)   //Broadcast_Mode_With_Data_Recv
					{
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","Broadcast_Mode_With_Data_Recv");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);
						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);

						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);
						
						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
					else if(Messagedata.status_c1==10)   //Broadcast_Mode_Non_Data
					{
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.InsertItem(0,0);

						str.Format("%2d",Messagedata.messno);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,0,str);

						str.Format("%s","Broadcast_Mode_Non_Data");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,1,str);

						if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
						{
						  str.Format("%s","消息无响应错误");//消息状态
						}
						else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
						{
						  str.Format("%s","状态响应时间超时错误");
						}
						else  str.Format("%s","正常");
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,2,str);

						str.Format("%d",Messagedata.response1.time);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,3,str);

						str =   m->InttoTimerStr(Messagedata.time.microseconds -  m->read_firstTime);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,4,str);

						str.Format("%2d",Messagedata.command1.rtaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,5,str);

						str.Format("%2d",Messagedata.command1.subaddr);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,6,str);

						if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
							str.Format("%s","B通道");//通道 
						if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
								str.Format("%s","A通道");//通道
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,7,str);

						if(Messagedata.command1.wcount==0) ShowCount = 32;
						else  ShowCount= Messagedata.command1.wcount;

						str.Format("%2d",ShowCount);
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,8,str);
						
						memcpy(&valefef,&Messagedata.status1,sizeof(short));
						str.Format("%4X",valefef);
						for(k=0;k<4;k++) 
						{
							if(str.GetAt(k)==' ') str.SetAt(k,'0');
						}
						m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,9,str);
							
						
						for(j=0;j<32;j++)
						{
							str.Format("0X:%4X",Messagedata.value[j]);
							for(k=3;k<7;k++) 
							{
								if(str.GetAt(k)==' ') str.SetAt(k,'0');
							}
							m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.SetItemText(0,10+j,str);
						}
					}
				}
				
			}
		}
	}
}

void CBMview::OnShowMode() 
{
	// TODO: Add your control notification handler code here
	

	ModeShow=!ModeShow;
	ShowModeChange(ModeShow);	
	
}

void CBMview::ShowModeChange(bool mode)
{
	CRect rcBounds,rect1,rect2;
	if(mode==true)
	{
		this->GetClientRect(rcBounds);
		
		rect1 = rcBounds;
		rect1.right = rect1.right -120;
		m_GetMessagelist.MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right -  105-5;
		rect1.right = rect1.right - 5;

		rect1.top = rect1.top + 1;
		rect1.bottom = rect1.bottom - 5; 
		GetDlgItem(IDC_STATICNA)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right - 10;

		rect1.top = rect1.top + 15;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_BUTTON1)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right - 10;

		rect1.top = rect1.top + 50;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_BUTTON2)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = (rect1.right - 10 - (rect1.right - 80-10))/2+(rect1.right - 80-10);

		rect1.top = rect1.top + 75;
		rect1.bottom = rect1.top + 20; 
		GetDlgItem(IDC_BUTTON6)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = (rect1.right - 10 - (rect1.right - 80-10))/2+(rect1.right - 80-10);
		rect1.right = rect1.right - 10;

		rect1.top = rect1.top + 75;
		rect1.bottom = rect1.top + 20; 
		GetDlgItem(IDC_BUTTON7)->MoveWindow(rect1,true);


		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right - 10;

		rect1.top = rect1.top + 110;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_BUTTON5)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right -10;

		rect1.top = rect1.top + 140;
		rect1.bottom = rect1.top + 40; 
		GetDlgItem(IDC_BUTTON3)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right -10;

		rect1.top = rect1.top + 185;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_BUTTON22)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right -10;

		rect1.top = rect1.top + 215;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_BUTTON8)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right -10;

		rect1.top = rect1.top + 245;
		rect1.bottom = rect1.top + 30; 
		GetDlgItem(IDC_CHECK1)->MoveWindow(rect1,true);

		

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right -10;

		rect1.top = rect1.top + 280;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_GETCOUNT)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right -10;

		rect1.top = rect1.top + 320;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_BUTTON9)->MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 95-10;
		rect1.right = rect1.right -10;

		rect1.top = rect1.top + 360;
		rect1.bottom = rect1.top + 25; 
		GetDlgItem(IDC_EDIT1)->MoveWindow(rect1,true);



		rect1 = rcBounds;
		rect1.left = rect1.right - 120;
		rect1.right = rect1.right - 110;

		rect1.top = rect1.bottom/2 -50;
		rect1.bottom = rect1.top + 50; 
		GetDlgItem(IDC_BUTTON4)->MoveWindow(rect1,true);


		

		GetDlgItem(IDC_BUTTON1)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON2)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON3)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON5)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON22)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON8)->ShowWindow(true);
		GetDlgItem(IDC_STATICNA)->ShowWindow(true);
		GetDlgItem(IDC_CHECK1)->ShowWindow(true);
		if(ReadDataFlag)
		{
			GetDlgItem(IDC_BUTTON6)->ShowWindow(true);
			GetDlgItem(IDC_BUTTON7)->ShowWindow(true);
		}
		else
		{
			GetDlgItem(IDC_BUTTON6)->ShowWindow(false);
			GetDlgItem(IDC_BUTTON7)->ShowWindow(false);
		}

		GetDlgItem(IDC_GETCOUNT)->ShowWindow(true);
		
		GetDlgItem(IDC_BUTTON4)->SetWindowText(">");

	}
	else
	{
		this->GetClientRect(rcBounds);
		
		rect1 = rcBounds;
		rect1.bottom=rect1.bottom;
		rect1.right = rect1.right-15;

		m_GetMessagelist.MoveWindow(rect1,true);

		rect1 = rcBounds;
		rect1.left = rect1.right - 15;
		rect1.right = rect1.right;

		rect1.top = rect1.bottom/2 -50;
		rect1.bottom = rect1.top + 50; 
		GetDlgItem(IDC_BUTTON4)->MoveWindow(rect1,true);
		GetDlgItem(IDC_BUTTON4)->SetWindowText("<");

		GetDlgItem(IDC_BUTTON1)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON2)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON3)->ShowWindow(false);
		GetDlgItem(IDC_STATICNA)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON5)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON22)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON8)->ShowWindow(false);
		GetDlgItem(IDC_CHECK1)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON6)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON7)->ShowWindow(false);
		GetDlgItem(IDC_GETCOUNT)->ShowWindow(false);
	}
}
void CBMview::InitBM()
{
	m_GetMessagelist.DeleteAllItems();
	SetDlgItemText(IDC_BUTTON22,"滚动显示");
}
void CBMview::OnGetData() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();


	//DataDlg.FileNameTempSave = "C:\\MessageTemp.dat";
	if(m_pMainWnd->BM_GetFlag==true)
	{
		m_Get.SetIcon(IDI_NOGET,IDI_NOGET);
		m_Get.SetWindowText("继续接收");
		m_pMainWnd->BM_NoGetData();
	}
	else
	{
		m_Get.SetIcon(IDI_GET,IDI_GET);
		m_Get.SetWindowText("暂停接收");
		
		m_pMainWnd->BM_GetData();
	}
}
void CBMview::OnButton3() 
{
	// TODO: Add your control notification handler code here
	bool ReOpenFlag;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	CMonitorConfigDlg dlg;
	dlg.DoModal();
	if(m_pMainWnd->BM_GetFlag)
	{
		m_pMainWnd->BM_NoGetData();
		ReOpenFlag = true;
	}
	else ReOpenFlag = false;

	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowModedata.DataCountAll = 0;
	m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.DeleteAllItems();

	if (ReOpenFlag)
		m_pMainWnd->BM_GetData();
}
void CBMview::OnButtonDown() 
{
	int SelectID,AllItem;
	CString str;
	SelectID = m_GetMessagelist.GetNextItem(-1,LVNI_SELECTED );
	AllItem = m_GetMessagelist.GetItemCount();
	if(SelectID>=0)
	{
		//str = m_GetMessagelist.GetItemText(SelectID,0);
		//SelectID = atoi(str);

		//SelectID = AllItem - SelectID;
		ShowDataDlg(SelectID);
	}
}
void CBMview::OnClickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
void CBMview::ShowDataDlg(int SelID)
{
	CRect RectBm,ShowRect;
	NowPoint = m_GetMessagelist.NowPoint;
	GetCursorPos(&NowPoint);
	DataDlg.ShowVal(SelID);
	this->GetWindowRect(RectBm);

	ShowRect.left = NowPoint.x;
	ShowRect.top = NowPoint.y;
	ShowRect.right =rect.right-rect.left+NowPoint.x;
	ShowRect.bottom = rect.bottom-rect.top+NowPoint.y;

	if(((rect.right-rect.left+NowPoint.x)<RectBm.right)&&((rect.bottom-rect.top+NowPoint.y)<RectBm.bottom))
		DataDlg.MoveWindow(ShowRect,false);
	else
	{
		if((rect.right-rect.left+NowPoint.x)>RectBm.right)
		{
			ShowRect.left = RectBm.right - (rect.right-rect.left);
			ShowRect.right = RectBm.right;
		}

		if((rect.bottom-rect.top+NowPoint.y)>RectBm.bottom)
		{
			ShowRect.top = RectBm.bottom - (rect.bottom-rect.top);
			ShowRect.bottom = RectBm.bottom;
		}
		DataDlg.MoveWindow(ShowRect,false);
	}

	DataDlg.ShowWindow(SW_SHOW);
}
void CBMview::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	NowPoint = point;
	CDialog::OnMouseMove(nFlags, point);
}
void CBMview::HideDataDlg()
{
	DataDlg.ShowWindow(SW_HIDE);
}
void CBMview::OnButtonShowMode() 
{
	// TODO: Add your control notification handler code here
	int i;
	bool ReOpenFlag;
	CString str;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	if(m_pMainWnd->BM_GetFlag)
	{
		m_pMainWnd->BM_NoGetData();
		ReOpenFlag = true;
	}
	else ReOpenFlag = false;

	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowModedata.DataCountAll = 0;
	m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.DeleteAllItems();
	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowType == 1)
	{
		m_ShowMode.SetIcon(IDI_ICON6,IDI_ICON6);
		SetDlgItemText(IDC_BUTTON22,"静止显示");
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowType = 0;
		

		

	}
	else 
	{
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowType = 1;
		SetDlgItemText(IDC_BUTTON22,"滚动显示");
		m_ShowMode.SetIcon(IDI_ICON7,IDI_ICON7);

	}
	if (ReOpenFlag)
		m_pMainWnd->BM_GetData();
	
}
void CBMview::OnCheck1() 
{
	// TODO: Add your control notification handler code here

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	m_pMainWnd->TimeShowFlag = !m_pMainWnd->TimeShowFlag;
}

void CBMview::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	CString strwrite;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	m_pMainWnd->HightSpeedMode = !m_pMainWnd->HightSpeedMode;

	
}

void CBMview::OnButton6() 
{
	// TODO: Add your control notification handler code here
	if( ReadDataFlag)
	{
		CountiuFlag = !CountiuFlag;
		if(CountiuFlag) 
		{
			SetDlgItemText(IDC_BUTTON6,"暂停");
			//m_GetMessagelist.SetRedraw(false);
		}
		else 
		{
			SetDlgItemText(IDC_BUTTON6,"继续");
			//m_GetMessagelist.SetRedraw(true);
		}
	}
}

void CBMview::OnButton7() 
{
	// TODO: Add your control notification handler code here
	if( ReadDataFlag) 
	{
		CountiuFlag = false;
		ReadDataFlag = false;
		CloseHandle(Thread);
		//ExitThread(ThreadID);
	}
}

void CBMview::OnDestroy() 
{

	
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CBMview::OnGetdispinfoList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	LV_ITEM* pItem= &(pDispInfo)->item;

	int iItemIndx= pItem->iItem;
	API_BM_MBUF Messagedata;
	short valefef;

//	pItem->iSubItem = 0;
//	lstrcpy(pItem->pszText,"m_Items[iItemIndx].m_strItemText");
	
	//ShowMessageData(CBMview* m,API_BM_MBUF Messagedata)
	int i,j,k,NowCount,ShowCount;
	CString str;

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.SeekToBegin( );
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.Seek(sizeof(int)+sizeof(API_BM_MBUF)*iItemIndx,CFile::begin);

	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileRead.Read(&Messagedata,sizeof(API_BM_MBUF));
	//ShowMessageData(&m_pMainWnd->BMView,Messagedata);

	if (pItem->mask & LVIF_TEXT) //字符串缓冲区有效
	{
		switch(pItem->iSubItem){
        case 1: //填充数据项的名字

			str.Format("%2d",Messagedata.messno);
			pItem->iSubItem = 0;
			sprintf(pItem->pszText,str);
		break;

		case 2:
			if(Messagedata.status_c1==1)
				str.Format("%s","BC->RT");
			else if(Messagedata.status_c1==2)
				str.Format("%s","RT->BC");
			else if(Messagedata.status_c1==3)
				str.Format("%s","RT->RT");
			else str.Format("%s","MODE");

			pItem->iSubItem = 1;
			sprintf(pItem->pszText,str);
		break;

		case 3:
			if((Messagedata.status_c2&BT1553_VALID_STATUS1)!=BT1553_VALID_STATUS1)   //msgflag
			{
			  str.Format("%s","消息无响应错误");//消息状态
			}
			else if((Messagedata.status_c2&BT1553_LATE_RESP1)==BT1553_LATE_RESP1)   //msgflag
			{
			  str.Format("%s","状态响应时间超时错误");
			}
			else  str.Format("%s","正常");
			pItem->iSubItem = 2;
			sprintf(pItem->pszText,str);
		break;

		case 4:

			str.Format("%d",Messagedata.response1.time);
			pItem->iSubItem = 3;
			sprintf(pItem->pszText,str);
		break;

		case 5:
			str =   InttoTimerStr(Messagedata.time.microseconds -  read_firstTime);
			pItem->iSubItem = 4;
			sprintf(pItem->pszText,str);
		break;

		case 6:
			str.Format("%2d",Messagedata.command1.rtaddr);
			pItem->iSubItem = 5;
			sprintf(pItem->pszText,str);
		break;

		case 7:
			str.Format("%2d",Messagedata.command1.subaddr);
			pItem->iSubItem = 6;
			sprintf(pItem->pszText,str);
		break;

		case 8:
				
			if((Messagedata.status_c2&BT1553_IN_B_BUS)==BT1553_IN_B_BUS)
				str.Format("%s","B通道");//通道 
			if((Messagedata.status_c2&BT1553_IN_A_BUS)==BT1553_IN_A_BUS)
					str.Format("%s","A通道");//通道
			pItem->iSubItem = 7;
			sprintf(pItem->pszText,str);
		break;

		case 9:
		

			if(Messagedata.command1.wcount==0) ShowCount = 32;
			else  ShowCount= Messagedata.command1.wcount;

			str.Format("%2d",ShowCount);
			pItem->iSubItem = 8;
			sprintf(pItem->pszText,str);
		break;

		case 10:
			memcpy(&valefef,&Messagedata.status1,sizeof(short));
			str.Format("%4X",valefef);
			for(k=0;k<4;k++) 
			{
				if(str.GetAt(k)==' ') str.SetAt(k,'0');
			}
			pItem->iSubItem = 9;
			sprintf(pItem->pszText,str);
		break;

		default:
			//for(j=0;j<ShowCount;j++)
			{
				str.Format("0X:%4X",Messagedata.value[pItem->iSubItem-11]);
				for(k=3;k<7;k++) 
				{
					if(str.GetAt(k)==' ') str.SetAt(k,'0');
				}
				//pItem->iSubItem = 10+j;
				sprintf(pItem->pszText,str);
			}
			break;
		}
	}

	*pResult = 0;
}

void CBMview::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rcWnd;
	this->GetClientRect(&rcWnd);
	CBrush brush;
	brush.CreateSolidBrush(RGB(237,246,255));
	dc.FillRect(&rcWnd,&brush);
	brush.DeleteObject();
	// Do not call CDialog::OnPaint() for painting messages
}

HBRUSH CBMview::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CBMview::OnClearview() 
{
	// TODO: Add your control notification handler code here
	int i;
	bool ReOpenFlag;
	CString str;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	if(m_pMainWnd->BM_GetFlag)
	{
		m_pMainWnd->BM_NoGetData();
		ReOpenFlag = true;
	}
	else ReOpenFlag = false;

	m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].messCount = 0;
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowModedata.DataCountAll = 0;
	m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.DeleteAllItems();
	/*
	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowType == 1)
	{
		m_ShowMode.SetIcon(IDI_ICON6,IDI_ICON6);
		SetDlgItemText(IDC_BUTTON22,"静止显示");
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowType = 0;
		

		

	}
	else 
	{
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].ShowType = 1;
		SetDlgItemText(IDC_BUTTON22,"滚动显示");
		m_ShowMode.SetIcon(IDI_ICON7,IDI_ICON7);

	}*/
	if (ReOpenFlag)
		m_pMainWnd->BM_GetData();
}

void CBMview::OnButton9() 
{
	// TODO: Add your control notification handler code here
	int count = m_GetMessagelist.GetItemCount();
	CString Str;
	Str.Format("%d",count);
	SetDlgItemText(IDC_EDIT1,Str);
}
