// TypeDefine.cpp: implementation of the TypeDefine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ManCtrl.h"
#include "TypeDefine.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TypeDefine::TypeDefine()
{

}

TypeDefine::~TypeDefine()
{

}

//DEL API_BC_MBUF TypeDefine::bc_msg_data()
//DEL {
//DEL 
//DEL }

void TypeDefine::SetMessageTeam()//组织消息序列
{
	int i,status;

	status = BusTools_BC_MessageAlloc(NowCardNO, BC_MessageMaxCount+BC_MessageMaxCount_2);
	for(i=0;i<BC_MessageMaxCount;i++) bc_msg_data[i].messno = i;
	for(i=BC_MessageMaxCount;i<BC_MessageMaxCount+BC_MessageMaxCount_2;i++) bc_msg_data_2[i].messno = i; 
	for(i=0;i<BC_MessageMaxCount;i++)
	{
		bc_msg_data[i].messno_next=bc_msg_data[i+1].messno; 
		if(BCRetry_Flag[i]) bc_msg_data[i].control |= BC_CONTROL_RETRY;
		else bc_msg_data[i].control &= ~BC_CONTROL_RETRY;
		if(i==0)//第一个消息
		{
				// End of minor frame.
			bc_msg_data[i].control |= BC_CONTROL_INTERRUPT;   //Interrupt Set
			bc_msg_data[i].control |= BC_CONTROL_MFRAME_BEG;	// Beginning of minor frame.
		}
		if(i==BC_MessageMaxCount-1)//最后一个消息
		{
			bc_msg_data[i].control |= BC_CONTROL_INTERRUPT;
			bc_msg_data[i].control |= BC_CONTROL_MFRAME_END;
			bc_msg_data[i].messno_next=bc_msg_data[0].messno; 

		}
		
		status = BusTools_BC_MessageWrite(NowCardNO, i, &bc_msg_data[i]);
		if(BCMessageEnabel[i])	
		{
			BusTools_BC_MessageNoop(NowCardNO,i,0,0);
		}
		else
			BusTools_BC_MessageNoop(NowCardNO,i,1,0);
	}
	for(i=BC_MessageMaxCount;i<BC_MessageMaxCount+BC_MessageMaxCount_2;i++)
	{
		bc_msg_data_2[i].messno_next=bc_msg_data_2[i+1].messno; 
		if(BCRetry_Flag_2[i]) bc_msg_data_2[i].control |= BC_CONTROL_RETRY;
		else bc_msg_data_2[i].control &= ~BC_CONTROL_RETRY;
		if(i==0)//第一个消息
		{
				// End of minor frame.
			bc_msg_data_2[i].control |= BC_CONTROL_INTERRUPT;   //Interrupt Set
			bc_msg_data_2[i].control |= BC_CONTROL_MFRAME_BEG;	// Beginning of minor frame.
		}
		if(i==BC_MessageMaxCount_2+BC_MessageMaxCount-1)//最后一个消息
		{
			bc_msg_data_2[i].control |= BC_CONTROL_INTERRUPT;
			bc_msg_data_2[i].control |= BC_CONTROL_MFRAME_END;
			if(BC_MessageMaxCount>0)
				bc_msg_data_2[i].messno_next=bc_msg_data[0].messno; 
			else
				bc_msg_data_2[i].messno_next=bc_msg_data_2[0].messno;

		}
		status = BusTools_BC_MessageWrite(NowCardNO, i, &bc_msg_data_2[i-BC_MessageMaxCount]);
	}


}

void TypeDefine::InitMessageTeam()
{
	int i,j;

	
	//if(BC_stutas==0)
	
	
		ShowType = 0;

		for(i=0;i<BC_MessageMaxCount;i++)	BCRetry_Flag[i] = false;
		for(i=0;i<BC_MessageMaxCount_2;i++)	BCRetry_Flag_2[i] = false;

		BC_MessageMaxCount = 0;
		BC_MessageMaxCount_2 = 0;


		RT_SetCount =0;
		BC_stutas = 0;
		RT_stutas = 0;
		FrameTimer = 500*1000;//500MS
		GrapTimer = 100;

		wRetry= BC_RETRY_NRSP | BC_RETRY_ALTB | BC_RETRY_ME | BC_RETRY_BUSY
					   | BC_RETRY_TF | BC_RETRY_SSF | BC_RETRY_INSTR |BC_RETRY_SRQ;

		BC_RetryVal.retryFlag = true;
		for(i=0;i<32;i++)
		{
			RT_Data_Exsit[i] = false;
			RT_Data[i].VectorSetFlag = false;
			for(j=0;j<32;j++) RT_Data[i].SubSetFlag[j] = false;
		}

		BC_RetryVal.multiple_retry[0] = RETRY_ALTERNATE_BUS;
		BC_RetryVal.multiple_retry[1] = RETRY_SAME_BUS;
		BC_RetryVal.multiple_retry[2] = RETRY_SAME_BUS;//RETRY_ALTERNATE_BUS;
		BC_RetryVal.multiple_retry[3] = RETRY_SAME_BUS;
		BC_RetryVal.multiple_retry[4] = RETRY_SAME_BUS;
		BC_RetryVal.multiple_retry[5] = RETRY_SAME_BUS;
		BC_RetryVal.multiple_retry[6] = RETRY_SAME_BUS;
		BC_RetryVal.multiple_retry[7] = RETRY_END;

		MessageSaveCondtion.NowConditcount = 0;
		firstTimeflag = true;
		NowGetMessgeCount = 1;
		for(i=0;i<32;i++) 
		{
			VectorArra[i].NowCount = 0;
			RT_Enable[i] = false;
		}
		FileNameTempSave = "C:\\MessageTemp.dat";
		FileNameNowWorkSave = FileNameTempSave;

		ShowModedata.DataCountAll = 0;
			
	
		CFileFind FF;
		CFileException e;
		int find ;
		
		//int find = FF.FindFile(m_pMainWnd->MessageData1553.FileNameTempSave,0);
		//if(find!=0)	//找到文件 
		{
			find = FileWrite.Open(FileNameTempSave,CFile::modeCreate |CFile::modeWrite|CFile::shareDenyNone  , &e);
			find = FileRead.Open(FileNameTempSave,CFile::modeRead|CFile::shareDenyNone  , &e);
   
		}
		NoShow_Stutas[256] = 0;
		NoShow_Vector[256] = 0;

		ShowLostCount = 0;
		DeleteFile(FileNameTempSave);
	
}

int TypeDefine::RunBC()
{
	int status;
	if (BC_MessageMaxCount!=0)
	{
		SetMessageTeam();
		status = BusTools_BC_StartStop(NowCardNO,1); 
		BC_stutas = 1;
		return 1;
	}
	else 
	{
		MessageBox(NULL ,"未定义周期消息",  NULL,MB_OK );
		return 0;
	}
} 

int TypeDefine::StopBC()
{
	int status;
	status = BusTools_BC_StartStop(NowCardNO,0); 
	BC_stutas = 0;
	return status;
}
BT_INT TypeDefine::OpenHardware()
{
	BT_INT status;
	unsigned int	flag = 1;  
  int peroid;
  short gaptime=10;
  status = BusTools_API_Init(NowCardNO, MY_BASE_ADDR, MY_IO_ADDR, &flag);
  

  //BusTools_BM_Init(NowCardNO,1,1);
	
 return status;
}

int TypeDefine::InitBC()
{
	int status,i;
	

	status = BusTools_BC_Init(NowCardNO, 0, 0, wRetry, 14, 12,FrameTimer, 2); 
	
	
	return status;
}
int TypeDefine::RunRT()
{
	int status;

	status = BusTools_RT_StartStop(NowCardNO,1);
	RT_stutas = 1;
	return status;

}
int TypeDefine::StopRT()
{
	int status;

	status = BusTools_RT_StartStop(NowCardNO,0);
	RT_stutas = 0;
	return status;
}
int TypeDefine::WriteRTData(int RTAdress,int SubAdress,int ID)
{
	int status;
	status = BusTools_RT_MessageWrite(NowCardNO, RTAdress, SubAdress, 1, 0, &RT_Data[RTAdress].msg_buffer_write[SubAdress]);
	return status;
}

int TypeDefine::EnableRT(int RTAdress)
{
	API_RT_ABUF			Abuf_RT1; 
	int status;

	Abuf_RT1.enable_a = 1;			// Respond on bus A
	Abuf_RT1.enable_b = 1;			// Respond on bus B
	Abuf_RT1.inhibit_term_flag = 1;	// Inhibit terminal flag in status word
	Abuf_RT1.status = 0x0800;		// Set status word
	Abuf_RT1.bit_word = 0x1000;		// Set BIT word (for mode code 19)
	status = BusTools_RT_AbufWrite(NowCardNO, RTAdress, &Abuf_RT1);

	return status;
}
int TypeDefine::Write_SelfTest(int RTAdress,int SelfTest,bool flag)
{
	API_RT_ABUF			Abuf_RT1; 
	int status;

	if(flag)
	{
		Abuf_RT1.enable_a = 1;			// Respond on bus A
		Abuf_RT1.enable_b = 1;			// Respond on bus B
	}
	else
	{
		Abuf_RT1.enable_a = 0;			// Respond on bus A
		Abuf_RT1.enable_b = 0;			// Respond on bus B
	}
	Abuf_RT1.inhibit_term_flag = 1;	// Inhibit terminal flag in status word
	Abuf_RT1.status = 0x0800;		// Set status word
	Abuf_RT1.bit_word = SelfTest;		// Set BIT word (for mode code 19)
	status = BusTools_RT_AbufWrite(NowCardNO, RTAdress, &Abuf_RT1);

	return status;
}

int TypeDefine::DisableRT(int RTAdress)
{
	API_RT_ABUF			Abuf_RT1; 
	int status;
	
	Abuf_RT1.enable_a = 0;			// Respond on bus A
	Abuf_RT1.enable_b = 0;			// Respond on bus B
	Abuf_RT1.inhibit_term_flag = 1;	// Inhibit terminal flag in status word
	Abuf_RT1.status = 0x0800;		// Set status word
	Abuf_RT1.bit_word = 0x0000;		// Set BIT word (for mode code 19)
	status = BusTools_RT_AbufWrite(NowCardNO, RTAdress, &Abuf_RT1);
	return status;
}
CString TypeDefine::InttoTimerStr(unsigned int val)
{
   CString retrundata;
   int i;
   
   int hour,minu,second,msecond,usecond,usecondvl;
	

   usecondvl =  val %10;
   usecond =  (val /1) % 1000;
   
   
   msecond =  (val /1000) %1000;
   second =  (val /1000000)%60 ;
	minu  = (val /60000000)%60;
	hour =  (val /(60000000*60))%60; 
	retrundata.Format("%2d:%2d:%2d:-%3d:%3d",	hour,minu,second,msecond,usecond);
	for(i=0;i<retrundata.GetLength();i++)
	{
		if(retrundata.GetAt(i)==' ') retrundata.SetAt(i,'0');
	}
	return retrundata;
	
}
WORD TypeDefine::Stutas1553ToInt(BT1553_STATUS stutas)
{
	WORD val;

	val = 0;

	if(stutas.me==1)  val |=(1<<10);
	else val &=~(1<<10);
	
	if(stutas.inst==1)  val |=(1<<9);
	else val &=~(1<<9);

	if(stutas.sr==1)  val |=(1<<8);
	else val &=~(1<<8);	

	if(stutas.bcr==1)  val |=(1<<4);
	else val &=~(1<<4);

	if(stutas.busy==1)  val |=(1<<3);
	else val &=~(1<<3);	

	if(stutas.sf==1)  val |=(1<<2);
	else val &=~(1<<2);

	if(stutas.dba==1)  val |=(1<<1);
	else val &=~(1<<1);

	if(stutas.tf==1)  val |=(1<<0);
	else val &=~(1<<0);

	return val;
}
BT1553_STATUS TypeDefine::IntToStutas1553(WORD val)
{
	BT1553_STATUS stutas;
	WORD val0;
	val0 = 0x0000;

	//memcpy(&stutas, &val0,sizeof(WORD));

	

	if((val & (1024))==1024)
		stutas.me=1 ;
	else stutas.me=0;

	if((val & (512))==512)
		stutas.inst=1;
	else stutas.inst=0;

	if((val & (256))==256)
		stutas.sr=1 ;
	else stutas.sr=0;	

	if((val & (16))==16)
		stutas.bcr=1;
	else stutas.bcr=0;

	if((val & (8))==8)
		stutas.busy=1;
	else stutas.busy=0;	

	if((val & (4))==4)
		stutas.sf=1;
	else stutas.sf=0;

	if((val & (2))==2)
		stutas.dba=1;
	else stutas.dba=0;

	if((val & (0X01))==1)
		stutas.tf=1;
	else stutas.tf=0;

	return stutas;
}
Message_DataType TypeDefine::GetMessageData(int type)
{
	BT_INT status;
	API_BM_MBUF     messages[512]; 
	BT_UINT num_buffers_read;
	int i,j,k,NowSaveConID;
	Message_DataType returndata;
	bool saveflag;
	char WriteBuffer[5000];
	CString timerstr;

	CMainFrame *m_pMainWnd;
	m_pMainWnd = (CMainFrame *) AfxGetMainWnd ();

	num_buffers_read = 0;
	returndata.MessageUnmber = 0;
 	status = BusTools_BM_MessageReadBlock(NowCardNO, messages,512,0,&num_buffers_read);
/*	if(NowGetMessgeCount+num_buffers_read<50000)
	{
		memcpy(&GetMessageSave[NowGetMessgeCount],&messages[0],sizeof(API_BM_MBUF)*num_buffers_read);
		NowGetMessgeCount+=num_buffers_read;
	}
	else//超出保存树组处理
	{

	}
*/	m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].messCount += num_buffers_read;
	CString strwrite;
	for(i=0;i<num_buffers_read;i++)  
	{
		////数据存储到临时文件中。

		if(firstTimeflag==TRUE)
		{
				firstTime =  messages[i].time.microseconds;
				strwrite.Format("%d",firstTime);
				//WritePrivateProfileString("BM_GetMessage","firstTime",strwrite,FileNameTempSave);
				m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileWrite.Write(&firstTime,sizeof(int));
				firstTimeflag = FALSE;
		}

		strwrite.Format("%d",m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].messCount);
		m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].SetDlgItemText(IDC_GETCOUNT,"数据总数:"+strwrite);
		////如果该数据被过滤，将不被写到文件中
		if((m_pMainWnd->CheckFiltration(messages[i]))&&(m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag[messages[i].command1.rtaddr][messages[i].command1.subaddr]))
		{
			m_pMainWnd->MessageData1553[m_pMainWnd->m_now_SelectChannel].FileWrite.Write(&messages[i],sizeof(API_BM_MBUF));
			NowGetMessgeCount++;
			/////////
			saveflag = FALSE;
			for(j=0;j<MessageSaveCondtion.NowConditcount;j++)
			{
				if((messages[i].command1.rtaddr==MessageSaveCondtion.Conditonval[j].Adress)&&(messages[i].command1.subaddr==MessageSaveCondtion.Conditonval[j].SubAdress)
					&&(MessageSaveCondtion.Conditonval[j].SaveFlag==true))//该消息需要保存
				{
					saveflag = TRUE;
					NowSaveConID = j;
					break;
				}
			}
			if(saveflag==TRUE)
			{
				sprintf(WriteBuffer,"%s","");
				for(k=0;k<32;k++)
					sprintf(WriteBuffer,"%s  %s%2d=%4X; ",WriteBuffer,"数据",k,returndata.Messagedata[i].value[k]);
				
				
				timerstr =   InttoTimerStr(messages[i].time.microseconds-firstTime);
				sprintf(WriteBuffer,"%s  %s=%s; ",WriteBuffer,"时标",timerstr); 
				
				sprintf(WriteBuffer,"%s  %s=%2d",WriteBuffer,"地址",messages[i].command1.rtaddr);
				sprintf(WriteBuffer,"%s  %s=%2d",WriteBuffer,"子地址",messages[i].command1.subaddr);
				sprintf(WriteBuffer,"%s  %s=%2d",WriteBuffer,"数据计数",messages[i].command1.wcount);
							
				sprintf(WriteBuffer,"%s  %s=%d",WriteBuffer,"消息差错",messages[i].status1.me);//消息差错
				sprintf(WriteBuffer,"%s  %s=%d",WriteBuffer,"服务请求",messages[i].status1.sr);//服务请求
				sprintf(WriteBuffer,"%s  %s=%d",WriteBuffer,"子系统标志",messages[i].status1.sf);//子系统标志
				sprintf(WriteBuffer,"%s  %s=%d",WriteBuffer,"终端标志",messages[i].status1.tf);//终端标志:
				sprintf(WriteBuffer,"%s  %s=%d",WriteBuffer,"忙",messages[i].status1.busy);//忙:
				sprintf(WriteBuffer,"%s  %s=%d",WriteBuffer,"动态总线控制接收",messages[i].status1.dba);//动态总线控制接收
				sprintf(WriteBuffer,"%s  %s=%d",WriteBuffer,"广播指令接收 ",messages[i].status1.bcr);//广播指令接收
				sprintf(WriteBuffer,"%s  %s=%d",WriteBuffer,"测试手段",messages[i].status1.inst);//测试手段
				
				MessageSaveCondtion.Conditonval[NowSaveConID].FileID.Write(WriteBuffer,650);  
				MessageSaveCondtion.Conditonval[NowSaveConID].FileID.Write("\n",2);  
				//WriteFile(SaveFileData.FileID[j],
				//WriteFile(SaveFileData.FileID[j],"\n",2);
			}
		}
	}
	
	if(m_pMainWnd->TimeShowFlag)
	{
		if(type==0)
		{
			if((status==0)&&(num_buffers_read>0))
			{
				for(i=0;i<num_buffers_read;i++)  
				{
					if(messages[i].status_c1==1)   //msgtype
					{
					}
				}
				
			}
			for(i=0;i<num_buffers_read;i++)  
				returndata.Messagedata[i] = messages[i];

			returndata.MessageUnmber = num_buffers_read;
			
			return returndata;
		}
		else
		{//非滚动方式
			
			if((status==0)&&(num_buffers_read>0))
			{
				for(j=0;j<ShowModedata.DataCountAll;j++) returndata.flag[j] = false;
				returndata.MessageUnmber = 0;
				
				for(i=0;i<num_buffers_read;i++)
				{
					if((m_pMainWnd->CheckFiltration(messages[i]))&&(m_pMainWnd->BMView[m_pMainWnd->m_now_SelectChannel].Exce_Flag[messages[i].command1.rtaddr][messages[i].command1.subaddr]))
					{
						for(j=0;j<ShowModedata.DataCountAll;j++)
						{
							if((ShowModedata.Dataval[j].subaddr == messages[i].command1.subaddr)
								&&(ShowModedata.Dataval[j].tran_rec == messages[i].command1.tran_rec)
								&&(ShowModedata.Dataval[j].wcount == messages[i].command1.wcount)
								&&(ShowModedata.Dataval[j].rtaddr == messages[i].command1.rtaddr )
								&&(ShowModedata.status_c1[j]==messages[i].status_c1))
							{
								returndata.Messagedata[j] = messages[i];
								returndata.flag[j] = true;
								returndata.ShowItem[j] = j;

								if(returndata.MessageUnmber<j)
									returndata.MessageUnmber=j;
								break;
							}

						}

						if(j==ShowModedata.DataCountAll)
						{
							ShowModedata.Dataval[j].subaddr = messages[i].command1.subaddr;
							ShowModedata.Dataval[j].tran_rec = messages[i].command1.tran_rec;
							ShowModedata.Dataval[j].wcount = messages[i].command1.wcount;
							ShowModedata.Dataval[j].rtaddr = messages[i].command1.rtaddr;
							ShowModedata.status_c1[j]=messages[i].status_c1;

							returndata.Messagedata[j] = messages[i];
							returndata.flag[j] = true;
							returndata.ShowItem[j] = j;

							if(returndata.MessageUnmber<j)
								returndata.MessageUnmber=j;

							ShowModedata.DataCountAll++;

						}
					}///end if(m_pMainWnd->CheckFiltration(messages[i]))
				}

			}
			returndata.MessageUnmber=returndata.MessageUnmber+1;
			return returndata;
		}
	}
	else
	{
		returndata.MessageUnmber = 0;
		return returndata;

	}

}

void TypeDefine::Out1553()
{
	BT_INT status;
   	status = BusTools_RT_StartStop(NowCardNO,0);
	status = BusTools_BC_StartStop(NowCardNO, 0);
    status = BusTools_API_Close(NowCardNO);
}
int TypeDefine::StepRun()
{
	int messageid,status; 
	if(BC_MessageMaxCount>0)
	{
		SetMessageTeam();
		for(messageid=0; messageid<BC_MessageMaxCount;messageid++)
		{
			if(BCMessageEnabel[messageid])
			{
   				while (BusTools_BC_AperiodicTest(NowCardNO, 0) == API_BC_APERIODIC_RUNNING);
					BusTools_BC_AperiodicRun(NowCardNO, messageid, 0, 1, 20);
			}
			BusTools_BC_MessageNoop(NowCardNO,messageid,1,0);
		}
	}
 	status = BusTools_BC_StartStop(NowCardNO,1);
	return status;
}

int TypeDefine::RT_WriteStatusWord(BT_UINT cardnum,         // (i) card number (0 - based)
   BT_UINT rtaddr,          // (i) RT address (0 - based)
   BT_UINT subaddr,         // (i) RT subaddress (0 - based)
   BT_UINT tr,              // (i) Transmit/Receive flag (1->rt transmit)
   BT_UINT mbuf_id,         // (i) RT MBUF number
   BT_U16BIT wStatusWord,   // (i) 1553 status word to be used by buffer
   BT_UINT wFlag)
{
	int status;
	RT_Data[rtaddr].StatusWord = wStatusWord;
	RT_Data[rtaddr].StatusSetFlag=true;
	status = BusTools_RT_MessageWriteStatusWord(NowCardNO, rtaddr, subaddr, tr, mbuf_id, wStatusWord, wFlag);
	return status;

}

int TypeDefine::RT_WriteVectorWord(BT_UINT cardnum, BT_UINT rtaddr, BT_UINT subaddr, BT_UINT tr, BT_UINT mbuf_id, BT_U16BIT vectorword)
{
	int status;
	API_RT_MBUF_WRITE	msg_buffer_write;
	
	msg_buffer_write.enable = 0;		// No interrupts enabled
	msg_buffer_write.error_inj_id = 0;	// No error injection
	msg_buffer_write.mess_data[0] = vectorword;//0xC0DE;

	RT_Data[rtaddr].VectorWord = vectorword;
	RT_Data[rtaddr].VectorSetFlag=true;
	status = BusTools_RT_MessageWrite(NowCardNO, rtaddr, 0, 1, mbuf_id, &msg_buffer_write);
	RT_WriteVectorWordCount(rtaddr,subaddr,1 ); 
	return status;
}
int TypeDefine::RT_WriteVectorWordCount(int rtaddr,int sub_addr,int ID_max_number )
{
	int status;
	API_RT_CBUF			Cbuf_RT1SA1R;
	API_RT_CBUF			Cbuf_RT1SA2T;

	Cbuf_RT1SA1R.legal_wordcount = 0xFFFFFFFF;  // any word count is legal.
	status = BusTools_RT_CbufWrite(NowCardNO, rtaddr,0, 1, ID_max_number, &Cbuf_RT1SA1R);
	return status;
//			
}
void TypeDefine::DeleteRT(int RT_ID)
{
	int i;
	DisableRT(RT_ID);
	RT_Data_Exsit[RT_ID] = false;
	for(i=0;i<32;i++)
	RT_Data[RT_ID].SubSetFlag[i] = false;;
	RT_Data[RT_ID].VectorWord = 0;
	RT_Data[RT_ID].VectorSetFlag = false;;
}

void TypeDefine::SetRespTime(int resptime)
{
	BusTools_SetOptions(NowCardNO, 0, resptime,0,0);
}

unsigned long TypeDefine::DiscreteRead(int Flag)
{	
	unsigned long io_status;
	short status;

	BusTools_DiscreteRead(NowCardNO,Flag,&io_status);

	return io_status;
}

void TypeDefine::DiscreteSetIO(int flag, unsigned long stutasIO)
{
	BusTools_DiscreteSetIO(NowCardNO,flag,stutasIO);
}
void TypeDefine::EnableMessge(int type,int ID)
{
	if(type==1)
	{
		BCMessageEnabel[ID] = true;
		if(BC_stutas == 1)//BC运行状态
			BusTools_BC_MessageNoop(NowCardNO,ID,0,0);
	}
	else
	{
		BCNoTiemMessageEnabel[ID] = true;
	}
	
	
}
void TypeDefine::DisableMessge(int type,int ID)
{
	if(type==1)
	{
		BCMessageEnabel[ID] = false;
		BusTools_BC_MessageNoop(NowCardNO,ID,1,0);
	}
	else
	{
		BCNoTiemMessageEnabel[ID] = false;
	}
	
}
void TypeDefine::SendNotimeMessage()
{
	int messageid,status; 
	if(BC_MessageMaxCount_2>0)
	{
		SetMessageTeam();
		if(BC_stutas==0)
		{
			for(messageid=0; messageid<BC_MessageMaxCount;messageid++)
			{
   				//while (BusTools_BC_AperiodicTest(NowCardNO, 0) == API_BC_APERIODIC_RUNNING);
				//BusTools_BC_AperiodicRun(NowCardNO, messageid, 0, 1, 20);
				BusTools_BC_MessageNoop(NowCardNO,messageid,1,0);
			}
		}
		for(messageid=BC_MessageMaxCount; messageid<BC_MessageMaxCount+BC_MessageMaxCount_2;messageid++)
		{
			if(BCNoTiemMessageEnabel[messageid-BC_MessageMaxCount])
			{
   				while (BusTools_BC_AperiodicTest(NowCardNO, 0) == API_BC_APERIODIC_RUNNING);
					BusTools_BC_AperiodicRun(NowCardNO, messageid, 0, 1, 20);
				
			}
			BusTools_BC_MessageNoop(NowCardNO,messageid,1,0);
		}
		status = BusTools_BC_StartStop(NowCardNO,1);
	}
                    
	else
	{
		MessageBox(NULL ,"未定义非周期消息",  NULL,MB_OK );
	}
}

void TypeDefine::SetNoTimeMessageTeam()
{
	int i,status;
	for(i=0;i<BC_MessageMaxCount_2;i++)
	{
		bc_msg_data_2[i].messno_next=bc_msg_data_2[i+1].messno; 
		if(BC_RetryVal.retryFlag) bc_msg_data_2[i].control |= BC_CONTROL_RETRY;
		else bc_msg_data_2[i].control &= ~BC_CONTROL_RETRY;
		if(i==0)//第一个消息
		{
				// End of minor frame.
			bc_msg_data_2[i].control |= BC_CONTROL_INTERRUPT;   //Interrupt Set
			bc_msg_data_2[i].control |= BC_CONTROL_MFRAME_BEG;	// Beginning of minor frame.
		}
		if(i==BC_MessageMaxCount_2-1)//最后一个消息
		{
			bc_msg_data_2[i].control |= BC_CONTROL_INTERRUPT;
			bc_msg_data_2[i].control |= BC_CONTROL_MFRAME_END;
			if(BC_MessageMaxCount>0)
				bc_msg_data_2[i].messno_next=bc_msg_data[0].messno; 
			else bc_msg_data_2[i].messno_next=bc_msg_data_2[0].messno; 

		}
		status = BusTools_BC_MessageWrite(NowCardNO, i+BC_MessageMaxCount, &bc_msg_data_2[i]);
	}
}
void TypeDefine::SendNowSelecteMessage(int TypeMessage,int MessageID)//单次发送选择消息
{
	int messageid,status,i; 
 
	SetMessageTeam();

	if(TypeMessage==1)
	{
		if(BC_stutas==0)
		{
			for(i=0;i<BC_MessageMaxCount;i++)
			{
				if(i == MessageID)
				{
					while (BusTools_BC_AperiodicTest(NowCardNO, 0) == API_BC_APERIODIC_RUNNING);
						BusTools_BC_AperiodicRun(NowCardNO, MessageID, 0, 1, 20);
				}
				BusTools_BC_MessageNoop(NowCardNO,i,1,0);
			}

			status = BusTools_BC_StartStop(NowCardNO,1);
		}
		else
		{
			MessageBox(NULL ,"周期消息运行中，不能单次发送选择消息",  "注意",MB_OK );
		}
	}
	else if(TypeMessage==2)
	{
		if(BC_stutas==0)//BC没有运行
		{
			for(i=0;i<BC_MessageMaxCount+BC_MessageMaxCount_2;i++)
			{	
				if(i == MessageID+BC_MessageMaxCount)
				{
					while (BusTools_BC_AperiodicTest(NowCardNO, 0) == API_BC_APERIODIC_RUNNING);
					BusTools_BC_AperiodicRun(NowCardNO, i, 0, 1, 20);
				}

				BusTools_BC_MessageNoop(NowCardNO,i,1,0);
			}
		}
		else//BC运行中
		{
			for(i=BC_MessageMaxCount;i<BC_MessageMaxCount+BC_MessageMaxCount_2;i++)
			{	
				if(i == MessageID+BC_MessageMaxCount)
				{
					while (BusTools_BC_AperiodicTest(NowCardNO, 0) == API_BC_APERIODIC_RUNNING);
					BusTools_BC_AperiodicRun(NowCardNO, i, 0, 1, 20);
				}

				BusTools_BC_MessageNoop(NowCardNO,i,1,0);
			}
		}

		status = BusTools_BC_StartStop(NowCardNO,1);
	}
	
	
}

void TypeDefine::MoveUpBCMessage(int type, int NowdeletID)
{
	API_BC_MBUF TempBCMessage;

	if(type==1)//周期消息
	{
		TempBCMessage = bc_msg_data[NowdeletID-1];
		bc_msg_data[NowdeletID-1] = bc_msg_data[NowdeletID] ;
		bc_msg_data[NowdeletID] = TempBCMessage;
	}
	else
	{
		TempBCMessage = bc_msg_data_2[NowdeletID-1];
		bc_msg_data_2[NowdeletID-1] = bc_msg_data_2[NowdeletID] ;
		bc_msg_data_2[NowdeletID] = TempBCMessage;
	}
}
void TypeDefine::MoveDownBCMessage(int type, int NowdeletID)
{
	API_BC_MBUF TempBCMessage;

	if(type==1)//周期消息
	{
		TempBCMessage = bc_msg_data[NowdeletID+1];
		bc_msg_data[NowdeletID+1] = bc_msg_data[NowdeletID] ;
		bc_msg_data[NowdeletID] = TempBCMessage;
	}
	else
	{
		TempBCMessage = bc_msg_data_2[NowdeletID+1];
		bc_msg_data_2[NowdeletID+1] = bc_msg_data_2[NowdeletID] ;
		bc_msg_data_2[NowdeletID] = TempBCMessage;
	}
}
