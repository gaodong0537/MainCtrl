// MessageSet.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "MessageSet.h"
#include "Winbase.h"
#include "MainFrm.h"
#include "math.h"
//

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageSet dialog


CMessageSet::CMessageSet(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessageSet)
	//}}AFX_DATA_INIT
}


void CMessageSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageSet)
	DDX_Control(pDX, IDC_STATICRTRT, m_StutasRTRT);
	DDX_Control(pDX, IDC_STATICRTBC, m_StutasRTBC);
	DDX_Control(pDX, IDC_STATICMODE, m_StutasMODE);
	DDX_Control(pDX, IDC_STATICBCRT, m_StutasBCRT);
	DDX_Control(pDX, IDC_COMBO7, GBoxAddress);
	DDX_Control(pDX, IDC_COMBO3, m_WCount);
	DDX_Control(pDX, IDC_COMBO2, m_SubAdress);
	DDX_Control(pDX, IDC_COMBO1, m_RTAdress);
	DDX_Control(pDX, IDC_COMBO6, m_WCount2);
	DDX_Control(pDX, IDC_COMBO5, m_SubAdress2);
	DDX_Control(pDX, IDC_COMBO4, m_RTAdress2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessageSet, CDialog)
	//{{AFX_MSG_MAP(CMessageSet)
	ON_WM_SETFOCUS()
	ON_CBN_SELCHANGE(IDC_COMBO9, OnSelchangeCombo9)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonBCRT)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonRTBC)
	ON_BN_CLICKED(IDC_BUTTON4, OnButtonRTRT)
	ON_BN_CLICKED(IDC_BUTTON5, OnButtonMODE)
	ON_BN_CLICKED(IDC_BUTTON6, OnButtonCreateRond)
	ON_BN_CLICKED(IDC_BUTTON8, OnButtonCreatezero)
	ON_BN_CLICKED(IDC_BUTTON9, OnButtonCreataff)
	ON_BN_CLICKED(IDC_BUTTON10, OnButtonCreateadd)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_BN_CLICKED(IDC_BUTTON12, OnButtonOK)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageSet message handlers



BEGIN_EVENTSINK_MAP(CMessageSet, CDialog)
    //{{AFX_EVENTSINK_MAP(CMessageSet)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CMessageSet::OnInitDialog() 
{
 	CDialog::OnInitDialog();
	int i;
	CString str;
	// TODO: Add extra initialization here
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();
	
	((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(true);	
	((CButton*)GetDlgItem(IDC_CHECK12))->SetCheck(false);

	for(i=0;i<32;i++)
	{
		str.Format("%2d",i);
		m_RTAdress.AddString(str);
		m_RTAdress2.AddString(str);

		m_SubAdress.AddString(str);
		m_SubAdress2.AddString(str);
	}
	for(i=0;i<32;i++)
	{
		str.Format("%2d",i+1);
		m_WCount.AddString(str);
		m_WCount2.AddString(str);
	}
	m_WCount.SetCurSel(31);
	m_WCount2.SetCurSel(31);
	for(i=0;i<=32;i++)
	{
		SetDlgItemText(IDC_EDIT18+i,"0000");
	}
	SetDlgItemText(ID_BCPRO_BCFRAMETIME,"200");
	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(0,"动态总线控制00000");
	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(1,"同步00001");
	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(2,"发送上一状态字00010");
	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(3,"启动自检测00011");
	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(4,"发送关闭00100");
	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(5,"取消发送关闭00101");
	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(6,"禁止终端标志位00110");
	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(7,"取消禁止终端标志位00111");
	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(8,"复位远程终端01000");

	((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(9,"发送矢量字10000");
    ((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(10,"带数据字同步10001");
    ((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(11,"发送上一矢量字10010");
    ((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(12,"发送自检测字10011");
    ((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(13,"选定的发送器关闭10100");
    ((CComboBox*)GetDlgItem(IDC_COMBO9))->InsertString(14,"取消选定的发送器关闭10101");
	
	((CComboBox*)GetDlgItem(IDC_COMBO9))->SetCurSel(0);	
	
/*
	for(i=1;i<31;i++)
	{
		str.Format("%2d",i);
		m_SubAdress.AddString(str);
		m_SubAdress2.AddString(str);
		
	}
*/
	m_RTAdress.SetCurSel(1);
	m_SubAdress.SetCurSel(1);
	m_WCount.SetCurSel(31);


	((CComboBox*)GetDlgItem(IDC_COMBO4))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO5))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO6))->SetCurSel(0);

	((CComboBox*)GetDlgItem(IDC_COMBO4))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_COMBO6))->ShowWindow(SW_HIDE);


	this->SetDlgItemText(IDC_MESSAGENAME,"BC_Message");
	OnSelchangeCombo9();
	if(IniType==0)//Insert New
	{
		MessageTyep = 0;
		
		LedShow(0);
	}
	else if(IniType==1)//Edit mode 
	{
		CString str;
		int j;

		LedShow(MessageTyep);
		VARIANT valtype;

		GetDlgItem(IDC_CHECK1)->ShowWindow(SW_SHOW);

		m_RTAdress.SetCurSel(address);
		m_SubAdress.SetCurSel(subaddr);
		if(wcount==0) m_WCount.SetCurSel(31);
		else m_WCount.SetCurSel(wcount-1);

		m_RTAdress2.SetCurSel(address2);
		m_SubAdress2.SetCurSel(subaddr2);
		if(wcount2==0) m_WCount2.SetCurSel(31);
		else m_WCount2.SetCurSel(wcount2-1);

		str.Format("%d",GapTime);
		SetDlgItemText(ID_BCPRO_BCFRAMETIME,str);
		
		if(NowAddMessageTyep==1)
			((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCRetry_Flag[nowMessageNo]);
		else ((CButton*)GetDlgItem(IDC_CHECK8))->SetCheck(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCRetry_Flag_2[nowMessageNo]);
		
		if(chanA_B==1)
		{
			((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(true);	
			((CButton*)GetDlgItem(IDC_CHECK12))->SetCheck(false);	
		}
		else
		{
			((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(false);	
			((CButton*)GetDlgItem(IDC_CHECK12))->SetCheck(true);
		}
		SetDlgItemText(IDC_MESSAGENAME,MessageName);

		
		for(i=0;i<32;i++)
		{
			
			str.Format("%4X",InitData[i]);
			for(j=0;j<4;j++)
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			SetDlgItemText(IDC_EDIT18+i,str);

			//valtype.dblVal = InitData[i];
			//((CCWNumEdit*)GetDlgItem(IDC_CWNUMEDIT1+i))->SetValue(valtype);
		}

		if(MessageTyep==3)//mode
		{
			str.Format("%4X",InitData[0]);
			for(j=0;j<4;j++)
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			SetDlgItemText(IDC_EDIT18+i,str);

			/*
			valtype.dblVal = InitData[0];
//			((CCWNumEdit*)GetDlgItem(IDC_MESSAGENAME2))->SetValue(valtype);
*/
			str.Format("%4X", wcount);

//			SetDlgItemText(IDC_EDIT50,str);

			if(wcount<9) ((CComboBox*)GetDlgItem(IDC_COMBO9))->SetCurSel(wcount);
			else 
			{
				((CComboBox*)GetDlgItem(IDC_COMBO9))->SetCurSel(wcount-7);
				if(wcount==17)
				{
					((CEdit *)GetDlgItem(IDC_EDIT18))->ShowWindow(SW_SHOW);
				}
			}

		}
		
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CMessageSet::OnButtonBCRT() 
{
	// TODO: Add your control notification handler code here
	MessageTyep=0;
	LedShow(0);
}

void CMessageSet::OnButtonRTBC() 
{
	// TODO: Add your control notification handler code here
	MessageTyep=1;
	LedShow(1);
}

void CMessageSet::OnButtonRTRT() 
{
	// TODO: Add your control notification handler code here
	MessageTyep=2;
	LedShow(2);
}

void CMessageSet::OnButtonMODE() 
{
	// TODO: Add your control notification handler code here
	MessageTyep=3;
	LedShow(3);	
}

void CMessageSet::LedShow(int type)
{
	int i;
	/*m_Led_BC_RT.SetValue(false);
	m_Led_RT_BC.SetValue(false);
	m_Led_RT_RT.SetValue(false);
	m_Led_MODE.SetValue(false);
	*/
	m_StutasBCRT.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_StutasRTBC.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_StutasRTRT.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_StutasMODE.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON3));

	((CComboBox*)GetDlgItem(IDC_COMBO4))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_COMBO5))->ShowWindow(SW_HIDE);
	((CComboBox*)GetDlgItem(IDC_COMBO6))->ShowWindow(SW_HIDE);

	

	(GetDlgItem(IDC_CHECKSEND))->ShowWindow(SW_HIDE);
//	(GetDlgItem(IDC_COMBO7))->ShowWindow(SW_HIDE);
//	(GetDlgItem(IDC_STATICM))->ShowWindow(SW_HIDE);
//	(GetDlgItem(IDC_EDIT50))->ShowWindow(SW_HIDE);
	
///	(GetDlgItem(IDC_MESSAGENAME2))->ShowWindow(SW_HIDE);
//	(GetDlgItem(IDC_STATICRET))->ShowWindow(SW_HIDE);

	(GetDlgItem(IDC_COMBO9))->ShowWindow(SW_HIDE);
//	(GetDlgItem(IDC_STATIC15))->ShowWindow(SW_HIDE);
	(GetDlgItem(IDC_STATIC16))->ShowWindow(SW_HIDE);

	CString str;
	m_SubAdress.ResetContent();
	for(i=0;i<32;i++)
	{
		str.Format("%2d",i);
		m_SubAdress.AddString(str);
	}

	for(i=0;i<32;i++)
	{
		((CEdit *)GetDlgItem(IDC_EDIT18+i))->ShowWindow(SW_SHOW);
	}
	
	((CButton *)GetDlgItem(IDC_BUTTON6))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_BUTTON8))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_BUTTON9))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_BUTTON10))->ShowWindow(SW_SHOW);
	((CButton *)GetDlgItem(IDC_BUTTON11))->ShowWindow(SW_SHOW);
	
	
	(GetDlgItem(IDC_STATIC4))->ShowWindow(SW_SHOW);
	(GetDlgItem(IDC_STATIC5))->ShowWindow(SW_SHOW);
	(GetDlgItem(IDC_STATIC6))->ShowWindow(SW_SHOW);
	(GetDlgItem(IDC_STATIC7))->ShowWindow(SW_SHOW);
	(GetDlgItem(IDC_STATIC323))->ShowWindow(SW_SHOW);
	

	(GetDlgItem(IDC_COMBO1))->ShowWindow(SW_SHOW);
	(GetDlgItem(IDC_COMBO2))->ShowWindow(SW_SHOW);
	(GetDlgItem(IDC_COMBO3))->ShowWindow(SW_SHOW);
	(GetDlgItem(IDC_STATIC_ADDGET))->ShowWindow(SW_HIDE);
	(GetDlgItem(IDC_STATIC_ADDSEND))->ShowWindow(SW_HIDE);

	if((subaddr>31)&&(subaddr<0))
		m_SubAdress.SetCurSel(subaddr);
	else
		m_SubAdress.SetCurSel(1);
	switch (type )
	{
		case 0:
			{
				m_StutasBCRT.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
				for(i=0;i<32;i++)
				{
					((CEdit *)GetDlgItem(IDC_EDIT18+i))->EnableWindow(true);
				}
				
				((CButton *)GetDlgItem(IDC_BUTTON6))->EnableWindow(true);
				((CButton *)GetDlgItem(IDC_BUTTON8))->EnableWindow(true);
				((CButton *)GetDlgItem(IDC_BUTTON9))->EnableWindow(true);
				((CButton *)GetDlgItem(IDC_BUTTON10))->EnableWindow(true);
				((CButton *)GetDlgItem(IDC_BUTTON11))->EnableWindow(true);
				
			}
		break;
		case 1:
			{
				m_StutasRTBC.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
				for(i=0;i<32;i++)
				{
					((CEdit *)GetDlgItem(IDC_EDIT18+i))->EnableWindow(false);
				}
				((CButton *)GetDlgItem(IDC_BUTTON6))->EnableWindow(false);
				((CButton *)GetDlgItem(IDC_BUTTON8))->EnableWindow(false);
				((CButton *)GetDlgItem(IDC_BUTTON9))->EnableWindow(false);
				((CButton *)GetDlgItem(IDC_BUTTON10))->EnableWindow(false);
				((CButton *)GetDlgItem(IDC_BUTTON11))->EnableWindow(false);
			}
		break;
		case 2:
			{
				m_StutasRTRT.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));

				for(i=0;i<32;i++)
				{
					((CEdit *)GetDlgItem(IDC_EDIT18+i))->EnableWindow(false);
				}
				((CButton *)GetDlgItem(IDC_BUTTON6))->EnableWindow(false);
				((CButton *)GetDlgItem(IDC_BUTTON8))->EnableWindow(false);
				((CButton *)GetDlgItem(IDC_BUTTON9))->EnableWindow(false);
				((CButton *)GetDlgItem(IDC_BUTTON10))->EnableWindow(false);
				((CButton *)GetDlgItem(IDC_BUTTON11))->EnableWindow(false);

				((CComboBox*)GetDlgItem(IDC_COMBO3))->ShowWindow(SW_HIDE);

				((CComboBox*)GetDlgItem(IDC_COMBO4))->ShowWindow(SW_SHOW);
				((CComboBox*)GetDlgItem(IDC_COMBO5))->ShowWindow(SW_SHOW);
				((CComboBox*)GetDlgItem(IDC_COMBO6))->ShowWindow(SW_SHOW);

				(GetDlgItem(IDC_STATIC_ADDGET))->ShowWindow(SW_SHOW);
				(GetDlgItem(IDC_STATIC_ADDSEND))->ShowWindow(SW_SHOW);
			}
		break;
		case 3:
			{
				m_SubAdress.SetCurSel(31);
				m_StutasMODE.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON2));
//				(GetDlgItem(IDC_COMBO7))->ShowWindow(SW_SHOW);

				(GetDlgItem(IDC_CHECKSEND))->ShowWindow(SW_SHOW);
//				(GetDlgItem(IDC_STATICM))->ShowWindow(SW_SHOW);
//				(GetDlgItem(IDC_EDIT50))->ShowWindow(SW_SHOW);
//				(GetDlgItem(IDC_MESSAGENAME2))->ShowWindow(SW_SHOW);
//				(GetDlgItem(IDC_STATICRET))->ShowWindow(SW_SHOW);


				(GetDlgItem(IDC_COMBO9))->ShowWindow(SW_SHOW);
//				(GetDlgItem(IDC_STATIC15))->ShowWindow(SW_SHOW);
				(GetDlgItem(IDC_STATIC16))->ShowWindow(SW_SHOW);

				for(i=0;i<32;i++)
				{
					((CEdit *)GetDlgItem(IDC_EDIT18+i))->ShowWindow(SW_HIDE);
				}
				((CButton *)GetDlgItem(IDC_BUTTON6))->ShowWindow(SW_HIDE);
				((CButton *)GetDlgItem(IDC_BUTTON8))->ShowWindow(SW_HIDE);
				((CButton *)GetDlgItem(IDC_BUTTON9))->ShowWindow(SW_HIDE);
				((CButton *)GetDlgItem(IDC_BUTTON10))->ShowWindow(SW_HIDE);
				((CButton *)GetDlgItem(IDC_BUTTON11))->ShowWindow(SW_HIDE);

				(GetDlgItem(IDC_STATIC4))->ShowWindow(SW_HIDE);
				(GetDlgItem(IDC_STATIC5))->ShowWindow(SW_HIDE);
				(GetDlgItem(IDC_STATIC6))->ShowWindow(SW_HIDE);
				(GetDlgItem(IDC_STATIC7))->ShowWindow(SW_HIDE);

				(GetDlgItem(IDC_COMBO1))->ShowWindow(SW_SHOW);
				(GetDlgItem(IDC_COMBO2))->ShowWindow(SW_SHOW);
				(GetDlgItem(IDC_COMBO3))->ShowWindow(SW_HIDE);
				(GetDlgItem(IDC_STATIC11))->ShowWindow(SW_SHOW);
				(GetDlgItem(IDC_STATIC12))->ShowWindow(SW_SHOW);
				(GetDlgItem(IDC_STATIC13))->ShowWindow(SW_HIDE);
				(GetDlgItem(IDC_STATIC323))->ShowWindow(SW_HIDE);

				m_SubAdress.ResetContent();
				str.Format("%2d",0);
				m_SubAdress.AddString(str);

				str.Format("%2d",31);
				m_SubAdress.AddString(str);
				m_SubAdress.SetCurSel(1);
				
			}
		break;
	}
}


void CMessageSet::OnSetFocus(CWnd* pOldWnd) 
{
	CDialog::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	
}




void CMessageSet::OnOK() 
{
	// TODO: Add extra validation here
	//根据配置的消息对消息赋值
	
}



void CMessageSet::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
	
}

void CMessageSet::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		IniType = 0;
	}
	else
	{
		IniType = 1;
	}
}

void CMessageSet::OnRadio17() 
{
	// TODO: Add your control notification handler code here
	
}



void CMessageSet::OnSelchangeCombo9() 
{
	// TODO: Add your control notification handler code here
	int Selecte;
	int i;

	Selecte= (((CComboBox*)GetDlgItem(IDC_COMBO9))->GetCurSel());

	((CButton *)GetDlgItem(IDC_CHECKSEND))->SetCheck(false);

	for(i=0;i<32;i++)
	{
		((CEdit *)GetDlgItem(IDC_EDIT18+i))->ShowWindow(SW_HIDE);
	}

	switch (Selecte)
	{
	  case 0:

		Mode = 0;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);
		tran_rec_Mode =1;
		
		break;
	  case 1:
		  Mode = 1;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		tran_rec_Mode = 1;
		break;
	  case 2:
		  Mode = 2;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		
		tran_rec_Mode =1;
		break;
	  case 3:
		  Mode = 3;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		tran_rec_Mode =1;
		break;
	  case 4:
		  Mode = 4;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);
		tran_rec_Mode =1;

		break;
	  case 5:
		  Mode = 5;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		tran_rec_Mode =1;
		break;
	  case 6:
		  Mode = 6;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		tran_rec_Mode =1;
		break;
	  case 7:
		  Mode = 7;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		tran_rec_Mode =1;
		break;
	  case 8:
		  Mode = 8;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		tran_rec_Mode =1;
		break;
	  case 9:
		  Mode = 16;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		
		tran_rec_Mode =1;
		break;
	  case 10:
		  Mode = 17;

		((CEdit *)GetDlgItem(IDC_EDIT18))->ShowWindow(SW_SHOW);

///		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		
		tran_rec_Mode =0;
		break;
	  case 11:
		  Mode = 18;
//		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		
		tran_rec_Mode =1;
		break;
	  case 12:
		  Mode = 19;
////		GetDlgItem(IDC_MESSAGENAME2)->EnableWindow(false);

		
		tran_rec_Mode =1;
		break;
	  case 13:
		  Mode = 20;

		tran_rec_Mode =0;
		break;
	  case 14:
		  Mode = 21;


		tran_rec_Mode =0;
		break;
	}
	if(tran_rec_Mode==1)
		((CButton *)GetDlgItem(IDC_CHECKMODESEND))->SetCheck(true);
	else	((CButton *)GetDlgItem(IDC_CHECKMODESEND))->SetCheck(false);
	wcount_mode =  Mode ;
	CString str;
	str.Format("%4X",wcount_mode);
//	SetDlgItemText(IDC_EDIT50,str);	

}

void CMessageSet::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	if(((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck())
	{
		m_RTAdress.SetCurSel(31);
	}
}



void CMessageSet::OnCheck8() 
{
	// TODO: Add your control notification handler code here
	
}



void CMessageSet::OnButtonCreateRond() 
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

void CMessageSet::OnButtonCreatezero() 
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

void CMessageSet::OnButtonCreataff() 
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

void CMessageSet::OnButtonCreateadd() 
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

void CMessageSet::OnButton11() 
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

void CMessageSet::OnButton13() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
int CMessageSet::chartoint(char val)
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
int CMessageSet::HexToInt(CString str,int len)
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
void CMessageSet::OnButtonOK() 
{
	// TODO: Add your control notification handler code here
	int i,j;
	CString str;
	int gap_time;
	VARIANT valtype;
	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	GetDlgItemText(ID_BCPRO_BCFRAMETIME,str);
	gap_time = atoi(str);

	if(NowAddMessageTyep==1)
	{
		
		if(IniType==0)//插入新数据模式
		{
			nowMessageNo = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_MessageMaxCount;//
			//memset(&m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo],0,sizeof(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo])); 
		}
		if(((CButton *)GetDlgItem(IDC_CHECK8))->GetCheck())
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCRetry_Flag [nowMessageNo] = true;
		else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCRetry_Flag [nowMessageNo] = false;
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control = 0;
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].messno= (unsigned short)nowMessageNo;
		//CString Str;
		
		if(MessageTyep==0)//BC->RT
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control = BC_CONTROL_MESSAGE;

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.rtaddr = m_RTAdress.GetCurSel();//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.subaddr = m_SubAdress.GetCurSel();//子地址
			//int mmfe = m_WCount.GetCurSel();
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.wcount = m_WCount.GetCurSel()+1;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.tran_rec = 0;//方向 0接收，1发送 
			
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.rtaddr = 0;//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.subaddr = 0;//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.wcount = 0;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.tran_rec = 0;//方向
//			GetDlgItemText(IDC_EDIT18,str);
			for(i=0;i<32;i++)
			{
				GetDlgItemText(IDC_EDIT18+i,str);
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].data[0][i] = HexToInt(str,4);
				//valtype = ((CCWNumEdit *)GetDlgItem(IDC_CWNUMEDIT1+i))->GetValue();
				//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].data[0][i] = valtype.dblVal;
			}
		}
		else if(MessageTyep==1)//RT->BC
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control = BC_CONTROL_MESSAGE;
			
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.rtaddr = m_RTAdress.GetCurSel();//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.subaddr = m_SubAdress.GetCurSel();//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.wcount =m_WCount.GetCurSel()+1;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.tran_rec = 1;//方向 0接收，1发送 

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.rtaddr = 0;//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.subaddr = 0;//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.wcount = 0;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.tran_rec = 0;//方向
		}
		else if(MessageTyep==2)//RT->RT
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control = BC_CONTROL_MESSAGE;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control |= BC_CONTROL_RTRTFORMAT;//RT->RT

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.rtaddr = m_RTAdress.GetCurSel();//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.subaddr = m_SubAdress.GetCurSel();//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.wcount = m_WCount2.GetCurSel()+1;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.tran_rec = 0;//方向 0接收，1发送 

			for(i=0;i<32;i++)
			{
				GetDlgItemText(IDC_EDIT18+i,str);
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].data[0][i] = HexToInt(str,4);
				

				//valtype = ((CCWNumEdit *)GetDlgItem(IDC_CWNUMEDIT1+i))->GetValue();
				//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].data[0][i] = valtype.dblVal;
			}

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.rtaddr = m_RTAdress2.GetCurSel();//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.subaddr = m_SubAdress2.GetCurSel();//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.wcount = m_WCount2.GetCurSel()+1;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.tran_rec = 1;//方向
		}

		else if(MessageTyep==3)//MODE
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control =  BC_CONTROL_MESSAGE;//

			UpdateData(true);
			OnSelchangeCombo9();

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.rtaddr = m_RTAdress.GetCurSel();//地址
			if(m_SubAdress.GetCurSel()==0)
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.subaddr = 0;//子地址
			else
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.subaddr = 31;//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.wcount = Mode;//m_WCount.GetCurSel()+1;//WORD COUNT
		
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.tran_rec = tran_rec_Mode;//方向 0接收，1发送 
			

			GetDlgItemText(IDC_EDIT18,str);
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].data[0][0] = HexToInt(str,4);

		
		}

		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].errorid				= 0;		// Error injection buffer ID, no err inj
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].gap_time				= gap_time;		// Intermessage gap time in microseconds
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].status				= 0;		// Message error status (hardware will control this)

		int val_Chan;
		if(((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck()==true)
			val_Chan = 1;
		else val_Chan = 0;
		if(val_Chan==1)//A通道
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].chanA_B[nowMessageNo] = 1;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
		}
		else	if(val_Chan==0)//B通道
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].chanA_B[nowMessageNo] = 0;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control |= BC_CONTROL_CHANNELB;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].control |= BC_CONTROL_BUFFERA;
		}
		CString inSertName;
		this->GetDlgItemText(IDC_MESSAGENAME,inSertName);
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName[nowMessageNo] = inSertName;
		if(MessageTyep==0)
			inSertName.Format("%s-%s:rt%2d-sub%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName[nowMessageNo],"BC->RT",m_RTAdress.GetCurSel(),m_SubAdress.GetCurSel());
		else if(MessageTyep==1)
			inSertName.Format("%s-%s:rt%2d-sub%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName[nowMessageNo],"RT->BC",m_RTAdress.GetCurSel(),m_SubAdress.GetCurSel());
		else if(MessageTyep==2)
			inSertName.Format("%s-%s:rt%2d-sub%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName[nowMessageNo],"RT->RT",m_RTAdress.GetCurSel(),m_SubAdress.GetCurSel());
		
		else if(MessageTyep==3)
			inSertName.Format("%s-%s:rt%2d-sub%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName[nowMessageNo],"MODE",m_RTAdress.GetCurSel(),m_SubAdress.GetCurSel());
		

		if(IniType==0) m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].InsertTreeData(10,inSertName,nowMessageNo);
		if(IniType==1) m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].ChangeTreeData(10,inSertName,nowMessageNo);

		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageTyep[nowMessageNo] = MessageTyep;
		//////////显示到消息BCVIEW中/////
		if(IniType==0)//插入新数据模式
		{
			m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.InsertItem(nowMessageNo,0);
			m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.AddNewItem(nowMessageNo);
		}
		inSertName.Format("%2d",nowMessageNo);
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,0,inSertName);
		this->GetDlgItemText(IDC_MESSAGENAME,inSertName);
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,1,inSertName);
		if(MessageTyep==0) inSertName.Format("%s","BC->RT");
		if(MessageTyep==1) inSertName.Format("%s","RT->BC");
		if(MessageTyep==2) inSertName.Format("%s","RT->RT");
		if(MessageTyep==3) inSertName.Format("%s","MODE");
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,2,inSertName);

		
		////显示地址和子地址
		if(MessageTyep==2) inSertName.Format("%2d/%2d",m_RTAdress.GetCurSel(),m_RTAdress2.GetCurSel());
		
		else inSertName.Format("%2d",m_RTAdress.GetCurSel());

		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,3,inSertName);
		
		if(MessageTyep==2) inSertName.Format("%2d/%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.subaddr,m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.subaddr);
		else inSertName.Format("%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.subaddr);

		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,4,inSertName);
		/////////////////////////
		if(val_Chan==0)
			inSertName.Format("通道%S","B");
		else inSertName.Format("通道%S","A");
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,5,inSertName);

		if(MessageTyep==2)
		{
			if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.wcount==0)
				inSertName.Format("%2d",32);	
			else inSertName.Format("%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.wcount);

		}
		else
		{
			if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.wcount==0)
				inSertName.Format("%2d",32);	
			else inSertName.Format("%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.wcount);
		}
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,6,inSertName);

		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCMessageEnabel[nowMessageNo] = true;
	//	m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,7,"激活");


		//CString str;
		if(MessageTyep==0) 
		for(i=0;i<32;i++)
		{
			str.Format("0X:%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].data[0][i]);
			for(j=3;j<7;j++) 
			{
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			}
			m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,8+i,str);
		}
		else	for(i=0;i<32;i++)
			m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList.SetItemText(nowMessageNo,8+i,"");

		/////////////////////////////////
		if(IniType==0)//插入新数据模式
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_MessageMaxCount++;
		
	//	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].SetMessageTeam();//组织消息
		////////////////////////////
	}
	else if(NowAddMessageTyep==2)//非周期消息
	{
		if(IniType==0)//插入新数据模式
			nowMessageNo = m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_MessageMaxCount_2;//

		
		if(((CButton *)GetDlgItem(IDC_CHECK8))->GetCheck())
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCRetry_Flag_2 [nowMessageNo] = true;
		else m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCRetry_Flag_2 [nowMessageNo] = false;

		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].messno= (unsigned short)nowMessageNo;
		
		GetDlgItemText(ID_BCPRO_BCFRAMETIME,str);
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].gap_time = atoi(str);
		if(MessageTyep==0)//BC->RT
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].control = BC_CONTROL_MESSAGE;

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.rtaddr = m_RTAdress.GetCurSel();//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.subaddr = m_SubAdress.GetCurSel();//子地址
			int mmfe = m_WCount.GetCurSel();
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.wcount = m_WCount.GetCurSel()+1;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.tran_rec = 0;//方向 0接收，1发送 
			
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.rtaddr = 0;//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.subaddr = 0;//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.wcount = 0;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.tran_rec = 0;//方向
			for(i=0;i<32;i++)
			{
				GetDlgItemText(IDC_EDIT18+i,str);
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].data[0][i] = HexToInt(str,4);
				
				//valtype = ((CCWNumEdit *)GetDlgItem(IDC_CWNUMEDIT1+i))->GetValue();
				//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].data[0][i] = valtype.dblVal;
			}
		}
		else if(MessageTyep==1)//RT->BC
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].control = BC_CONTROL_MESSAGE;
			
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.rtaddr = m_RTAdress.GetCurSel();//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.subaddr = m_SubAdress.GetCurSel();//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.wcount =m_WCount.GetCurSel()+1;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.tran_rec = 1;//方向 0接收，1发送 

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.rtaddr = 0;//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.subaddr = 0;//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.wcount = 0;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.tran_rec = 0;//方向
		}
		else if(MessageTyep==2)//RT->RT
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].control = BC_CONTROL_RTRTFORMAT;//RT->RT

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.rtaddr = m_RTAdress.GetCurSel();//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.subaddr = m_SubAdress.GetCurSel();//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.wcount = m_WCount.GetCurSel()+1;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.tran_rec = 1;//方向 0接收，1发送 

			for(i=0;i<32;i++)
			{
				GetDlgItemText(IDC_EDIT18+i,str);
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].data[0][i] = HexToInt(str,4);
				
				//valtype = ((CCWNumEdit *)GetDlgItem(IDC_CWNUMEDIT1+i))->GetValue();
				//m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].data[0][i] = valtype.dblVal;
			}

			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.rtaddr = m_RTAdress2.GetCurSel();//地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.subaddr = m_SubAdress2.GetCurSel();//子地址
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.wcount = 0;//m_WCount2.GetCurSel()+1;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command2.tran_rec = 1;//方向
		}

		else if(MessageTyep==3)//MODE
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].control =  BC_CONTROL_MFRAME_BEG;//

			UpdateData(true);
			OnSelchangeCombo9();
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.rtaddr = m_RTAdress.GetCurSel();//地址
			if(m_SubAdress.GetCurSel()==0)
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.subaddr = 0;//子地址
			else
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.subaddr = 31;//子地址
			
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.wcount = Mode;//m_WCount.GetCurSel()+1;//WORD COUNT
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.tran_rec = tran_rec_Mode;//方向 0接收，1发送 
			
			GetDlgItemText(IDC_EDIT18,str);
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].data[0][0] = HexToInt(str,4);

		}

		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].errorid				= 0;		// Error injection buffer ID, no err inj
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].gap_time				= gap_time;		// Intermessage gap time in microseconds
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].status				= 0;		// Message error status (hardware will control this)

		int val_Chan;
		if(((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck()==true)
			val_Chan= 1;
		else val_Chan= 0;
		if(val_Chan==1)//A通道
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].chanA_B_2[nowMessageNo] = 1;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].control |= BC_CONTROL_CHANNELA;	// Send message on bus A (primary).
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].control |= BC_CONTROL_BUFFERA;	// Only using one buffer, buffer A.
		}
		else	if(val_Chan==0)//B通道
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].chanA_B_2[nowMessageNo] = 0;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].control |= BC_CONTROL_CHANNELB;
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].control |= BC_CONTROL_BUFFERA;
		}
		CString inSertName;
		this->GetDlgItemText(IDC_MESSAGENAME,inSertName);
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName_2[nowMessageNo] = inSertName;
		if(MessageTyep==0)
			inSertName.Format("%s-%s:rt%2d-sub%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName_2[nowMessageNo],"BC->RT",m_RTAdress.GetCurSel(),m_SubAdress.GetCurSel());
		else if(MessageTyep==1)
			inSertName.Format("%s-%s:rt%2d-sub%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName_2[nowMessageNo],"RT->BC",m_RTAdress.GetCurSel(),m_SubAdress.GetCurSel());
		else if(MessageTyep==2)
			inSertName.Format("%s-%s:rt%2d-sub%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName_2[nowMessageNo],"RT->RT",m_RTAdress.GetCurSel(),m_SubAdress.GetCurSel());
		
		else if(MessageTyep==3)
			inSertName.Format("%s-%s:rt%2d-sub%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageName_2[nowMessageNo],"MODE",m_RTAdress.GetCurSel(),m_SubAdress.GetCurSel());
		

		if(IniType==0) m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].InsertTreeData(11,inSertName,nowMessageNo);
		if(IniType==1) m_pMainWnd->TabProjDlg.ProjectDlg[m_pMainWnd->m_now_SelectChannel].ChangeTreeData(11,inSertName,nowMessageNo);

		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].MessageTyep_2[nowMessageNo] = MessageTyep;
		//////////显示到消息BCVIEW中/////
		if(IniType==0)//插入新数据模式
		{
			m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.InsertItem(nowMessageNo,0);
			m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.AddNewItem(nowMessageNo);
		}
		inSertName.Format("%2d",nowMessageNo);
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,0,inSertName);
		this->GetDlgItemText(IDC_MESSAGENAME,inSertName);
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,1,inSertName);
		if(MessageTyep==0) inSertName.Format("%s","BC->RT");
		if(MessageTyep==1) inSertName.Format("%s","RT->BC");
		if(MessageTyep==2) inSertName.Format("%s","RT->RT");
		if(MessageTyep==3) inSertName.Format("%s","MODE");
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,2,inSertName);

		
		////显示地址和子地址
		if(MessageTyep==2) inSertName.Format("%2d/%2d",m_RTAdress.GetCurSel(),m_RTAdress2.GetCurSel());
		else inSertName.Format("%2d",m_RTAdress.GetCurSel());

		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,3,inSertName);
		
		if(MessageTyep==2)
		{
			if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.wcount==0)
				inSertName.Format("%2d",32);	
			else inSertName.Format("%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command2.wcount);

		}
		else
		{
			if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.wcount==0)
				inSertName.Format("%2d",32);	
			else inSertName.Format("%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data[nowMessageNo].mess_command1.wcount);
		}
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,4,inSertName);
		/////////////////////////
		if(val_Chan==0)
			inSertName.Format("通道%S","B");
		else inSertName.Format("通道%S","A");
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,5,inSertName);

		if(m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.wcount==0)
			inSertName.Format("%2d",32);	
		else inSertName.Format("%2d",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].mess_command1.wcount);

		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,6,inSertName);
		m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BCNoTiemMessageEnabel[nowMessageNo] = true;
		m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,7,"激活");


		//CString str;
		if(MessageTyep==0) 
		for(i=0;i<32;i++)
		{
			str.Format("0X:%4X",m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].bc_msg_data_2[nowMessageNo].data[0][i]);
			for(j=3;j<7;j++) 
			{
				if(str.GetAt(j)==' ') str.SetAt(j,'0');
			}
			m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,8+i,str);
		}
		else	for(i=0;i<32;i++)
				m_pMainWnd->BCView[m_pMainWnd->m_now_SelectChannel].m_BC_MesList2.SetItemText(nowMessageNo,8+i,"");
		/////////////////////////////////
		if(IniType==0)//插入新数据模式
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].BC_MessageMaxCount_2++;
		
	//	m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].SetMessageTeam();//组织消息
		////////////////////////////
	}
	CDialog::OnOK();
}

void CMessageSet::OnCheck7() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck())
	{
		chanA_B = 0;
		((CButton*)GetDlgItem(IDC_CHECK12))->SetCheck(false);
	}
	else
	{
		chanA_B = 1;
		((CButton*)GetDlgItem(IDC_CHECK12))->SetCheck(true);
	}
}

void CMessageSet::OnCheck12() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK12))->GetCheck())
	{
		chanA_B = 1;
		((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(false);
	}
	else
	{
		chanA_B = 0;
		((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(true);

	}
}
