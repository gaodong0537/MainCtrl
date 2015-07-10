// RTDataSet.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "RTDataSet.h"
#include "MainFrm.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTDataSet dialog


CRTDataSet::CRTDataSet(CWnd* pParent /*=NULL*/)
	: CDialog(CRTDataSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRTDataSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRTDataSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRTDataSet)
	DDX_Control(pDX, IDC_BUTTON2, m_Button2);
	DDX_Control(pDX, IDC_BUTTON23, m_Button1);
	DDX_Control(pDX, ID_SETRT_STADIT, m_Static1);
	DDX_Control(pDX, IDC_LIST4, m_VectorList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRTDataSet, CDialog)
	//{{AFX_MSG_MAP(CRTDataSet)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON6, OnButtonCreateRond)
	ON_BN_CLICKED(IDC_BUTTON8, OnButtonCreatezero)
	ON_BN_CLICKED(IDC_BUTTON9, OnButtonCreataff)
	ON_BN_CLICKED(IDC_BUTTON10, OnButtonCreateadd)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonOK)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonADDvec)
	ON_BN_CLICKED(IDC_BUTTON21, OnButtonEnableContrl)
	ON_BN_CLICKED(IDC_CHECK124, OnCheck124Enable)
	ON_BN_CLICKED(IDC_BUTTON19, OnButtonAllEnable)
	ON_BN_CLICKED(IDC_BUTTON20, OnButtonAllDisable)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON22, OnButton22)
	ON_CBN_SELCHANGE(IDC_SUBADRESS, OnSelchangeSubadress)
	ON_CBN_SELCHANGE(IDC_ADRESS4, OnSelchangeAdress4)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckVectorEnableFlash)
	ON_BN_CLICKED(IDC_CHECK125, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK126, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK127, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK128, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK129, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK130, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK131, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK132, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK133, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK134, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK135, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK136, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK137, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK138, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK139, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK140, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK141, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK142, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK143, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK144, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK145, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK146, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK147, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK148, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK149, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK150, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK151, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK152, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK153, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK154, OnCheck124Enable)
	ON_BN_CLICKED(IDC_CHECK155, OnCheck124Enable)
	ON_BN_CLICKED(IDC_BUTTON23, OnButtonAddvector)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRTDataSet message handlers

BEGIN_EVENTSINK_MAP(CRTDataSet, CDialog)
    //{{AFX_EVENTSINK_MAP(CRTDataSet)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CRTDataSet::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//m_Button1.SetIcon(IDI_READ,IDI_READ);
	m_Button1.DrawBorder(true);
	m_Button1.OffsetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 0, 0));
	m_Button1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(255, 0, 0));
	m_Button1.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_Button1.SetShowText(true);
	m_Button1.SetFlat(false,false);

	m_Button2.DrawBorder(true);
	m_Button2.OffsetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));
	m_Button2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 128, 0));
	m_Button2.SetAlign(CButtonST::ST_ALIGN_HORIZ);
	m_Button2.SetShowText(true);
	m_Button2.SetFlat(false,false);


	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	LV_COLUMN lvcolumn;
	m_VectorList.ModifyStyle(LVS_EDITLABELS,0L);
	m_VectorList.ModifyStyle(0L,LVS_REPORT);
	m_VectorList.ModifyStyle(0L,LVS_SHOWSELALWAYS);
	m_VectorList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES|LVS_EX_ONECLICKACTIVATE|LVS_EX_FLATSB);

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVIS_FOCUSED | LVIS_SELECTED;
	lvcolumn.fmt = LVCFMT_LEFT; // Other possible formats are LVCFMT_CENTER & LVCFMT_RIGHT
	
	lvcolumn.cx = 100;
	lvcolumn.pszText = "矢量字";
	m_VectorList.InsertColumn(0,&lvcolumn);


	int RTflag,busyflag,questflag,systermflag,dynaflag,broadflag,errflag,instrflag; 

	CString str;
	VARIANT valtype;
	int val;
	int i,j;

	for(i=0;i<6;i++)
	{
		str.Format("%2d",i);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(str);

	}
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);

	for(i=0;i<60;i++)
	{
		str.Format("%2d",i);
		((CComboBox*)GetDlgItem(IDC_WRITEID))->AddString(str);
	}
	((CComboBox*)GetDlgItem(IDC_WRITEID))->SetCurSel(0);

	SetDlgItemText(IDC_EDIT7,"0000");
	SetDlgItemText(IDC_EDIT3,"0000");
	/*
	str.Format("%d",RTAdress);
	SetDlgItemText(IDC_EDIT1,str);
	*/
	for(i=0;i<32;i++)
	{
		str.Format("%2d",i);
		((CComboBox*)GetDlgItem(IDC_ADRESS4))->AddString(str);
		((CComboBox*)GetDlgItem(IDC_SUBADRESS))->AddString(str);

		if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Enable[i])
			((CButton*)GetDlgItem(IDC_CHECK124+i))->SetCheck(true);
	}
	((CComboBox*)GetDlgItem(IDC_ADRESS4))->SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_SUBADRESS))->SetCurSel(1);
	if(IniType==0)
	{
	
		((CComboBox*)GetDlgItem(IDC_ADRESS4))->SetCurSel(RTAdress);
		SetDlgItemText(IDC_EDIT3,"000A");
		SetDlgItemText(IDC_EDIT5,"00A0");
		for(i=0;i<32;i++)
		{
			str.Format("%2d",i);
			SetDlgItemText(IDC_EDIT18+i,"0000");
		}

	}
	else if(IniType==1)
	{
		((CComboBox*)GetDlgItem(IDC_ADRESS4))->SetCurSel(RTAdress);
		((CComboBox*)GetDlgItem(IDC_SUBADRESS))->SetCurSel(SubAdress);
		for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount;i++)
		{
			m_VectorList.InsertItem(i,"");
			str.Format("%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].VectorWord[i]);
			for(j=0;j<4;j++)
					if(str.GetAt(j)==' ') str.SetAt(j,'0');
			m_VectorList.SetItemText(i,0,str);
		}

		for(i=0;i<32;i++)
		{

			val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].msg_buffer_write[SubAdress].mess_data[i];
		
			str.Format("%4X",val);
			for(j=0;j<4;j++) 
			{
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			}
			SetDlgItemText(IDC_EDIT18+i,str);

		}

		val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel]. rtstatus[RTAdress];

	if((val&1)==1)
		RTflag = true;
	else RTflag= false;
	
	if((val&(1<<3))==(1<<3))
		busyflag = true;
	else busyflag= false;
	
	if((val&(1<<8))==(1<<8))
		questflag = true;
	else questflag= false;
	
	if((val&(1<<2))==(1<<2))
		systermflag = true;
	else systermflag= false;

	if((val&(1<<1))==(1<<1))
		dynaflag = true;
	else dynaflag= false;

	if((val&(1<<4))==(1<<4))
		broadflag = true;
	else broadflag= false;
	
	if((val&(1<<10))==(1<<10))
		errflag = true;
	else errflag= false;

	if((val&(1<<9))==(1<<9))
		instrflag = true;
	else instrflag= false;

	((CButton *)GetDlgItem(IDC_RTBIT))->SetCheck(RTflag);

	((CButton *)GetDlgItem(IDC_BUSYBIT))->SetCheck(busyflag);

	((CButton *)GetDlgItem(IDC_SEVERBIT))->SetCheck(questflag);

	((CButton *)GetDlgItem(IDC_SYSTMBIT))->SetCheck(systermflag);

	((CButton *)GetDlgItem(IDC_SYNOBIT))->SetCheck(dynaflag);

	((CButton *)GetDlgItem(IDC_BOARDBIT))->SetCheck(broadflag);
	((CButton *)GetDlgItem(IDC_ERRBIT))->SetCheck(errflag);

	((CButton *)GetDlgItem(IDC_INSTRBIT))->SetCheck(instrflag);

		val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorWord;
		
	str.Format("%4X",val);
	for(j=0;j<4;j++) 
	{
		if(str.GetAt(j)==' ') str.SetAt(j,'0');
	}
	SetDlgItemText(IDC_EDIT3,str);

	val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].Stestword[RTAdress];
	str.Format("%4X",val);
	for(j=0;j<4;j++) 
	{
		if(str.GetAt(j)==' ') str.SetAt(j,'0');
	}
	SetDlgItemText(IDC_EDIT5,str);

	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].SubSetFlag[SubAdress])
		for(i=0;i<32;i++)
		{
			val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].msg_buffer_write[SubAdress].mess_data[i];
			str.Format("%4X",val);
			for(j=0;j<4;j++) 
			{
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			}
			SetDlgItemText(IDC_EDIT18+i,str);

		}
		else 
		for(i=0;i<32;i++)
		{
			val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].msg_buffer_write[1].mess_data[i];
			str.Format("%4X",val);
			for(j=0;j<4;j++) 
			{
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			}
			SetDlgItemText(IDC_EDIT18+i,str);

		}

	}
	else if(IniType==3)
	{
		((CComboBox*)GetDlgItem(IDC_ADRESS4))->SetCurSel(RTAdress);
		((CComboBox*)GetDlgItem(IDC_SUBADRESS))->SetCurSel(SubAdress);
		for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount;i++)
		{
			m_VectorList.InsertItem(i,"");
			str.Format("%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].VectorWord[i]);
			for(j=0;j<4;j++)
					if(str.GetAt(j)==' ') str.SetAt(j,'0');
			m_VectorList.SetItemText(i,0,str);
		}

		if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorSetFlag)
		{
			val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel]. rtstatus[RTAdress];

			if((val&1)==1)
				RTflag = true;
			else RTflag= false;
			
			if((val&(1<<3))==(1<<3))
				busyflag = true;
			else busyflag= false;
			
			if((val&(1<<8))==(1<<8))
				questflag = true;
			else questflag= false;
			
			if((val&(1<<2))==(1<<2))
				systermflag = true;
			else systermflag= false;

			if((val&(1<<1))==(1<<1))
				dynaflag = true;
			else dynaflag= false;

			if((val&(1<<4))==(1<<4))
				broadflag = true;
			else broadflag= false;
			
			if((val&(1<<10))==(1<<10))
				errflag = true;
			else errflag= false;

			if((val&(1<<9))==(1<<9))
				instrflag = true;
			else instrflag= false;

			((CButton *)GetDlgItem(IDC_RTBIT))->SetCheck(RTflag);

			((CButton *)GetDlgItem(IDC_BUSYBIT))->SetCheck(busyflag);

			((CButton *)GetDlgItem(IDC_SEVERBIT))->SetCheck(questflag);

			((CButton *)GetDlgItem(IDC_SYSTMBIT))->SetCheck(systermflag);

			((CButton *)GetDlgItem(IDC_SYNOBIT))->SetCheck(dynaflag);

			((CButton *)GetDlgItem(IDC_BOARDBIT))->SetCheck(broadflag);
			((CButton *)GetDlgItem(IDC_ERRBIT))->SetCheck(errflag);

			((CButton *)GetDlgItem(IDC_INSTRBIT))->SetCheck(instrflag);

				val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorWord;
				
			str.Format("%4X",val);
			for(j=0;j<4;j++) 
			{
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			}
			SetDlgItemText(IDC_EDIT3,str);

			val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].Stestword[RTAdress];
			str.Format("%4X",val);
			for(j=0;j<4;j++) 
			{
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			}
			SetDlgItemText(IDC_EDIT5,str);
		}

		if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].SubSetFlag[1])
		for(i=0;i<32;i++)
		{
			val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].msg_buffer_write[1].mess_data[i];
			str.Format("%4X",val);
			for(j=0;j<4;j++) 
			{
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			}
			SetDlgItemText(IDC_EDIT18+i,str);

		}
		else 
		for(i=0;i<32;i++)
		{
			val = 0;
			str.Format("%4X",val);
			for(j=0;j<4;j++) 
			{
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			}
			SetDlgItemText(IDC_EDIT18+i,str);

		}
		


	}

	OnSelchangeAdress4();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CRTDataSet::OnButtonOK() 
{
	// TODO: Add your control notification handler code here
	int i,SubAdress,RT_SetCount;
	bool Add_Flag;
	int RTflag,busyflag,questflag,systermflag,dynaflag,broadflag,errflag,instrflag; 
	CString str;

	CString MessageStr;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	RT_SetCount = ((CComboBox*)GetDlgItem(IDC_ADRESS4))->GetCurSel();;//
	SubAdress = ((CComboBox*)GetDlgItem(IDC_SUBADRESS))->GetCurSel();

	//确定写入状态字
	if(((CButton *)GetDlgItem(IDC_RTBIT))->GetCheck()) RTflag =1;
	else RTflag = 0;

	if(((CButton *)GetDlgItem(IDC_BUSYBIT))->GetCheck()) busyflag =1;
	else busyflag = 0;

	if(((CButton *)GetDlgItem(IDC_SEVERBIT))->GetCheck()) questflag =1;
	else questflag = 0;

	if(((CButton *)GetDlgItem(IDC_SYSTMBIT))->GetCheck()) systermflag =1;
	else systermflag = 0;

	if(((CButton *)GetDlgItem(IDC_SYNOBIT))->GetCheck()) dynaflag =1;
	else dynaflag = 0;

	if(((CButton *)GetDlgItem(IDC_BOARDBIT))->GetCheck()) broadflag =1;
	else broadflag = 0;

	if(((CButton *)GetDlgItem(IDC_ERRBIT))->GetCheck()) errflag =1;
	else errflag = 0;

	if(((CButton *)GetDlgItem(IDC_INSTRBIT))->GetCheck()) instrflag =1;
	else instrflag = 0;




	if(RTflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=1;
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1);
	
	if(busyflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<3);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<3);	
	
	if(questflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<8);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<8);	
	
	if(systermflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<2);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<2);
	
	if(dynaflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<1);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<1);
	
	if(broadflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<4);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<4);
	
	if(errflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<10);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<10);
	
	if(instrflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<9);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<9);


	GetDlgItemText(IDC_EDIT3,str);
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].VectorWord = HexToInt(str,4);
	
	GetDlgItemText(IDC_EDIT5,str);
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].SelfTestWord = HexToInt(str,4);

	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].SubSetFlag[SubAdress] == false)
	{
		Add_Flag = true;
	}
	else 
	{
		MessageStr.Format("子地址%d数据已经存在，是否覆盖",SubAdress);
		if(MessageBox(MessageStr,"提示",MB_YESNOCANCEL)==IDYES)
		{
			Add_Flag = true;
		}
		else Add_Flag = false;
	}

	if(Add_Flag == true)
	{
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].msg_buffer_write[SubAdress].enable = 0;		// No interrupts enabled
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].msg_buffer_write[SubAdress].error_inj_id = 0;	// No error injection
		
		for(i=0;i<32;i++)
		{
			GetDlgItemText(IDC_EDIT18+i,str);
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].msg_buffer_write[SubAdress].mess_data[i] = HexToInt(str,4);
		}
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].SubSetFlag[SubAdress] = true;
		
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].WriteRTData(RT_SetCount,SubAdress,((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel());
//		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteStatusWord(0, RT_SetCount, SubAdress, 1, 0, statusword, 1);
//		valtype = ((CCWNumEdit *)GetDlgItem(IDC_CWNUMEDITRT34))->GetValue();
//		short vectorword = valtype.dblVal;
//		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWord(0, RT_SetCount, 0, 1, 0, vectorword);
/*
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteStatusWord(0, RT_SetCount, 0, 0, 0, m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount], 1);//状态字
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWord(0, RT_SetCount, 0, 1, 0, m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].VectorWord);
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWordCount(RT_SetCount,0,1);
*/		m_pMainWnd->SetRTViewData(RT_SetCount,SubAdress,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].msg_buffer_write[SubAdress],true);
		
	}
	this->ShowWindow(SW_SHOWNA);
	m_pMainWnd->Invalidate();
}




void CRTDataSet::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	if(((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck())
		statusword = statusword|0x00010000;
	else
		statusword = statusword&0xfffeffff;

}

void CRTDataSet::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	if(((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck())
		statusword = statusword|0x00000400;
	else
		statusword = statusword&0xfffffbff;
}

void CRTDataSet::OnCheck7() 
{
	// TODO: Add your control notification handler code here
	if(((CButton *)GetDlgItem(IDC_CHECK7))->GetCheck())
		statusword = statusword|0x00020000;
	else
		statusword = statusword&0xfffdffff;
}

void CRTDataSet::OnCheck5() 
{
	// TODO: Add your control notification handler code here
	if(((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck())
		statusword = statusword|0x00040000;
	else
		statusword = statusword&0xfffbffff;
}

void CRTDataSet::OnCheck6() 
{
	// TODO: Add your control notification handler code here
	if(((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck())
		statusword = statusword|0x00008000;
	else
		statusword = statusword&0xffff7fff;
}
void CRTDataSet::OnButtonADDvec() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int id,RTAdress,j;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	//GetDlgItemText(IDC_EDIT1,str);
	RTAdress = ((CComboBox*)GetDlgItem(IDC_ADRESS4))->GetCurSel();
	id = ((CComboBox*)GetDlgItem(IDC_WRITEID))->GetCurSel();
	id = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount;
	GetDlgItemText(IDC_EDIT7,str);
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].VectorWord[id] = HexToInt(str,4);
	str.Format("%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].VectorWord[id]+1);
	for(j=0;j<4;j++)
		if(str.GetAt(j)==' ') str.SetAt(j,'0');
	SetDlgItemText(IDC_EDIT7,str);

	m_VectorList.InsertItem(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount,"");
	str.Format("%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].VectorWord[id]);
	for(j=0;j<4;j++)
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
	m_VectorList.SetItemText(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount,0,str);
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount++;
}
void CRTDataSet::OnButton3() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	int SelID,i;
	SelID = m_VectorList.GetNextItem(-1,LVNI_SELECTED);

	if(SelID>=0)
	{
		for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount-1;i++)
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].VectorWord[i] = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].VectorWord[i+1];
		}
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount--;
		m_VectorList.DeleteItem(SelID);
	}
	else
	{
		MessageBox("请在列表中选择要删除的矢量字","提示");
	}
}

void CRTDataSet::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	int i,RTadress;
	CString str;
	RTAdress = ((CComboBox*)GetDlgItem(IDC_ADRESS4))->GetCurSel();
	//RTAdress = atoi(str);

	if(((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck())
	{
		if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount>0)
		{
			for(i=0;i<m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount;i++)
			{
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWord(0, RTAdress, 0, 1, i, m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].VectorWord[i]);
			}
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWordCount(RTAdress,0,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].VectorArra[RTAdress].NowCount );
		
		}
		else
		{
			MessageBox("没有设置该RT的自动更新矢量字组\n设置为固定矢量字","提示");
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWord(0, RTAdress, 0, 1, 0, m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorWord);
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWordCount(RTAdress,0,1);

			((CButton *)GetDlgItem(IDC_CHECK2))->SetCheck(false);
			OnCheckVectorEnableFlash() ;
		}
	}
	else
	{
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWord(0, RTAdress, 0, 1, 0, m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorWord);
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWordCount(RTAdress,0,1);
	}
}
void CRTDataSet::OnButtonCreateRond() 
{
	// TODO: Add your control notification handler code here
	int val;
	VARIANT valtype;
	//valtype =m_Edit1.GetValue();            
	CString str;
	int i,j; 

	for(i=0;i<32;i++)
	{
		val=rand ();
		
		str.Format("%4X",val);
		for(j=0;j<4;j++)
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		SetDlgItemText(IDC_EDIT18+i,str);
		//valtype.dblVal = val;
		//((CCWNumEdit*)GetDlgItem(IDC_CWNUMEDIT1+i))->SetValue(valtype);
	}
}

void CRTDataSet::OnButtonCreatezero() 
{
	// TODO: Add your control notification handler code here
	int val;
	VARIANT valtype;
	
	CString str;
	int i,j; 
	//valtype =m_Edit1.GetValue();
	//val = valtype.dblVal;
	for(i=0;i<32;i++)
	{
		val=0;
		str.Format("%4X",val);
		for(j=0;j<4;j++)
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		SetDlgItemText(IDC_EDIT18+i,str);
		
		//valtype.dblVal = val;
		//((CCWNumEdit*)GetDlgItem(IDC_CWNUMEDIT1+i))->SetValue(valtype);
	}
}

void CRTDataSet::OnButtonCreataff() 
{
	// TODO: Add your control notification handler code here
	int val;
	//VARIANT valtype;
	//valtype =m_Edit1.GetValue();
	CString str;
	int i,j; 

	for(i=0;i<32;i++)
	{
		val=0xffff;
		str.Format("%4X",val);
		for(j=0;j<4;j++)
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		SetDlgItemText(IDC_EDIT18+i,str);
		//valtype.dblVal = val;
		//((CCWNumEdit*)GetDlgItem(IDC_CWNUMEDIT1+i))->SetValue(valtype);
	}
}

void CRTDataSet::OnButtonCreateadd() 
{
	// TODO: Add your control notification handler code here
	int val;
	VARIANT valtype;
	
	CString str;
	int i,j; 
//	valtype =m_Edit1.GetValue();
//	val = valtype.dblVal;
	GetDlgItemText(IDC_EDIT18,str);
	val = HexToInt(str,4);
	for(i=0;i<32;i++)
	{
		val++;
		str.Format("%4X",val%0xffff);
		for(j=0;j<4;j++)
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		SetDlgItemText(IDC_EDIT18+i,str);

		//valtype.dblVal = val%0xffff;
		//((CCWNumEdit*)GetDlgItem(IDC_CWNUMEDIT1+i))->SetValue(valtype);
	}
}

void CRTDataSet::OnButton11() 
{
	// TODO: Add your control notification handler code here
	int val;
	//VARIANT valtype;
	//valtype =m_Edit1.GetValue();
	CString str;
	int i,j; 

	//val = valtype.dblVal;
	GetDlgItemText(IDC_EDIT18,str);
	val = HexToInt(str,4);
	for(i=0;i<32;i++)
	{
		
		str.Format("%4X",val);
		for(j=0;j<4;j++)
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		SetDlgItemText(IDC_EDIT18+i,str);

		//((CCWNumEdit*)GetDlgItem(IDC_CWNUMEDIT1+i))->SetValue(valtype);
	}
}
int CRTDataSet::chartoint(char val)
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
int CRTDataSet::HexToInt(CString str,int len)
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





void CRTDataSet::OnButtonEnableContrl() 
{
	// TODO: Add your control notification handler code here
	int i;
	bool Val;
	CString inSertName;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	for(i=0;i<32;i++)
	{
		if(((CButton*)GetDlgItem(IDC_CHECK124+i))->GetCheck()==true)
		{	
			if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data_Exsit[i]==false)//判断该RT是否也存在
			{
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data_Exsit[i] = true;
				
				inSertName.Format("RT%2d",i);
				m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].InsertTreeData(1,inSertName,i);
				//m_pMainWnd->RTView[i].ShowWindow(SW_SHOW);
				m_pMainWnd->RTView[m_pMainWnd->m_now_SelectChannel][i].SetWindowText(inSertName);
				
			}
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Enable[i] = true;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].EnableRT(i);
			m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].SetRTIcon(i,true);
		}
		else
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Enable[i] = false;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].DisableRT(i);
			m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].SetRTIcon(i,false);
			//m_pMainWnd->ProjectDlg.DeleteRT(i);
			m_pMainWnd->RTView[m_pMainWnd->m_now_SelectChannel][i].ShowWindow(SW_HIDE);
		}
	}
	//CDialog::OnOK();
}

void CRTDataSet::OnCheck124Enable() 
{
	// TODO: Add your control notification handler code here
	OnButtonEnableContrl() ;
}

void CRTDataSet::OnButtonAllEnable() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<32;i++)
	{
		((CButton*)GetDlgItem(IDC_CHECK124+i))->SetCheck(true);
	}
	OnButtonEnableContrl() ;
}

void CRTDataSet::OnButtonAllDisable() 
{
	// TODO: Add your control notification handler code here
	int i;
	for(i=0;i<32;i++)
	{
		((CButton*)GetDlgItem(IDC_CHECK124+i))->SetCheck(false);
	}
	OnButtonEnableContrl() ;
}

void CRTDataSet::OnButton5() 
{
	// TODO: Add your control notification handler code here
	OnButtonOK() ;
	CDialog::OnCancel();
}

void CRTDataSet::OnButton22() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CRTDataSet::OnSelchangeSubadress() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int i,j,val;
	RTAdress = ((CComboBox*)GetDlgItem(IDC_ADRESS4))->GetCurSel();
	SubAdress = ((CComboBox*)GetDlgItem(IDC_SUBADRESS))->GetCurSel();

	str.Format("地址为%d子地址为%d的数据字配置(HEX)",RTAdress,SubAdress);
	//SetDlgItemText(ID_SETRT_STADIT,str);
	((CStatic *)GetDlgItem(ID_SETRTNAME))->SetWindowText(str);

	str.Format("地址为%d状态字设置",RTAdress);
	((CStatic *)GetDlgItem(ID_SETRTP))->SetWindowText(str);

	str.Format("地址为%d矢量字设置",RTAdress);
	((CStatic *)GetDlgItem(ID_SETRTVECTOR))->SetWindowText(str);

	str.Format("RT%d子地址%d加载数据",RTAdress,SubAdress);
	SetDlgItemText(IDC_BUTTON2,str);
	
	//m_Static1.SetWindowText(str);

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].SubSetFlag[SubAdress])
	for(i=0;i<32;i++)
	{
		val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].msg_buffer_write[SubAdress].mess_data[i];
		str.Format("%4X",val);
		for(j=0;j<4;j++) 
		{
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		}
		SetDlgItemText(IDC_EDIT18+i,str);

	}
	else 
	for(i=0;i<32;i++)
	{
		val = 0;
		str.Format("%4X",val);
		for(j=0;j<4;j++) 
		{
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		}
		SetDlgItemText(IDC_EDIT18+i,str);

	}
	
	

}

void CRTDataSet::OnSelchangeAdress4() 
{
	// TODO: Add your control notification handler code here
	CString str;
	int i,j,val;
	int RTflag,busyflag,questflag,systermflag,dynaflag,broadflag,errflag,instrflag;
	RTAdress = ((CComboBox*)GetDlgItem(IDC_ADRESS4))->GetCurSel();
	SubAdress = ((CComboBox*)GetDlgItem(IDC_SUBADRESS))->GetCurSel();

	str.Format("地址为%d子地址为%d的数据字配置(HEX)",RTAdress,SubAdress);
	//SetDlgItemText(ID_SETRT_STADIT,str);
	((CStatic *)GetDlgItem(ID_SETRTNAME))->SetWindowText(str);

	str.Format("地址为%d状态字设置",RTAdress);
	((CStatic *)GetDlgItem(ID_SETRTP))->SetWindowText(str);

	str.Format("地址为%d矢量字设置",RTAdress);
	((CStatic *)GetDlgItem(ID_SETRTVECTOR))->SetWindowText(str);

	str.Format("RT%d加载状态字、矢量字和自测试字",RTAdress);
	SetDlgItemText(IDC_BUTTON23,str);

	str.Format("RT%d子地址%d加载数据",RTAdress,SubAdress);
	SetDlgItemText(IDC_BUTTON2,str);

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].SubSetFlag[SubAdress])
	for(i=0;i<32;i++)
	{
		val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].msg_buffer_write[SubAdress].mess_data[i];
		str.Format("%4X",val);
		for(j=0;j<4;j++) 
		{
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		}
		SetDlgItemText(IDC_EDIT18+i,str);

	}
	else 
	for(i=0;i<32;i++)
	{
		val = 0;
		str.Format("%4X",val);
		for(j=0;j<4;j++) 
		{
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		}
		SetDlgItemText(IDC_EDIT18+i,str);

	}

	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorSetFlag)
	{
		val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorWord;
		str.Format("%4X",val);
		for(j=0;j<4;j++) 
		{
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		}
		SetDlgItemText(IDC_EDIT3,str);

		val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].SelfTestWord;
		str.Format("%4X",val);
		for(j=0;j<4;j++) 
		{
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		}
		SetDlgItemText(IDC_EDIT8,str);
	}
	else
	{
		val = 0;
		str.Format("%4X",val);
		for(j=0;j<4;j++) 
		{
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		}
		SetDlgItemText(IDC_EDIT3,str);
		SetDlgItemText(IDC_EDIT8,str);
	}
	API_BM_MBUF     messages; 

	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorSetFlag)
		{
		messages.status1 = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].IntToStutas1553(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].StatusWord);
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

		((CButton *)GetDlgItem(IDC_RTBIT))->SetCheck(RTflag);

		((CButton *)GetDlgItem(IDC_BUSYBIT))->SetCheck(busyflag);

		((CButton *)GetDlgItem(IDC_SEVERBIT))->SetCheck(questflag);

		((CButton *)GetDlgItem(IDC_SYSTMBIT))->SetCheck(systermflag);

		((CButton *)GetDlgItem(IDC_SYNOBIT))->SetCheck(dynaflag);

		((CButton *)GetDlgItem(IDC_BOARDBIT))->SetCheck(broadflag);
		((CButton *)GetDlgItem(IDC_ERRBIT))->SetCheck(errflag);

		((CButton *)GetDlgItem(IDC_INSTRBIT))->SetCheck(instrflag);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_RTBIT))->SetCheck(false);

		((CButton *)GetDlgItem(IDC_BUSYBIT))->SetCheck(false);

		((CButton *)GetDlgItem(IDC_SEVERBIT))->SetCheck(false);

		((CButton *)GetDlgItem(IDC_SYSTMBIT))->SetCheck(false);

		((CButton *)GetDlgItem(IDC_SYNOBIT))->SetCheck(false);

		((CButton *)GetDlgItem(IDC_BOARDBIT))->SetCheck(false);
		((CButton *)GetDlgItem(IDC_ERRBIT))->SetCheck(false);

		((CButton *)GetDlgItem(IDC_INSTRBIT))->SetCheck(false);
	}

	/*
	if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorSetFlag)
	{
		val = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RTAdress].VectorWord;
		str.Format("%4X",val);
		for(j=0;j<4;j++) 
		{
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		}
		SetDlgItemText(IDC_EDIT3,str);
	}
	else
	{
		val = 0;
		str.Format("%4X",val);
		for(j=0;j<4;j++) 
		{
			if(str.GetAt(j)==' ') str.SetAt(j,'0');
		}
		SetDlgItemText(IDC_EDIT3,str);
	}
	*/
}

void CRTDataSet::OnCheckVectorEnableFlash() 
{
	// TODO: Add your control notification handler code here
	if(((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck())
	{
		((CEdit*)GetDlgItem(IDC_EDIT7))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_BUTTON1))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_BUTTON3))->EnableWindow(true);
		((CListCtrl*)GetDlgItem(IDC_LIST4))->EnableWindow(true);

		((CEdit*)GetDlgItem(IDC_EDIT3))->EnableWindow(false);
	}
	else
	{
		((CEdit*)GetDlgItem(IDC_EDIT7))->EnableWindow(false);
		((CButton*)GetDlgItem(IDC_BUTTON1))->EnableWindow(false);
		((CButton*)GetDlgItem(IDC_BUTTON3))->EnableWindow(false);
		((CListCtrl*)GetDlgItem(IDC_LIST4))->EnableWindow(false);

		((CEdit*)GetDlgItem(IDC_EDIT3))->EnableWindow(true);
	}
}

void CRTDataSet::OnButtonAddvector() 
{
	// TODO: Add your control notification handler code here
	int i,SubAdress,RT_SetCount;
	bool Add_Flag;
	int RTflag,busyflag,questflag,systermflag,dynaflag,broadflag,errflag,instrflag; 
	CString str;

	CString MessageStr;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	RT_SetCount = ((CComboBox*)GetDlgItem(IDC_ADRESS4))->GetCurSel();;//
	SubAdress = ((CComboBox*)GetDlgItem(IDC_SUBADRESS))->GetCurSel();

	//确定写入状态字
	if(((CButton *)GetDlgItem(IDC_RTBIT))->GetCheck()) RTflag =1;//终端
	else RTflag = 0;

	if(((CButton *)GetDlgItem(IDC_BUSYBIT))->GetCheck()) busyflag =1;
	else busyflag = 0;

	if(((CButton *)GetDlgItem(IDC_SEVERBIT))->GetCheck()) questflag =1;
	else questflag = 0;

	if(((CButton *)GetDlgItem(IDC_SYSTMBIT))->GetCheck()) systermflag =1;//子系统
	else systermflag = 0;

	if(((CButton *)GetDlgItem(IDC_SYNOBIT))->GetCheck()) dynaflag =1;
	else dynaflag = 0;

	if(((CButton *)GetDlgItem(IDC_BOARDBIT))->GetCheck()) broadflag =1;
	else broadflag = 0;

	if(((CButton *)GetDlgItem(IDC_ERRBIT))->GetCheck()) errflag =1;
	else errflag = 0;

	if(((CButton *)GetDlgItem(IDC_INSTRBIT))->GetCheck()) instrflag =1;//测试手段
	else instrflag = 0;



	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] = 0;


	
	if(errflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<10);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<10);
	
	if(instrflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<9);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<9);

	if(questflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<8);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<8);

	if(broadflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<4);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<4);

	if(busyflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<3);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<3);	

	if(systermflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<2);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<2);

	if(dynaflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<1);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<1);

	if(RTflag==1)  m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] |=(1<<0);
	else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] &=~(1<<0);


	GetDlgItemText(IDC_EDIT1,str);
	//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount] = HexToInt(str,4);

	GetDlgItemText(IDC_EDIT3,str);
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].VectorWord = HexToInt(str,4);

	GetDlgItemText(IDC_EDIT8,str);
	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].SelfTestWord = HexToInt(str,4);

	//if(Add_Flag == true)
	{
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].msg_buffer_write[SubAdress].enable = 0;		// No interrupts enabled
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].msg_buffer_write[SubAdress].error_inj_id = 0;	// No error injection
/*		
		for(i=0;i<32;i++)
		{
			GetDlgItemText(IDC_EDIT18+i,str);
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].msg_buffer_write[SubAdress].mess_data[i] = HexToInt(str,4);
		}
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].SubSetFlag[SubAdress] = true;
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].WriteRTData(RT_SetCount,SubAdress);
*/
//		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteStatusWord(0, RT_SetCount, SubAdress, 1, 0, statusword, 1);
//		valtype = ((CCWNumEdit *)GetDlgItem(IDC_CWNUMEDITRT34))->GetValue();
//		short vectorword = valtype.dblVal;
//		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWord(0, RT_SetCount, 0, 1, 0, vectorword);

		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].Write_SelfTest(RT_SetCount,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].SelfTestWord,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Enable[RT_SetCount]);
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteStatusWord(0, RT_SetCount, 0, 0, 0, m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].rtstatus[RT_SetCount], 1);//状态字
		OnButton4(); 
		//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWord(0, RT_SetCount, 0, 1, 0, m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].VectorWord);
		//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_WriteVectorWordCount(RT_SetCount,0,1);
		m_pMainWnd->SetRTViewData(RT_SetCount,SubAdress,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].RT_Data[RT_SetCount].msg_buffer_write[SubAdress],false);
		
	}
	this->ShowWindow(SW_SHOWNA);
	m_pMainWnd->Invalidate();
}
