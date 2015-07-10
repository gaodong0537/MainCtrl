// BCPROPER.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "BCPROPER.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCPROPER dialog


CBCPROPER::CBCPROPER(CWnd* pParent /*=NULL*/)
	: CDialog(CBCPROPER::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBCPROPER)
	m_BCcount = 0;
	m_Frametimer = 0;
	m_Graptimer = 0;
	//}}AFX_DATA_INIT
}


void CBCPROPER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBCPROPER)
	DDX_Text(pDX, ID_BCPRO_BCCOUNT, m_BCcount);
	DDX_Text(pDX, ID_BCPRO_BCFRAMETIME, m_Frametimer);
	DDX_Text(pDX, ID_BCPRO_BCGRAP, m_Graptimer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBCPROPER, CDialog)
	//{{AFX_MSG_MAP(CBCPROPER)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK15, OnCheck15)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK10, OnCheck10)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_BN_CLICKED(IDC_CHECK12, OnCheck12)
	ON_BN_CLICKED(IDC_CHECK13, OnCheck13)
	ON_BN_CLICKED(IDC_CHECK14, OnCheck14)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCPROPER message handlers

BOOL CBCPROPER::OnInitDialog() 
{
	CDialog::OnInitDialog();

	VARIANT valtype;
	// TODO: Add extra initialization here
	
	m_BCcount=Maxcount;
	m_Frametimer=frameTime;

	m_Graptimer=GrapTime;



	UpdateData(false);

	int i;
	CString str;
	for(i=0;i<8;i++)
	{
		str.Format("%d次",i);
		((CComboBox *)GetDlgItem(IDC_COMBO1))->InsertString(i,str);
		
	}
	for(i=0;i<8;i++)
	if(multiple_retryval.multiple_retry[i]==RETRY_END)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO1))->SetCurSel(i);
		break;
	}
	if(multiple_retryval.multiple_retry[0]==RETRY_SAME_BUS)
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(false);
	else 
		((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(true);


	if(multiple_retryval.multiple_retry[1]==RETRY_SAME_BUS)
		((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(false);
	else 
		((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(true);

	if((wRetry	& BC_RETRY_ALTB)==BC_RETRY_ALTB)
		((CButton*)GetDlgItem(IDC_CHECK15))->SetCheck(true);
	else ((CButton*)GetDlgItem(IDC_CHECK15))->SetCheck(false);

	if((wRetry	& BC_RETRY_NRSP)==BC_RETRY_NRSP)
		((CButton*)GetDlgItem(IDC_CHECK9))->SetCheck(true);
	else ((CButton*)GetDlgItem(IDC_CHECK9))->SetCheck(false);

	if((wRetry	& BC_RETRY_ME)==BC_RETRY_ME)
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(true);
	else ((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(false);

	if((wRetry	& BC_RETRY_BUSY)==BC_RETRY_BUSY)
		((CButton*)GetDlgItem(IDC_CHECK10))->SetCheck(true);
	else ((CButton*)GetDlgItem(IDC_CHECK10))->SetCheck(false);

	if((wRetry	& BC_RETRY_TF)==BC_RETRY_TF)
		((CButton*)GetDlgItem(IDC_CHECK11))->SetCheck(true);
	else ((CButton*)GetDlgItem(IDC_CHECK11))->SetCheck(false);

	if((wRetry	& BC_RETRY_SSF)==BC_RETRY_SSF)
		((CButton*)GetDlgItem(IDC_CHECK12))->SetCheck(true);
	else ((CButton*)GetDlgItem(IDC_CHECK12))->SetCheck(false);

	if((wRetry	& BC_RETRY_INSTR)==BC_RETRY_INSTR)
		((CButton*)GetDlgItem(IDC_CHECK13))->SetCheck(true);
	else ((CButton*)GetDlgItem(IDC_CHECK13))->SetCheck(false);


	if((wRetry	& BC_RETRY_SRQ)==BC_RETRY_SRQ)
		((CButton*)GetDlgItem(IDC_CHECK14))->SetCheck(true);
	else ((CButton*)GetDlgItem(IDC_CHECK14))->SetCheck(false);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBCPROPER::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	if(m_Frametimer<1000)
	{
		MessageBox("周期最小为1000微秒","注意",MB_OK);
		m_Frametimer = 1000;
	}
	else
	{
		frameTime=m_Frametimer;

		GrapTime=m_Graptimer;

		CDialog::OnOK();
	}
}

void CBCPROPER::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	int RetryTime;
	RetryTime = ((CComboBox *)GetDlgItem(IDC_COMBO1))->GetCurSel();
	if(RetryTime>0)
	{
		multiple_retryval.multiple_retry[RetryTime]=RETRY_END;
		multiple_retryval.retryFlag = true;
	}
	else
	{
		multiple_retryval.multiple_retry[RetryTime]=RETRY_END;
		multiple_retryval.retryFlag = false;
	}
}

void CBCPROPER::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck())
		multiple_retryval.multiple_retry[0]=RETRY_ALTERNATE_BUS;
	else 
		multiple_retryval.multiple_retry[0]=RETRY_SAME_BUS;
}

void CBCPROPER::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck())
		multiple_retryval.multiple_retry[1]=RETRY_ALTERNATE_BUS;
	else 
		multiple_retryval.multiple_retry[1]=RETRY_SAME_BUS;
}

void CBCPROPER::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	
}

void CBCPROPER::OnCheck15() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK15))->GetCheck())
		wRetry	|= BC_RETRY_ALTB;
	else wRetry	&= ~BC_RETRY_ALTB;
}

void CBCPROPER::OnCheck9() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK9))->GetCheck())
		wRetry	|= BC_RETRY_NRSP;
	else wRetry	&= ~BC_RETRY_NRSP;
}

void CBCPROPER::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
		wRetry	|= BC_RETRY_ME;
	else wRetry	&= ~BC_RETRY_ME;
}

void CBCPROPER::OnCheck10() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK10))->GetCheck())
		wRetry	|= BC_RETRY_BUSY;
	else wRetry	&= ~BC_RETRY_BUSY;
}

void CBCPROPER::OnCheck11() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK11))->GetCheck())
		wRetry	|= BC_RETRY_TF;
	else wRetry	&= ~BC_RETRY_TF;
}

void CBCPROPER::OnCheck12() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK12))->GetCheck())
		wRetry	|= BC_RETRY_SSF;
	else wRetry	&= ~BC_RETRY_SSF;
}

void CBCPROPER::OnCheck13() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK13))->GetCheck())
		wRetry	|= BC_RETRY_INSTR;
	else wRetry	&= ~BC_RETRY_INSTR;
}

void CBCPROPER::OnCheck14() 
{
	// TODO: Add your control notification handler code here
	if(((CButton*)GetDlgItem(IDC_CHECK14))->GetCheck())
		wRetry	|= BC_RETRY_SRQ;
	else wRetry	&= ~BC_RETRY_SRQ;
}
