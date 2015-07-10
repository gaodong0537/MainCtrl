// RTViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "RTViewDlg.h"
#include "MainFrm.h"
#include "RTDataSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTViewDlg dialog


CRTViewDlg::CRTViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRTViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRTViewDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRTViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRTViewDlg)
	DDX_Control(pDX, IDC_LIST1, m_RT_DataList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRTViewDlg, CDialog)
	//{{AFX_MSG_MAP(CRTViewDlg)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRTViewDlg message handlers

BOOL CRTViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_RT_DataList.ModifyStyle(LVS_EDITLABELS,0L);
	m_RT_DataList.ModifyStyle(0L,LVS_REPORT);
	m_RT_DataList.ModifyStyle(0L,LVS_SHOWSELALWAYS);
	m_RT_DataList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	LV_COLUMN lvcolumn;
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.cx = 80;
	lvcolumn.pszText = "子地址";
	m_RT_DataList.InsertColumn(0,&lvcolumn);

	int i;
	char str[20];
	for(i=0;i<32;i++)
	{
		sprintf(str,"数据%d",i);
		lvcolumn.pszText = str; 
		lvcolumn.cx = 70;
		m_RT_DataList.InsertColumn(1+i,&lvcolumn);
	}



	for(i=0;i<32;i++)SubAdressShow[i] =  false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CRTViewDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}
void CRTViewDlg::SetRTViewData(int rtadrss,int subadress,API_RT_MBUF_WRITE data,bool flag)
{
	int NowCount;
	int i,j;
	int show_flag;
	CString strshow;
	CString ShowStr2;
	char ShowStr[1000];
	show_flag=false;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();


	if(SubAdressShow[subadress]==true)
	{
			NowCount=subAdressTocount[subadress];
			show_flag=true;
	}
	if(show_flag==false)//该子地址数据没有在列表中显示
	{
		NowCount = m_RT_DataList.GetItemCount();
		subAdressTocount[subadress] = NowCount;
		if(flag)
		{
			SubAdressShow[subadress]=true;
			m_RT_DataList.InsertItem(NowCount,0);
			ShowStr2.Format("%2d",subadress);
			m_RT_DataList.SetItemText(NowCount,0,ShowStr2 );
			sprintf(ShowStr,"");
			for(j=0;j<32;j++)
			{
				ShowStr2.Format("0X%4X",data.mess_data[j]);

				for(i=0;i<6;i++)
				{
					if(ShowStr2.GetAt(i)==' ') ShowStr2.SetAt(i,'0') ;
				}
				m_RT_DataList.SetItemText(NowCount,1+j,ShowStr2 );
			}
		}
		else
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[rtadrss].VectorSetFlag = true;
			strshow.Format("0x%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[rtadrss]);
			for(i=0;i<6;i++)
			{
				if(strshow.GetAt(i)==' ') strshow.SetAt(i,'0') ;
			}
			SetDlgItemText(IDC_EDIT1,strshow);

			strshow.Format("0x%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[rtadrss].VectorWord);
			for(i=0;i<6;i++)
			{
				if(strshow.GetAt(i)==' ') strshow.SetAt(i,'0') ;
			}
			SetDlgItemText(IDC_EDIT2,strshow);
		}
	}
	else 
	{
		sprintf(ShowStr,"");
		for(j=0;j<32;j++)
		{
			ShowStr2.Format("0X%4X",data.mess_data[j]);
			for(i=0;i<6;i++)
			{
				if(ShowStr2.GetAt(i)==' ') ShowStr2.SetAt(i,'0') ;
			}
			m_RT_DataList.SetItemText(NowCount,1+j,ShowStr2 );	
		}

		SubAdressShow[subadress]=true;
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[rtadrss].VectorSetFlag = true;
		strshow.Format("0x%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[rtadrss]);
		for(i=0;i<6;i++)
		{
			if(strshow.GetAt(i)==' ') strshow.SetAt(i,'0') ;
		}
		SetDlgItemText(IDC_EDIT1,strshow);

		strshow.Format("0x%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[rtadrss].VectorWord);
		for(i=0;i<6;i++)
		{
			if(strshow.GetAt(i)==' ') strshow.SetAt(i,'0') ;
		}
		SetDlgItemText(IDC_EDIT2,strshow);
		
	}
}

void CRTViewDlg::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}

BOOL CRTViewDlg::PreTranslateMessage(MSG* pMsg) 
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

void CRTViewDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	this->ShowWindow(SW_HIDE);
	CDialog::OnClose();
}

void CRTViewDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString SeleName,CopName;
	bool FindFlag;
	int i,SelectItem,RTAdress;

	this->GetWindowText(SeleName);
	FindFlag = false;
	for(i=0;i<32;i++)
	{	
		CopName.Format("RT%2d",i);
		if(SeleName == CopName )
		{
			FindFlag = true;
			RTAdress = i;
			break;
		}
	}

	if(FindFlag==true)
	{
		SelectItem = m_RT_DataList.GetNextItem(-1,LVNI_SELECTED );
		if(SelectItem >=0)
		{
			CRTDataSet RTSetDlg;
			RTSetDlg.IniType = 1;//
			RTSetDlg.RTAdress = RTAdress;//
			RTSetDlg.vectorword = 
			RTSetDlg.SubAdress = atoi(m_RT_DataList.GetItemText(SelectItem,0));
			RTSetDlg.DoModal();
		}
		else
		{
			CRTDataSet RTSetDlg;
			RTSetDlg.IniType = 3;//
			RTSetDlg.RTAdress = RTAdress;//
			RTSetDlg.DoModal();

		}
	}
	*pResult = 0;
}

void CRTViewDlg::DeleteRT()
{
	int i;
	bool  show_flag;

	for(i=0;i<32;i++)
		SubAdressShow[i]==false;

	m_RT_DataList.DeleteAllItems();

}
