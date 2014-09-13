

/***************************** Include Files *******************************/
#include "LD3320_AXI.h"

/************************** Function Definitions ***************************/
s32 LD3320Init(LD3320 *ld,u32 BaseAddress)
{
	ld->BaseAddress=BaseAddress;
	ld->Cmd=BaseAddress+LD3320_REG_CMD;
	ld->Result=BaseAddress+LD3320_REG_RESULT;
	ld->Ram=BaseAddress+LD3320_REG_RAMLIST;
	ld->RamState=BaseAddress+LD3320_REG_RAMSTATE;
	return (XST_SUCCESS);
}

void LD3320RamListTrans(LD3320 *ld,u8 data[],int data_len)
{
	u32 trans=(Ram_List<<24);
	u32 State;
	u8 State_c[4];
	u8 i=0;
	LD3320_AXI_mWriteReg(ld->Ram,0x00000000);
	for (i=0;i<data_len;i++)
	{
		trans=(Ram_List<<24);
		trans+=(i<<16);
		trans+=data[i];
		LD3320_AXI_mWriteReg(ld->Ram,trans);
		while(1)
		{
			State=LD3320_AXI_mReadReg(ld->RamState);
			memcpy(&State_c,&State, 4);
			if (State_c[3]==Ram_Re_Yes)
			{
				if((State&0x00ffffff)==(trans&0x00ffffff))
					break;
				else
				{
					i--;
					break;
				}
			}
		}
	}
	return;
}

void LD3320RamInitTrans(LD3320 *ld,u16 data[],int data_len)
{
	u32 trans=(Ram_Init<<24);
	u32 State;
	u8 State_c[4];
	u8 i=0;
	LD3320_AXI_mWriteReg(ld->Ram,0x00000000);
	for (i=0;i<data_len;i++)
	{
		trans=(Ram_Init<<24);
		trans+=(i<<16);
		trans+=data[i];
		LD3320_AXI_mWriteReg(ld->Ram,trans);
		while(1)
		{
			State=LD3320_AXI_mReadReg(ld->RamState);
			memcpy(&State_c,&State, 4);
			if (State_c[3]==Ram_Re_Yes)
			{	
				if((State&0x00ffffff)==(trans&0x00ffffff))
					break;
				else
				{
					i--;
					break;
				}
			}
		}
	}
	return;
}


void LD3320RamFin(LD3320 *ld)
{
	LD3320_AXI_mWriteReg(ld->Ram,Ram_Stop<<24);
	return;
}


void LD3320Start(LD3320 *ld)
{
	LD3320_AXI_mWriteReg(ld->Cmd,Cmd_Start);
	usleep(1000000);
	return;
}

u8 LD3320Work(LD3320 *ld)
{
	LD3320_AXI_mWriteReg(ld->Cmd,Cmd_Rqu);
	u32 res;
	u8 result[4];
	while(1)
	{
		res=LD3320_AXI_mReadReg(ld->RamState);
		memcpy(&result,&res,4);
		if ((result[1])==Re_Wait)
			usleep(1);
		else if((result[1])==Re_Fail)
			return Re_Fail;
		else if((result[1])==Re_Success)
			return result[0];
	}
}
