// ManCtrlDoc.h : interface of the CMy1553Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_1553DOC_H__7B90F2E9_79C2_4793_A0C0_2EFE6853B76E__INCLUDED_)
#define AFX_1553DOC_H__7B90F2E9_79C2_4793_A0C0_2EFE6853B76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMy1553Doc : public COleDocument
{
protected: // create from serialization only
	CMy1553Doc();
	DECLARE_DYNCREATE(CMy1553Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1553Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMy1553Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMy1553Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1553DOC_H__7B90F2E9_79C2_4793_A0C0_2EFE6853B76E__INCLUDED_)
