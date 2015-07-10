// DataShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "MainFrm.h"
#include "DataShowDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DataShowDlg dialog


DataShowDlg::DataShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DataShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DataShowDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DataShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DataShowDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DataShowDlg, CDialog)
	//{{AFX_MSG_MAP(DataShowDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DataShowDlg message handlers

BOOL DataShowDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

BOOL DataShowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
	GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	HINSTANCE hInst = LoadLibrary("User32.DLL"); //显式加载DLL
	if(hInst) 
	{            
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD);          
		MYFUNC fun = NULL;     
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");//取得SetLayeredWindowAttributes函数指针
		if(fun)fun(this->GetSafeHwnd(),0,1000,2);     
		FreeLibrary(hInst); 
	}

		FileNameTempSave = "C:\\MessageTemp.dat";
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
int DataShowDlg::chartoint(char val)
{
	switch (val) 
	{
	case	'0': return 0;
	case	'1': return 1;
	case	'2': return 2;
	case	'3': return 3;
	case	'4': return 4;
	case	'5': return 5;
	case	'6': return 6;
	case	'7': return 7;
	case	'8': return 8;
	case	'9': return 9;
	case	'a': return 10;
	case	'b': return 11;
	case	'c': return 12;
	case	'd': return 13;
	case	'e': return 14;
	case	'f': return 15;
	case    'A': return 10; 
	case	'B': return 11;
	case	'C': return 12;
	case	'D': return 13;
	case	'E': return 14;
	case	'F': return 15;
	default:  return 0;
	}

} 
int DataShowDlg::HexToInt(CString str,int len)
{
	int val;
	int i;
	int strlen;
	val=0;
	strlen = str.GetLength();
	if(strlen<4)
		for(i=0;i<4-strlen;i++)
			str.Insert(0,'0');
	for(i=0;i<len;i++)
	{
		val=val+chartoint(str.GetAt(i))*pow(2,(len-1-i)*4);
	}
	return val;
}
void DataShowDlg::ShowVal(int SelectID)
{
	int i,j,val1,val;
	int RTflag,busyflag,questflag,systermflag,dynaflag,broadflag,errflag,instrflag;
	API_BM_MBUF     messages; 
	CString strwrite,str,str_meid,str_mert,str_mesub;

	short tempval;

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	//FileNameTempSave = ((CMainFrame*)this->GetParent())->MessageData1553.FileNameNowWorkSave;
/*
	strwrite.Format("Value%d",SelectID);
	m_pMainWnd->MessageData1553.FileRead.Seek((SelectID+m_pMainWnd->MessageData1553.ShowLostCount-1)* sizeof(API_BM_MBUF)+sizeof(int),CFile::begin);
	m_pMainWnd->MessageData1553.FileRead.Read(&messages,sizeof(API_BM_MBUF));
*/	//GetPrivateProfileStruct("BM_GetMessage",strwrite,&messages, sizeof(API_BM_MBUF),FileNameTempSave);
	
	//BT1553_STATUS val;
	str_meid = m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.GetItemText(SelectID,1);
	str_mert = m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.GetItemText(SelectID,6);
	str_mesub = m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.GetItemText(SelectID,7);
	strwrite.Format("消息号：%s;地址：%s;子地址：%s;",str_meid,str_mert,str_mesub);
	SetDlgItemText(IDC_STATICLABLE,strwrite);

	str = m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.GetItemText(SelectID,10);
	tempval = HexToInt(str,4);
	//memcpy(&messages.status1,&tempval,sizeof(short));
	messages.status1 = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].IntToStutas1553(tempval);

	str = m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.GetItemText(SelectID,9);
	messages.command1.wcount = atoi(str);

	for(i=0;i<32;i++)
	{

		val1 = messages.value[i];

		strwrite = m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].m_GetMessagelist.GetItemText(SelectID,11+i);
		if(strwrite.GetLength()>=4+3)
		{
			str.Format("");
			for(j=0;j<4;j++) 
			{
				 str.Insert(j,strwrite.GetAt(j+3));
			}
		
			SetDlgItemText(IDC_EDIT18+i,str);
		}
		((CButton*)(GetDlgItem(IDC_EDIT18+i)))->EnableWindow(true);
	}
	if(messages.command1.wcount!=0) 
	for(i=messages.command1.wcount;i<32;i++) 
		((CButton*)(GetDlgItem(IDC_EDIT18+i)))->EnableWindow(false);

	//val = messages.status1;

	if(messages.status1.tf)
		RTflag = true;
	else RTflag= false;
	
	if(messages.status1.busy)
		busyflag = true;
	else busyflag= false;
	
	if(messages.status1.sr)
		questflag = true;
	else questflag= false;
	
	if(messages.status1.sf)
		systermflag = true;
	else systermflag= false;

	if(messages.status1.dba)
		dynaflag = true;
	else dynaflag= false;

	if(messages.status1.bcr)
		broadflag = true;
	else broadflag= false;
	
	if(messages.status1.me)
		errflag = true;
	else errflag= false;

	if(messages.status1.inst)
		instrflag = true;
	else instrflag= false;

	/*
	messages.status1.me);//消息差错
	messages.status1.sr);//服务请求
	messages.status1.sf);//子系统标志
	messages.status1.tf);//终端标志:
	messages.status1.busy);//忙:
	messages.status1.dba);//动态总线控制接收
	messages.status1.bcr);//广播指令接收
	messages.status1.inst);//测试手段
*/

	((CButton *)GetDlgItem(IDC_RTBIT))->SetCheck(RTflag);

	((CButton *)GetDlgItem(IDC_BUSYBIT))->SetCheck(busyflag);

	((CButton *)GetDlgItem(IDC_SEVERBIT))->SetCheck(questflag);

	((CButton *)GetDlgItem(IDC_SYSTMBIT))->SetCheck(systermflag);

	((CButton *)GetDlgItem(IDC_SYNOBIT))->SetCheck(dynaflag);

	((CButton *)GetDlgItem(IDC_BOARDBIT))->SetCheck(broadflag);
	((CButton *)GetDlgItem(IDC_ERRBIT))->SetCheck(errflag);

	((CButton *)GetDlgItem(IDC_INSTRBIT))->SetCheck(instrflag);
	
} 
