// ManCtrl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ManCtrl.h"

#include "MainFrm.h"
#include "ManCtrlDoc.h"
#include "ManCtrlView.h"
#include "FlashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy1553App

BEGIN_MESSAGE_MAP(CMy1553App, CWinApp)
	//{{AFX_MSG_MAP(CMy1553App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy1553App construction

CMy1553App::CMy1553App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMy1553App object

CMy1553App theApp;

/////////////////////////////////////////////////////////////////////////////
// CMy1553App initialization

BOOL CMy1553App::InitInstance()
{
	// Initialize OLE libraries
		CString Filestr;
		SetDialogBkColor(RGB(237,246,255), RGB(0, 0, 0) );
	//	if (m_lpCmdLine[0] == _T('\0'))
	   {

	   }
	 //  else
	   {
		  // Open a file passed as the first command line parameter.
		 // pMainFrame->ReadMessageSetFunctiong(m_lpCmdLine);
		   Filestr.Format(m_lpCmdLine);
		  WritePrivateProfileString("BM_Config","dakai",Filestr,"c:\\test.txt");
	   }
//		

	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(2);  // Load standard INI file options (including MRU)


	


	CFlashDlg FlashDlg;

	if(FlashDlg.DoModal()==IDOK)
	{
		CMainFrame* pMainFrame = new CMainFrame;
		if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
			return FALSE;
		m_pMainWnd = pMainFrame;

		//m_pMainWnd->DragAcceptFiles();
		// Parse command line for standard shell commands, DDE, file open


	
		// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	
	
		EnableShellOpen(); 
		//RegisterShellFileTypes();

		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;

	
		return TRUE;
	}

	else return false;

}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMy1553App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMy1553App message handlers


CDocument* CMy1553App::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	// TODO: Add your specialized code here and/or call the base class

	return NULL;// CWinApp::OpenDocumentFile(lpszFileName);
}
