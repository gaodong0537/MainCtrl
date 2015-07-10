// TypeDefine.h: interface for the TypeDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TYPEDEFINE_H__3B510A19_D34C_469D_82D0_BFC9032BD787__INCLUDED_)
#define AFX_TYPEDEFINE_H__3B510A19_D34C_469D_82D0_BFC9032BD787__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "busapi.h"

#define MY_CARD_NUM		0
#define MY_BASE_ADDR	0
#define MY_IO_ADDR		0


typedef struct {
    API_BM_MBUF	Messagedata[1000];
	BT_UINT	MessageUnmber;
	bool flag[1000];
	int ShowItem[2560];
	
	//LPCTSTR  Name;
	}Message_DataType;

typedef struct {
    BT1553_COMMAND Dataval[MAXMESSAGECOUNT];
	int DataCountAll;
	int ShowItem[MAXMESSAGECOUNT];
	int status_c1[2560];
	}ShowModetype;

typedef struct {
	int Adress;
	int SubAdress;
    CFile	FileID;
	CString FileName;
	bool SaveFlag;
	//LPCTSTR  Name;
	}SaveMessageFileType1;
typedef struct {
	BT_U16BIT VectorWord[60];
	int NowCount;
	//LPCTSTR  Name;
	}Vector_ArrayType;

typedef struct {
	SaveMessageFileType1 Conditonval[200];
	int NowConditcount;
	}SaveMessageFileType;

typedef struct {
    API_RT_MBUF_WRITE	msg_buffer_write[32];
	bool SubSetFlag[32];
	BT_U16BIT	RtAdress;
	BT_U16BIT	VectorWord;
	BT_U16BIT	SelfTestWord;
	BT_U16BIT   StatusWord;
	bool StatusSetFlag;
	bool VectorSetFlag;
	//LPCTSTR  Name;
	}RT_DataType;
typedef struct {
	BT_U16BIT	multiple_retry[8];
	bool retryFlag;
	}BC_RetryType;
class TypeDefine  
{

public:
	void MoveUpBCMessage(int type,int NowdeletID);
	void MoveDownBCMessage(int type,int NowdeletID);
	BT1553_STATUS IntToStutas1553(WORD val);
	WORD Stutas1553ToInt(BT1553_STATUS stutas);
	void SendNowSelecteMessage(int TypeMessage,int MessageID);//单次发送选择消息
	void SetNoTimeMessageTeam();
	void SendNotimeMessage();
	BC_RetryType BC_RetryVal;
	void EnableMessge(int type,int ID);
	void DisableMessge(int type,int ID);
	
	void DiscreteSetIO(int flag,unsigned long stutasIO);
	unsigned long DiscreteRead(int Flag);
	void SetRespTime(int resptime);
	int NowCardNO;
	void DeleteRT(int RT_ID);
	int RT_WriteVectorWord(BT_UINT cardnum, BT_UINT rtaddr,BT_UINT subaddr,BT_UINT tr, BT_UINT mbuf_id,  BT_U16BIT vectorword);
	
	int RT_WriteVectorWordCount(int rtaddr,int sub_addr,int ID_max_number );

	int RT_WriteStatusWord(BT_UINT cardnum,         // (i) card number (0 - based)
						   BT_UINT rtaddr,          // (i) RT address (0 - based)
						   BT_UINT subaddr,         // (i) RT subaddress (0 - based)
						   BT_UINT tr,              // (i) Transmit/Receive flag (1->rt transmit)
						   BT_UINT mbuf_id,         // (i) RT MBUF number
						   BT_U16BIT wStatusWord,   // (i) 1553 status word to be used by buffer
						   BT_UINT wFlag);

	int ShowLostCount;

	ShowModetype ShowModedata;

	int RT_stutas;
	int BC_stutas;
	int ShowType;
	WORD  rtstatus[32],vectorword[32],Stestword[32]; 
	int StopRT();
	int GrapTimer;
	int FrameTimer;
	int StepRun();
	void Out1553();
	Message_DataType GetMessageData(int type);
	int DisableRT(int RTAdress);
	int EnableRT(int RTAdress);
	int RunRT();
	int Write_SelfTest(int RTAdress,int SelfTest,bool flag);
	int WriteRTData(int RTAdress,int SubAdress,int ID);
	int InitBC();
	int StopBC();
	int RunBC();
	BT_INT OpenHardware();//初始化硬件
	void InitMessageTeam();
	void SetMessageTeam();
	CString InttoTimerStr(unsigned int val); 

	SaveMessageFileType MessageSaveCondtion;//消息保存设置
	API_BM_MBUF GetMessageSave[50000];//保存收到的消息
	int NowGetMessgeCount;//当前保存的消息数
	CString FileNameTempSave;
	CString FileNameNowWorkSave;

	bool firstTimeflag;
	int firstTime;
	Vector_ArrayType VectorArra[32];
	BT_U16BIT wRetry;

	int chanA_B[MAXMESSAGECOUNT],chanA_B_2[MAXMESSAGECOUNT];//1 A 0 B
	int BC_MessageMaxCount,RT_SetCount,BC_MessageMaxCount_2;
	int MessageTyep[MAXMESSAGECOUNT],MessageTyep_2[MAXMESSAGECOUNT];//0 bc->rt 1 rt->bc 2rt->rt 3 mode
	CString MessageName[MAXMESSAGECOUNT],MessageName_2[MAXMESSAGECOUNT];
	API_BC_MBUF bc_msg_data[MAXMESSAGECOUNT],bc_msg_data_2[MAXMESSAGECOUNT];
	bool BCRetry_Flag[MAXMESSAGECOUNT],BCRetry_Flag_2[MAXMESSAGECOUNT];
	short NowAddMessageType;

	RT_DataType RT_Data[32];
	bool RT_Data_Exsit[32];
	bool RT_Enable[32];
	bool RT_VectoStutaSetflag[32];
	bool BCMessageEnabel[MAXMESSAGECOUNT];
	bool BCNoTiemMessageEnabel[MAXMESSAGECOUNT];
	//int m_gapTime_Timer[MAXMESSAGECOUNT];//周期消息的消息间隔
	//int m_gapTime_NoTimer[MAXMESSAGECOUNT];//周期消息的消息间隔

	CFile FileWrite;//高速模式下的数据存储句柄
	CFile FileRead;//高速模式下的数据存储句柄

	int NoShow_Vector[257];//过滤矢量字
	int NoShow_Stutas[257];//过滤状态字 51位为该过滤设置个数

	TypeDefine();
	virtual ~TypeDefine();

};

#endif // !defined(AFX_TYPEDEFINE_H__3B510A19_D34C_469D_82D0_BFC9032BD787__INCLUDED_)
