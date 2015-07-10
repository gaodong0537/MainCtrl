// WorkModeSelect.cpp : implementation file
//

#include "stdafx.h"
#include "ManCtrl.h"
#include "WorkModeSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkModeSelect dialog


CWorkModeSelect::CWorkModeSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkModeSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWorkModeSelect)
	m_bmmode = true;
	m_rtmode = true;
	m_bcmode = true;
	//}}AFX_DATA_INIT
}


void CWorkModeSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkModeSelect)
	DDX_Check(pDX, IDC_CHECK3, m_bmmode);
	DDX_Check(pDX, IDC_CHECK2, m_rtmode);
	DDX_Check(pDX, IDC_CHECK1, m_bcmode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorkModeSelect, CDialog)
	//{{AFX_MSG_MAP(CWorkModeSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkModeSelect message handlers

void CWorkModeSelect::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CWorkModeSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
