// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__3B091B00_5FE4_4CA9_A7CE_242C8695C72B__INCLUDED_)
#define AFX_MAINFRM_H__3B091B00_5FE4_4CA9_A7CE_242C8695C72B__INCLUDED_

#include "TypeDefine.h"	// Added by ClassView
#include "Project.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MessageSet.h"
#include "BCviewDlg.h"
#include "RTviewDlg.h"
#include "BMview.h"
#include "TabProjDlg.h"
//#include "VCKBASEDlg.h"	// Added by ClassView
#include "CoolTabCtrl.h"	// Added by ClassView
#include "1553select.h"

class CMainFrame : public CMDIFrameWnd
{

	/*------------------------------------------------------------------------*
 * MIL-1553 状态参数定义
*------------------------------------------------------------------------*/
#define BT1553_BC_EN                         0x2000     //BC有效
#define BT1553_RT_EN                         0x1000     //RT有效
#define BT1553_NO_RESP                       0x0400     //消息无响应错误
#define BT1553_LATE_RESP1                    0x0200     //状态响应1时间超时错误
#define BT1553_LATE_RESP2                    0x0100     //状态响应2时间超时错误
#define BT1553_RESP_WRONG_BUS                0x0080     //发送消息响应在错误通道
#define BT1553_VALID_CMD1                    0x0040     //命令字1有效
#define BT1553_VALID_CMD2                    0x0020     //命令字1有效
#define BT1553_VALID_STATUS1                 0x0010     //状态字1有效
#define BT1553_VALID_STATUS2                 0x0008     //状态字2有效
#define BT1553_VALID_WORD                    0x0004     //数据字有效
#define BT1553_IN_B_BUS                      0x0002     //消息在B通道
#define BT1553_IN_A_BUS                      0x0001     //消息在A通道

/*------------------------------------------------------------------------*/


	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
//	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:

	void ShowProject_Channel(int ShowChennel);

	void MoveBCMessageto(int tyep,int fp,int lp);
	void MoveUpBCMessage();
	void MoveDownBCMessage();
	CCoolBar		m_wndMyBar1;
	CCoolBar		m_wndMyBarCtrl;
	CToolBar		m_wndToolBar;
	CCoolTabCtrl	m_TabCtrl;
	void SendMessgeNowSelecte(int TypeMessage,int MessageID);
	bool CheckFiltration(API_BM_MBUF messge);
	void SendNotimeMessage();
	int NowAddMessageType;
	void CPropRT();
	void EditRTdata();
	void BM_NoGetData();
	void BM_GetData();
	bool BM_GetFlag;
	void DeleteRT();
	
	void View_RT();
	void View_BM();
	void View_BC();
	void NewSetMessage();
	void StopRT();
	void RunRT();
	void OnProper();
	void StepRun();
	void OpenMessageSet();
	void InitAllSet();
	void ReadMessageSet(CString FileNameGet);
	bool SaveMessageSet();
	void GetMessageData();
	void ShowMessageData(int m_channelshow);
	int NowSelectRT;
	void RT_Disable();
	void RT_Enable();
	void ShowRTdata();
	void ShowProject();
	void InsertRTData();
	void SaveMessageTeam();
	void ReadMessageTeam();
	
	void OpenCurrent1();
	void OpenCurrent2();
	void OpenCurrent3();

	void EnableMessge();
	void DisableMessge();

	void SetRTViewData(int rtadress,int subadress,API_RT_MBUF_WRITE data,bool flag);
	void StopBC();
	void RunBC();
	void FlashConfigProject(CString FileStr);
	void FlashMenu();
	CBCViewDlg BCView[8];
	CBMview BMView[8];
	CRTViewDlg RTView[8][32];



	int m_now_SelectChannel;


	int NowdeletID;
	Message_DataType GetData;

	CTabProjDlg TabProjDlg;
	C1553select Tab1553Sel;

	bool bcmode;
	bool rtmode;
	bool bmmode;
	bool TimeShowFlag;//实时显示
	bool HightSpeedMode;
	TypeDefine MessageData1553[8];


	
	 HMENU hMenuMain;
	 HMENU hMenuMainCtrl;

	void InsertTimerMessage();
	void InsertNOTimerMessage();
	void InsertBCMessage();
	void MoveBCMessage(int MessageID);
	void DeleteBCMessage(int MessageID);
	CStatusBar  m_wndStatusBar;

	void Change1553();
	void ChangeMainCtrl();
	//CProject ProjectDlg;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	

	void DrawTitleBar(CDC *pDC);  // 绘制标题栏函数
	CRect m_rtButtExit;	          //关闭按钮位置
	CRect m_rtButtMax;	          //最大化按钮位置
	CRect m_rtButtMin;	          //最小化按钮位置
	CRect m_rtButtHelp;	          //帮助按钮位置
	CRect m_rtIcon;		          //标题栏程序图标位置
	
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__3B091B00_5FE4_4CA9_A7CE_242C8695C72B__INCLUDED_)
