
#ifndef LD3320_AXI_H
#define LD3320_AXI_H


/****************** Include Files ********************/
#include "xbasic_types.h"
#include "xil_types.h"
#include "xstatus.h"
#include "xil_io.h"

#define LD3320_AXI_S00_AXI_SLV_REG0_OFFSET 0
#define LD3320_AXI_S00_AXI_SLV_REG1_OFFSET 4
#define LD3320_AXI_S00_AXI_SLV_REG2_OFFSET 8
#define LD3320_AXI_S00_AXI_SLV_REG3_OFFSET 12

#define LD3320_REG_CMD LD3320_AXI_S00_AXI_SLV_REG0_OFFSET
#define LD3320_REG_RESULT LD3320_AXI_S00_AXI_SLV_REG1_OFFSET
#define LD3320_REG_RAMLIST LD3320_AXI_S00_AXI_SLV_REG2_OFFSET
#define LD3320_REG_RAMSTATE LD3320_AXI_S00_AXI_SLV_REG3_OFFSET

#define Cmd_Start 0x00000001
#define Cmd_Rqu 0x00000002
#define Re_Success 0x01
#define Re_Fail 0x02
#define Re_Wait 0x03
#define Ram_Init 0x01
#define Ram_List 0x02
#define Ram_Stop 0x03
#define Ram_Re_Yes 0x01
#define Ram_Re_No 0x02



/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a LD3320_AXI register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the LD3320_AXIdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void LD3320_AXI_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
typedef struct 
{
	u32 BaseAddress;
	u32 Cmd;
	u32 Result;
	u32 Ram;
	u32 RamState;
}LD3320;


#define LD3320_AXI_mWriteReg(Address, Data) \
  	Xil_Out32(Address, (u32)(Data))

/**
 *
 * Read a value from a LD3320_AXI register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the LD3320_AXI device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 LD3320_AXI_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define LD3320_AXI_mReadReg(Address) \
    Xil_In32(Address)

/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the LD3320_AXI instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
s32 LD3320Init(LD3320 *ld,u32 BaseAddress);


XStatus LD3320_AXI_Reg_SelfTest(void * baseaddr_p);
void LD3320RamListTrans(LD3320 *ld,u8 data[],int data_len);
void LD3320RamInitTrans(LD3320 *ld,u16 data[],int data_len);
void LD3320RamFin(LD3320 *ld);
void LD3320Start(LD3320 *ld);
u8 LD3320Work(LD3320 *ld);


#endif // LD3320_AXI_H
