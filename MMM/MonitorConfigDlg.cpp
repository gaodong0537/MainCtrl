// MonitorConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "MonitorConfigDlg.h"
#include "MainFrm.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMonitorConfigDlg dialog


CMonitorConfigDlg::CMonitorConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonitorConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMonitorConfigDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMonitorConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonitorConfigDlg)
	DDX_Control(pDX, IDC_LIST2, m_StutasList);
	DDX_Control(pDX, IDC_LIST3, m_VectorList);
	DDX_Control(pDX, IDC_LIST1, m_FileCondtionList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMonitorConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CMonitorConfigDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_BUTTON15, OnButton15)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON16, OnButton16)
	ON_BN_CLICKED(IDC_BUTTON17, OnButtonADD)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON18, OnButtonDelete)
	ON_BN_CLICKED(IDC_CHECK59, OnCheck59)
	ON_BN_CLICKED(IDC_BUTTON122, OnButton122)
	ON_BN_CLICKED(IDC_BUTTON123, OnButton123)
	ON_BN_CLICKED(IDC_BUTTON124, OnButton124)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON22, OnButton22)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_CHECK68, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK69, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK70, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK71, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK72, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK73, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK74, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK75, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK76, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK77, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK78, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK79, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK80, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK81, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK82, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK83, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK84, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK85, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK86, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK87, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK88, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK89, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK90, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK91, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK92, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK93, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK94, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK95, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK96, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK97, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK98, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK99, OnCheck1)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMonitorConfigDlg message handlers

BEGIN_EVENTSINK_MAP(CMonitorConfigDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CMonitorConfigDlg)
	
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void CMonitorConfigDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here

	int i,NowSelectRT;
	CString str;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	NowSelectRT = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	for(i=0;i<32;i++)
	{
		((CButton*)GetDlgItem(IDC_CHECK68+i))->	SetCheck(m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag[NowSelectRT][i]);
	}
	str.Format("RT%d数据全显示",NowSelectRT);
	SetDlgItemText(IDC_BUTTON7,str);
	str.Format("RT%d数据全过滤",NowSelectRT);
	SetDlgItemText(IDC_BUTTON8,str);

}

BOOL CMonitorConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int i,k,NowSelectRT;
	CString str;
	for(i=0;i<32;i++)
	{
		str.Format("RT%2d",i);	
		((CComboBox*)GetDlgItem(IDC_COMBO1))->InsertString(i,str);
		str.Format("%2d",i);
		((CComboBox*)GetDlgItem(IDC_COMBO2))->InsertString(i,str);
		str.Format("%2d",i);
		((CComboBox*)GetDlgItem(IDC_COMBO3))->InsertString(i,str);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO2))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO3))->SetCurSel(0);
	GetDlgItem(IDC_BUTTON14)->EnableWindow(false);

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	NowSelectRT = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	for(i=0;i<32;i++)
	{
		
		((CButton*)GetDlgItem(IDC_CHECK68+i))->	SetCheck(m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag[NowSelectRT][i]);
	}

	for(NowSelectRT=0;NowSelectRT<32;NowSelectRT++)
	{
		for(i=0;i<32;i++)
		{
			NowFlag[NowSelectRT][i] = m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag[NowSelectRT][i] ;
		}
	}

	LV_COLUMN lvcolumn;
	m_FileCondtionList.ModifyStyle(LVS_EDITLABELS,0L);
	m_FileCondtionList.ModifyStyle(0L,LVS_REPORT);
	m_FileCondtionList.ModifyStyle(0L,LVS_SHOWSELALWAYS);
	m_FileCondtionList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.cx = 80;
	lvcolumn.pszText = "地址";
	m_FileCondtionList.InsertColumn(0,&lvcolumn);
	lvcolumn.cx = 80;
	lvcolumn.pszText = "子地址";
	m_FileCondtionList.InsertColumn(1,&lvcolumn);
	lvcolumn.cx = 110;
	lvcolumn.pszText = "保存标记";
	m_FileCondtionList.InsertColumn(2,&lvcolumn);
	lvcolumn.cx = 480;
	lvcolumn.pszText = "保存文件目录";
	m_FileCondtionList.InsertColumn(3,&lvcolumn);


	
	m_StutasList.ModifyStyle(LVS_EDITLABELS,0L);
	m_StutasList.ModifyStyle(0L,LVS_REPORT);
	m_StutasList.ModifyStyle(0L,LVS_SHOWSELALWAYS);
	m_StutasList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.cx = 110;
	lvcolumn.pszText = "状态字过滤值";
	m_StutasList.InsertColumn(0,&lvcolumn);


	m_VectorList.ModifyStyle(LVS_EDITLABELS,0L);
	m_VectorList.ModifyStyle(0L,LVS_REPORT);
	m_VectorList.ModifyStyle(0L,LVS_SHOWSELALWAYS);
	m_VectorList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.cx = 110;
	lvcolumn.pszText = "矢量字过滤值";
	m_VectorList.InsertColumn(0,&lvcolumn);

	SetDlgItemText(IDC_EDIT1,"000A");
	SetDlgItemText(IDC_EDIT2,"000A");

	OnSelchangeCombo1() ;

	for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[256];i++)
	{
		str.Format("%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[i]);
		for(k=0;k<4;k++) 
				if(str.GetAt(k)==' ') str.SetAt(k,'0');
		m_StutasList.InsertItem(i,str);
	}

	for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[256];i++)
	{
		str.Format("%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[i]);
		for(k=0;k<4;k++) 
				if(str.GetAt(k)==' ') str.SetAt(k,'0');
		m_VectorList.InsertItem(i,str);
	}
	//SetTimer(0,200,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMonitorConfigDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	
	CDialog::OnTimer(nIDEvent);
}





void CMonitorConfigDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString FileName,str,writestr;
	int i,k,NowSelectRT;
	CFileException e;
	char GetBuff[600];

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	CFileDialog FileSave( true,NULL,"*.BM",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ".BM", NULL );
	if(FileSave.DoModal()==IDOK )
	{
		FileName=FileSave.GetPathName();///读
		GetPrivateProfileStruct("BM_Config","Value",&NowFlag, sizeof(bool)*32*32,FileName);
		GetPrivateProfileStruct("BM_Config","Value",&m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag, sizeof(bool)*32*32,FileName);

		GetPrivateProfileStruct("BM_Config","Value_Stutas",&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas, sizeof(int)*257,FileName);
		GetPrivateProfileStruct("BM_Config","Value_Vectors",&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector, sizeof(int)*257,FileName);
		
		m_StutasList.DeleteAllItems();
		for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[256];i++)
		{
			str.Format("%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[i]);
			for(k=0;k<4;k++) 
				if(str.GetAt(k)==' ') str.SetAt(k,'0');
			m_StutasList.InsertItem(i,str);
		}

		m_VectorList.DeleteAllItems();
		for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[256];i++)
		{
			str.Format("%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[i]);
			for(k=0;k<4;k++) 
				if(str.GetAt(k)==' ') str.SetAt(k,'0');
			m_VectorList.InsertItem(i,str);
		}

		NowSelectRT = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
		for(i=0;i<32;i++)
		{
			((CButton*)GetDlgItem(IDC_CHECK68+i))->	SetCheck(NowFlag[NowSelectRT][i]);
		}
		
		GetPrivateProfileStruct("BM_Config","Value2",&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion, sizeof(SaveMessageFileType),FileName);
		
		m_FileCondtionList.DeleteAllItems();
		for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.NowConditcount;i++)
		{
	
			writestr.Format("FileName%d",i);
 			GetPrivateProfileString("BM_Config",writestr,"",GetBuff,600,FileName);
			str.Format(GetBuff);
			//memcpy(&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].FileName,&str,str.GetLength());
			//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].FileName=str;
			//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].FileID=NULL;
			//ADDCondtion(i,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].Adress,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].SubAdress,str);
		/*	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].FileID.Open(str,CFile::modeWrite, &e ))
			{
				m_FileCondtionList.InsertItem(i,"");
				str.Format("%d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].Adress);
				m_FileCondtionList.SetItemText(i,0,str);
				str.Format("%d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].SubAdress);
				m_FileCondtionList.SetItemText(i,1,str);
				if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].SaveFlag)
					m_FileCondtionList.SetItemText(i,2,"保存");
				else	m_FileCondtionList.SetItemText(i,2,"不保存");
				
				m_FileCondtionList.SetItemText(i,3,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].FileName);
			}
			*/
		}
	}
}

void CMonitorConfigDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CString FileName,writestr;
	int i;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	CFileDialog FileSave( false,NULL,"*.BM",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
	if(FileSave.DoModal()==IDOK )
	{
		FileName=FileSave.GetPathName();///存
		WritePrivateProfileStruct("BM_Config","Value",&NowFlag, sizeof(bool)*32*32,FileName);
		WritePrivateProfileStruct("BM_Config","Value_Stutas",&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas, sizeof(int)*257,FileName);
		WritePrivateProfileStruct("BM_Config","Value_Vectors",&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector, sizeof(int)*257,FileName);

		WritePrivateProfileStruct("BM_Config","Value2",&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion, sizeof(SaveMessageFileType),FileName);
		for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.NowConditcount;i++)
		{
			writestr.Format("FileName%d",i);
			WritePrivateProfileString("BM_Config",writestr,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].FileName,FileName);
			
		}
	}
}




void CMonitorConfigDlg::OnButton14() 
{
	// TODO: Add your control notification handler code here
	int i,NowSelectRT;

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	NowSelectRT = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	for(NowSelectRT=0;NowSelectRT<32;NowSelectRT++)
	{
		for(i=0;i<32;i++)
		{
			m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag[NowSelectRT][i] = NowFlag[NowSelectRT][i];
		}
	}
	GetDlgItem(IDC_BUTTON14)->EnableWindow(false);
}

void CMonitorConfigDlg::OnButton15() 
{
	// TODO: Add your control notification handler code here
	int i,NowSelectRT;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	NowSelectRT = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();

	for(i=0;i<32;i++)
	{
		m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag[NowSelectRT][i] = ((CButton*)GetDlgItem(IDC_CHECK68+i))->GetCheck();

	}

}

void CMonitorConfigDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	OnButton15();
}

void CMonitorConfigDlg::OnButton16() 
{
	// TODO: Add your control notification handler code here
	CString FileName,FilePathName,writestr;
	int i,j;


	CFileDialog FileSave( true,NULL,"*.txt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL );
	if(FileSave.DoModal()==IDOK )
	{
		FileName=FileSave.GetPathName();
		SetDlgItemText(IDC_EDIT6,FileName);
	}
}
void CMonitorConfigDlg::ADDCondtion(int addCondID,int Adress,int SubAdress,CString FileName) 
{
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	int i;
	CFile FileID;
	bool AddFlag;
	CString str;
	CFileException e;

	if(FileID .Open(FileName,CFile::modeCreate | CFile::modeWrite, &e ))
	//if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[addCondID].FileID = FileID)
	{
		AddFlag = true;
		for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.NowConditcount;i++)
		{
			if((Adress==m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].Adress)&&(SubAdress == m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].SubAdress))
			{
				AddFlag = false;
				MessageBox("该地址，子地址的保存文件\n已设置，不能添加","提示");
				break;
			}
		}
		if(AddFlag)
		for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.NowConditcount;i++)
		{
			if(FileName==m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i].FileName)
			{
				AddFlag = false;
				MessageBox("已被设置为某地址子地址的保存文件，\n请选择其他文件用于保存","提示文件");
				break;
			}
		}
		
		if(AddFlag)
		{
			m_FileCondtionList.InsertItem(addCondID,"");
			str.Format("%d",Adress);
			m_FileCondtionList.SetItemText(addCondID,0,str);
			str.Format("%d",SubAdress+1);
			m_FileCondtionList.SetItemText(addCondID,1,str);

			m_FileCondtionList.SetItemText(addCondID,2,"保存");
			
			m_FileCondtionList.SetItemText(addCondID,3,FileName);

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[addCondID].Adress = Adress;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[addCondID].SubAdress = SubAdress;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[addCondID].FileName = FileName;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[addCondID].SaveFlag = true;
			//FileID = FileID;
			
			MessageBox("添加成功","提示");

		}
	}
	else MessageBox("请选择保存文件","提示");

}
void CMonitorConfigDlg::OnButtonADD() 
{
	// TODO: Add your control notification handler code here
	/*
	Adress;
	int SubAdress;
    int	FileID;
	CString FileName;
	bool SaveFlag;*/
	int Adress,SubAdress,i;
	CFile FileID;
	bool AddFlag;
	CString str,FileName;
	CFileException e;

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();


	

	GetDlgItemText(IDC_EDIT6,FileName);

	Adress = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();
	SubAdress = ((CComboBox*)GetDlgItem(IDC_COMBO3))->GetCurSel();

	ADDCondtion(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.NowConditcount,Adress,SubAdress,FileName) ;
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.NowConditcount++;

}

void CMonitorConfigDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int SelecID;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	SelecID = m_FileCondtionList.GetNextItem(-1,LVNI_SELECTED);
	if(SelecID>=0)	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[SelecID].SaveFlag = !m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[SelecID].SaveFlag;
	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[SelecID].SaveFlag)
		m_FileCondtionList.SetItemText(SelecID,2,"保存");
	else	m_FileCondtionList.SetItemText(SelecID,2,"不保存");

	*pResult = 0;
}

void CMonitorConfigDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	int SelecID,i;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	SelecID = m_FileCondtionList.GetNextItem(-1,LVNI_SELECTED);
	if(SelecID>=0)	
	{
		for(i=SelecID;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.NowConditcount-1;i++)
			memcpy(&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i], &m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.Conditonval[i+1],sizeof(SaveMessageFileType1));
	}
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageSaveCondtion.NowConditcount--;
	m_FileCondtionList.DeleteItem(SelecID);
}



void CMonitorConfigDlg::OnCheck59() 
{
	// TODO: Add your control notification handler code here
	
}

void CMonitorConfigDlg::OnOk() 
{
	// TODO: Add your control notification handler code here
	
}

void CMonitorConfigDlg::OnButton122() 
{
	// TODO: Add your control notification handler code here
	//if(GetDlgItem(IDC_BUTTON14)->IsWindowEnabled())
	{
		//if(MessageBox("数据已经更改是否更改过滤条件","提示",MB_YESNOCANCEL)==IDYES)
		{
	//		OnButton15(); 
			CDialog::OnCancel();
		}
	}
	
}

void CMonitorConfigDlg::OnButton123() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CMonitorConfigDlg::OnButton124() 
{
	// TODO: Add your control notification handler code here
	OnButton15();
}	


	// TODO: Add your control notification handler code here
int CMonitorConfigDlg::chartoint(char val)
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
int CMonitorConfigDlg::HexToInt(CString str,int len)
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

void CMonitorConfigDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	CString str;
	int k;

	GetDlgItemText(IDC_EDIT1,str);
	int val = HexToInt(str,4);
	str.Format("%4X",val);
	for(k=0;k<4;k++) 
				if(str.GetAt(k)==' ') str.SetAt(k,'0');

	m_VectorList.InsertItem(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[256],str);

	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[256]] = HexToInt(str,4);
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[256]++;

}

void CMonitorConfigDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	int Select,AllItem,i;
	AllItem = m_VectorList.GetItemCount();
	Select = m_VectorList.GetNextItem(-1,LVNI_SELECTED);	
	if(Select>=0)
	{
		for(i=Select;i<AllItem-Select-1;i++)
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[i] = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[i+1];

		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Vector[256]--;
		m_VectorList.DeleteItem(Select);
	}
		

}

void CMonitorConfigDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	CString str;
	int k;
	GetDlgItemText(IDC_EDIT2,str);
	int val = HexToInt(str,4);
	str.Format("%4X",val);
	for(k=0;k<4;k++) 
				if(str.GetAt(k)==' ') str.SetAt(k,'0');
	m_StutasList.InsertItem(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[256],str);

	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[256]] = HexToInt(str,4);
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[256]++;
}

void CMonitorConfigDlg::OnButton22() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	int Select,AllItem,i;
	AllItem = m_StutasList.GetItemCount();
	Select = m_StutasList.GetNextItem(-1,LVNI_SELECTED);	
	if(Select>=0)
	{
		for(i=Select;i<AllItem-Select-1;i++)
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[i] = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[i+1];

		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].NoShow_Stutas[256]--;
		m_StutasList.DeleteItem(Select);
	}
}

void CMonitorConfigDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<32;i++)
	{
		((CButton*)GetDlgItem(IDC_CHECK68+i))->SetCheck(true);

	}
	OnCheck1() ;
}

void CMonitorConfigDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<32;i++)
	{
		((CButton*)GetDlgItem(IDC_CHECK68+i))->SetCheck(false);

	}
	OnCheck1() ;
}

void CMonitorConfigDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	int i,j;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	for(j=0;j<32;j++)
	{
		for(i=0;i<32;i++)
		{
			
			m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag[j][i] = true;

			
		}
	}
	for(i=0;i<32;i++)
	{
		((CButton*)GetDlgItem(IDC_CHECK68+i))->SetCheck(true);			
	}
}

void CMonitorConfigDlg::OnButton10() 
{
	// TODO: Add your control notification handler code here
		int i,j;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	for(j=0;j<32;j++)
	{
		for(i=0;i<32;i++)
		{
			
			m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag[j][i] = false;

			
		}
	}
	for(i=0;i<32;i++)
	{
		((CButton*)GetDlgItem(IDC_CHECK68+i))->SetCheck(false);			
	}
}
