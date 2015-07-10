// ManCtrl.h : main header file for the ManCtrl application
//

#if !defined(AFX_1553_H__77075C44_EC45_416D_B60C_06878D290B8F__INCLUDED_)
#define AFX_1553_H__77075C44_EC45_416D_B60C_06878D290B8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "TypeDefine.h"

/////////////////////////////////////////////////////////////////////////////
// CMy1553App:
// See ManCtrl.cpp for the implementation of this class
//

class CMy1553App : public CWinApp
{
public:
	CMy1553App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1553App)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy1553App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1553_H__77075C44_EC45_416D_B60C_06878D290B8F__INCLUDED_)
