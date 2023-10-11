#include "common.h"

#define CASE1
void test_cmpss_reg_w_r(u8 ch)
{
	volatile struct CMPSS_REGS *cmpss = (volatile struct CMPSS_REGS *)(CMPSS_BASE+ch*0x100);
	EALLOW;
	cmpss-> COMPCTL.all=0x11111111;          // CMPSS Comparator Control Register
	vu32 compctl_reg=cmpss-> COMPCTL.all;      // CMPSS Comparator Control Register read
	printf("comphysctl_reg= 0x%x \n",compctl_reg);

	vu32 compsts_reg=cmpss-> COMPSTS.all;      // CMPSS Comparator Status Register
	printf("compst= 0x%x \n",compsts_reg);

	cmpss-> COMPSTSCLR.all=0x22222222;       // CMPSS Comparator Status Clear Register
	vu32 compstsclr_reg=cmpss-> COMPSTSCLR.all;      // CMPSS Comparator Status Clear Register read
	printf("compstsclr_reg= 0x%x \n",compstsclr_reg);

	cmpss-> COMPDACCTL.all=0x33333333;       // CMPSS DAC Control Regist
	vu32 compdacctl_reg=cmpss-> COMPDACCTL.all;      // CMPSS DAC Control Register read
	printf("compdacctl_reg= 0x%x \n",compdacctl_reg);

	cmpss-> DACHVALS.all=0x44444444;         // CMPSS High DAC Value Shadow Register
	vu32 dachvals_reg=cmpss-> DACHVALS.all;      // CMPSS High DAC Value Shadow Register read
	printf("dachvals_reg= 0x%x \n",dachvals_reg);

	vu32 dachvala_reg=cmpss->DACHVALA.all;     // CMPSS High DAC Value Active Register
	printf("dachvala= 0x%x \n",dachvala_reg);

	vu32 rampmaxrefa_reg=cmpss->RAMPMAXREFA;   // CMPSS Ramp Max Reference Active Register
	printf("rampmaxrefa= 0x%x \n",rampmaxrefa_reg);

	cmpss-> RAMPMAXREFS=0x55555555;          // CMPSS Ramp Decrement Value Active Register
	vu32 rampmaxrefs_reg=cmpss->RAMPMAXREFS;    // CMPSS Ramp Decrement Value Active Register read
	printf("rampmaxrefs= 0x%x \n",rampmaxrefs_reg);

	cmpss-> RAMPDECVALS=0x66666666;
	vu32 rampdecvals_reg=cmpss->RAMPDECVALS;           // CMPSS Ramp Status Register
	printf("rampdecvals= 0x%x \n",rampdecvals_reg);

	cmpss-> DACLVALS.all=0x77777777;         // CMPSS Low DAC Value Shadow Register
	vu32 daclvals_reg=cmpss->DACLVALS.all;     // CMPSS Low DAC Value Active Register read
	printf("daclvals= 0x%x \n",daclvals_reg);

	vu32 rampdlya_reg=cmpss->RAMPDLYA.all;     //  CMPSS Ramp Delay Active Register
	printf("rampdlya= 0x%x \n",rampdlya_reg);

	cmpss-> RAMPDLYS.all=0x88888888;         // CMPSS Ramp Delay Shadow Register
	vu32 rampdlys_reg=cmpss->RAMPDLYS.all;     //  CMPSS Ramp Delay Shadow Register read
	printf("rampdlys= 0x%x \n",rampdlys_reg);

	cmpss->CTRIPLFILCTL.all=0x99999999;      // CTRIPL Filter Control Register
	vu32 ctriplfilctl_reg=cmpss->CTRIPLFILCTL.all;     //  CTRIPL Filter Control Register read
	printf("ctriplfilctl= 0x%x \n",ctriplfilctl_reg);

	cmpss->CTRIPLFILCLKCTL.all=0xaaaaaaaa;   // CTRIPH Filter Clock Control Register
	vu32 ctriplfilclkctl_reg=cmpss->CTRIPLFILCLKCTL.all;     //  CTRIPH Filter Clock Control Register read
	printf("ctriplfilclkctl= 0x%x \n",ctriplfilclkctl_reg);

	cmpss->CTRIPHFILCTL.all=0xbbbbbbbb;      // CTRIPL Filter Control Register
	vu32 ctriphfilctl_reg=cmpss->CTRIPHFILCTL.all;     //  CTRIPH Filter Clock Control Register read
	printf("ctriphfilctl= 0x%x \n",ctriphfilctl_reg);

	cmpss->CTRIPHFILCLKCTL.all=0xcccccccc;   // CTRIPH Filter Clock Control Register
	vu32 ctriphfilclkctl_reg=cmpss->CTRIPHFILCLKCTL.all;     //  CTRIPH Filter Clock Control Register read
	printf("ctriphfilclkctl= 0x%x \n",ctriphfilclkctl_reg);

	cmpss->COMPLOCK.all=0xdddddddd;           // CMPSS Lock Register
	vu32 complock_reg=cmpss->COMPLOCK.all;     // CMPSS Lock Register read
	printf("complock= 0x%x \n",complock_reg);

	cmpss->COMPDACHCTL.all=0xeeeeeeee;
	vu32 compdachctl_reg=cmpss->COMPDACHCTL.all;
	printf("compdachctl= 0x%x \n",compdachctl_reg);

	cmpss->COMPDACLCTL.all=0xffffffff;
	vu32 compdaclctl_reg=cmpss->COMPDACLCTL.all;
	printf("compdaclctl= 0x%x \n",compdaclctl_reg);

    EDIS;

}

void test_cmpss_compare(u8 ch)//
{
	EALLOW;
	volatile struct CMPSS_REGS *cmpss = (volatile struct CMPSS_REGS *)(CMPSS_BASE+ch*0x100);
	cmpss->COMPCTL.bit.COMPLSOURCE=0x1;
	cmpss->COMPCTL.bit.COMPLINV=0x1; //convert the output
	cmpss->COMPCTL.bit.CTRIPLSEL=0x1;//low output to epwm choose syncoutput
    cmpss->COMPDACLCTL.bit.COMPH_HYS=0x1;// COMPL_HYS

	int delay=1000;
	while(delay--)

	cmpss->COMPCTL.bit.COMPHSOURCE=0x1;
	cmpss->COMPCTL.bit.COMPHINV=0x1; //convert the output
	cmpss->COMPCTL.bit.CTRIPHSEL=0x1; //high output to epwm choose syncoutput
    cmpss->COMPDACHCTL.bit.COMPH_HYS=0x1;// COMPH_HYS

	delay=1000;
	while(delay--)
    cmpss->COMPCTL.bit.COMPDACE=0x1;
//	cmpss->COMPSTSCLR.bit.HSYNCCLREN=0x1; // high syncoutput update by EPWMSYNCPER
//	cmpss->COMPSTSCLR.bit.LSYNCCLREN=0x1; // low  syncoutput update by EPWMSYNCPER

    cmpss->COMPSTSCLR.bit.LLATCHCLR=0x1;   //low clr latch signal update by software
	delay=1000;
	while(delay--)
    cmpss->COMPSTSCLR.bit.HLATCHCLR=0x1;   //high clr latch signal update by software
	printf("test compare1 done \n");
    EDIS;
}

void test_cmpss_dac(u8 ch)
{
	EALLOW;
	volatile struct CMPSS_REGS *cmpss = (volatile struct CMPSS_REGS *)(CMPSS_BASE+ch*0x100);
	cmpss->COMPCTL.bit.COMPDACE=0x1;//Enable

	cmpss->COMPSTSCLR.bit.HSYNCCLREN=0x0;//forbid high syncoutput update by EPWMSYNCPER
	cmpss->COMPSTSCLR.bit.LSYNCCLREN=0x0;//forbid low syncoutput update by EPWMSYNCPER


//	cmpss->COMPDACCTL.bit.SWLOADSEL=0x0;//DACxVALA is updated from DACxVALS on SYSCL
	cmpss->COMPDACCTL.bit.SWLOADSEL=0x1;//DACxVALA is updated from DACxVALS on EPWMSYNCPER

	cmpss->COMPDACCTL.bit.SELREF=0x0;//VDAC is the voltage reference for the DAC
	cmpss->DACLVALS.bit.DACVAL=0x1;
	cmpss->DACHVALS.bit.DACVAL=0xfff;
	//sysclk sync
	cmpss->COMPCTL.bit.CTRIPHSEL=0x1; //high output to epwm choose syncoutput
	cmpss->COMPCTL.bit.CTRIPLSEL=0x1;//low output to epwm choose syncoutput
	cmpss->COMPCTL.bit.CTRIPOUTHSEL=0x1;//high output to output x-bar choose syncoutput
	cmpss->COMPCTL.bit.CTRIPOUTLSEL=0x1;//low output to output x-bar choose syncoutput
	int delay=1000;
	while(delay--)
//	cmpss->COMPSTSCLR.bit.HSYNCCLREN=0x1;//on high syncoutput update by EPWMSYNCPER
//	cmpss->COMPSTSCLR.bit.LSYNCCLREN=0x1;//on low syncoutput update by EPWMSYNCPER

//	cmpss->COMPSTSCLR.bit.HLATCHCLR=0x1;//high comparator latch software clear
//	cmpss->COMPSTSCLR.bit.LLATCHCLR=0x1;//low  comparator latch software clear

	//
    EDIS;
}

void test_cmpss_fil(u8 ch){

	EALLOW;
	volatile struct CMPSS_REGS *cmpss = (volatile struct CMPSS_REGS *)(CMPSS_BASE+ch *0x100);
	cmpss->COMPCTL.bit.COMPDACE=0x1;//Enable
//	cmpss->COMPHYSCTL.all=0x0;
//	cmpss->COMPSTSCLR.all=0x0;
	cmpss->COMPSTSCLR.bit.HSYNCCLREN=0x1;
	cmpss->COMPSTSCLR.bit.LSYNCCLREN=0x1;

 	cmpss->COMPDACCTL.bit.SWLOADSEL=0x0;//DACxVALA is updated from DACxVALS on SYSCL
//	cmpss->COMPDACCTL.bit.SWLOADSEL=0x1;//DACxVALA is updated from DACxVALS on EPWMSYNCPER
//	cmpss->COMPDACCTL.bit.SELREF=0x1;//VDAC is the voltage reference for the DAC

	cmpss->DACLVALS.bit.DACVAL=0x1;
	cmpss->DACHVALS.bit.DACVAL=0xfff;
    int delay=1000;
	while(delay--)
	cmpss->CTRIPHFILCTL.bit.FILINIT=0x1;//High filter initialization
	cmpss->CTRIPLFILCTL.bit.FILINIT=0x1;//Low filter initialization
	cmpss->CTRIPHFILCTL.bit.FILINIT=0x0;//High filter initialization
	cmpss->CTRIPLFILCTL.bit.FILINIT=0x0;//Low filter initialization
	cmpss->CTRIPLFILCTL.bit.THRESH=0x1;//Low filter majority voting threshold
	cmpss->CTRIPLFILCTL.bit.SAMPWIN=0x1;//Low filter sample window size
	cmpss->CTRIPHFILCTL.bit.THRESH=0x1;//High filter majority voting threshold
	cmpss->CTRIPHFILCTL.bit.SAMPWIN=0x1;//High filter sample window size


	cmpss->CTRIPLFILCLKCTL.all=0x0000000f;//Low filter sample clock prescale
	cmpss->CTRIPHFILCLKCTL.all=0x0000000f;//high filter sample clock prescale

	//ASYNC
	cmpss->COMPCTL.bit.ASYNCHEN=0x1;
	cmpss->COMPCTL.bit.ASYNCLEN=0x1;

	//fil output
	cmpss->COMPCTL.bit.CTRIPHSEL=0x2;
	cmpss->COMPCTL.bit.CTRIPLSEL=0x2;
	cmpss->COMPCTL.bit.CTRIPOUTHSEL=0x2;
	cmpss->COMPCTL.bit.CTRIPOUTLSEL=0x2;

	printf("fil set done \n");
	cmpss->DACLVALS.bit.DACVAL=0x0;
	cmpss->DACHVALS.bit.DACVAL=0x0;

    delay=1000;
	while(delay--)
    cmpss->DACLVALS.bit.DACVAL=0xfff;
    cmpss->DACHVALS.bit.DACVAL=0xfff;
    printf("fil set done \n");
    delay=100;
	while(delay--)


	//latch output
	cmpss->COMPCTL.bit.CTRIPHSEL=0x3;
	cmpss->COMPCTL.bit.CTRIPLSEL=0x3;
	cmpss->COMPCTL.bit.CTRIPOUTHSEL=0x3;
	cmpss->COMPCTL.bit.CTRIPOUTLSEL=0x3;

	delay=100;
	while(delay--)




	//	cmpss->COMPCTL.all=0x0000b110;//latch output
	//	cmpss->COMPCTL.all=0x0000c190//ASYNC
	EDIS;

}

void test_cmpss_ramp(u8 ch){
	EALLOW;
	volatile struct CMPSS_REGS *cmpss = (volatile struct CMPSS_REGS *)(CMPSS_BASE+ch*0x100);
//	cmpss->COMPCTL.all=0x00002111;//DAC input
	cmpss->COMPCTL.bit.COMPDACE=1;//;//Enable DAC
	cmpss->COMPCTL.bit.COMPHSOURCE=0;//choose high dac as input
	cmpss->COMPCTL.bit.COMPLSOURCE=0;//choose low dac as input

	cmpss->COMPDACCTL.bit.DACSOURCE=0x1;//choose ramp as dac input

	cmpss->RAMPMAXREFS=0x0fff;//ramp value
	cmpss->RAMPDECVALS=0x0fff;//ramp Decrement Value

	cmpss->RAMPDLYS.all=0x0f;//Ramp Delay Active Register

//	cmpss->COMPDACCTL.bit.RAMPLOADSEL=0x1;//RAMPSTS is loaded from RAMPMAXREFS

    EDIS;
}

void test_choosecmpss_input( ){
	EALLOW;

	volatile struct ANALOG_SUBSYS_REGS *analog_subsys = (volatile struct ANALOG_SUBSYS_REGS *)(0x0100a000);
	analog_subsys->CMPHNMXSEL.bit.CMP1HNMXSEL=0x0;// 1 channel high CMP_N input
	analog_subsys->CMPLNMXSEL.bit.CMP1LNMXSEL=0x0;// 1 channel low CMP_N input

	analog_subsys->CMPHPMXSEL.bit.CMP1HPMXSEL=0x2;// 1 channel high CMP_P input
	analog_subsys->CMPLPMXSEL.bit.CMP1LPMXSEL=0x1;// 1 channel low CMP_P input

	analog_subsys->CMPHNMXSEL.bit.CMP2HNMXSEL=0x0;// 2 channel high CMP_N input
	analog_subsys->CMPLNMXSEL.bit.CMP2LNMXSEL=0x0;// 2 channel low CMP_N input

	analog_subsys->CMPHPMXSEL.bit.CMP2HPMXSEL=0x1;// 2 channel high CMP_P input
	analog_subsys->CMPLPMXSEL.bit.CMP2LPMXSEL=0x2;// 2 channel low CMP_P input

	analog_subsys->CMPHNMXSEL.bit.CMP3HNMXSEL=0x0;// 3 channel high CMP_N input
	analog_subsys->CMPLNMXSEL.bit.CMP3LNMXSEL=0x0;// 3 channel low CMP_N input

	analog_subsys->CMPHPMXSEL.bit.CMP3HPMXSEL=0x3;// 3 channel high CMP_P input
	analog_subsys->CMPLPMXSEL.bit.CMP3LPMXSEL=0x4;// 3 channel low CMP_P input

	analog_subsys->CMPHNMXSEL.bit.CMP4HNMXSEL=0x0;// 4 channel high CMP_N input
	analog_subsys->CMPLNMXSEL.bit.CMP4LNMXSEL=0x0;// 4 channel low CMP_N input

	analog_subsys->CMPHPMXSEL.bit.CMP4HPMXSEL=0x4;// 4 channel high CMP_P input
	analog_subsys->CMPLPMXSEL.bit.CMP4LPMXSEL=0x3;// 4 channel low CMP_P input

	analog_subsys->CMPHNMXSEL.bit.CMP5HNMXSEL=0x0;// 5 channel high CMP_N input
	analog_subsys->CMPLNMXSEL.bit.CMP5LNMXSEL=0x0;// 5 channel low CMP_N input

	analog_subsys->CMPHPMXSEL.bit.CMP5HPMXSEL=0x5;// 5 channel high CMP_P input
	analog_subsys->CMPLPMXSEL.bit.CMP5LPMXSEL=0x6;// 5 channel low CMP_P input

	analog_subsys->CMPHNMXSEL.bit.CMP6HNMXSEL=0x0;// 6 channel high CMP_N input
	analog_subsys->CMPLNMXSEL.bit.CMP6LNMXSEL=0x0;// 6 channel low CMP_N input

	analog_subsys->CMPHPMXSEL.bit.CMP6HPMXSEL=0x6;// 6 channel high CMP_P input
	analog_subsys->CMPLPMXSEL.bit.CMP6LPMXSEL=0x5;// 6 channel low CMP_P input

	analog_subsys->CMPHNMXSEL.bit.CMP7HNMXSEL=0x0;// 7 channel high CMP_N input
	analog_subsys->CMPLNMXSEL.bit.CMP7LNMXSEL=0x0;// 7 channel low CMP_N input

	analog_subsys->CMPHPMXSEL.bit.CMP7HPMXSEL=0x2;// 7 channel high CMP_P input
	analog_subsys->CMPLPMXSEL.bit.CMP7LPMXSEL=0x1;// 7 channel low CMP_P input


	EDIS;


}


void test_lock_regs(u8 ch){
	EALLOW;
	volatile struct CMPSS_REGS *cmpss = (volatile struct CMPSS_REGS *)(CMPSS_BASE+ch*0x100);
	cmpss->COMPLOCK.bit.COMPCTL=0x1;
	cmpss->COMPLOCK.bit.COMPHYSCTL=0x1;
	cmpss->COMPLOCK.bit.CTRIP=0x1;
	cmpss->COMPLOCK.bit.DACCTL=0x1;

	cmpss-> COMPCTL.all=0x11111111;          // CMPSS Comparator Control Register
	vu32 compctl_reg=cmpss-> COMPCTL.all;      // CMPSS Comparator Control Register read
	printf("comphysctl_reg= 0x%x \n",compctl_reg);

	cmpss-> COMPDACCTL.all=0x33333333;       // CMPSS DAC Control Regist
	vu32 compdacctl_reg=cmpss-> COMPDACCTL.all;      // CMPSS DAC Control Register read
	printf("compdacctl_reg= 0x%x \n",compdacctl_reg);

	cmpss->CTRIPLFILCTL.all=0x99999999;      // CTRIPL Filter Control Register
	vu32 ctriplfilctl_reg=cmpss->CTRIPLFILCTL.all;     //  CTRIPL Filter Control Register read
	printf("ctriplfilctl= 0x%x \n",ctriplfilctl_reg);

	cmpss->CTRIPLFILCLKCTL.all=0xaaaaaaaa;   // CTRIPH Filter Clock Control Register
	vu32 ctriplfilclkctl_reg=cmpss->CTRIPLFILCLKCTL.all;     //  CTRIPH Filter Clock Control Register read
	printf("ctriplfilclkctl= 0x%x \n",ctriplfilclkctl_reg);

	cmpss->CTRIPHFILCTL.all=0xbbbbbbbb;      // CTRIPL Filter Control Register
	vu32 ctriphfilctl_reg=cmpss->CTRIPHFILCTL.all;     //  CTRIPH Filter Clock Control Register read
	printf("ctriphfilctl= 0x%x \n",ctriphfilctl_reg);

	cmpss->CTRIPHFILCLKCTL.all=0xcccccccc;   // CTRIPH Filter Clock Control Register
	vu32 ctriphfilclkctl_reg=cmpss->CTRIPHFILCLKCTL.all;     //  CTRIPH Filter Clock Control Register read
	printf("ctriphfilclkctl= 0x%x \n",ctriphfilclkctl_reg);


    cmpss->COMPDACHCTL.bit.COMPH_HYS=0x1;// COMPH_HYS
    vu32 CTRIPH_Filter_reg=cmpss->COMPDACHCTL.bit.COMPH_HYS;     //  CTRIPH Filter Clock Control Register read
	printf("CTRIPH_Filter_reg= 0x%x \n",CTRIPH_Filter_reg);

	cmpss->COMPLOCK.bit.COMPCTL=0x0;
	cmpss->COMPLOCK.bit.COMPHYSCTL=0x0;
	cmpss->COMPLOCK.bit.CTRIP=0x0;
	cmpss->COMPLOCK.bit.DACCTL=0x0;

	cmpss-> COMPCTL.all=0x11111111;          // CMPSS Comparator Control Register
	compctl_reg=cmpss-> COMPCTL.all;      // CMPSS Comparator Control Register read
	printf("comphysctl_reg= 0x%x \n",compctl_reg);

	cmpss-> COMPDACCTL.all=0x33333333;       // CMPSS DAC Control Regist
	compdacctl_reg=cmpss-> COMPDACCTL.all;      // CMPSS DAC Control Register read
	printf("compdacctl_reg= 0x%x \n",compdacctl_reg);

	cmpss->CTRIPLFILCTL.all=0x99999999;      // CTRIPL Filter Control Register
	ctriplfilctl_reg=cmpss->CTRIPLFILCTL.all;     //  CTRIPL Filter Control Register read
	printf("ctriplfilctl= 0x%x \n",ctriplfilctl_reg);

	cmpss->CTRIPLFILCLKCTL.all=0xaaaaaaaa;   // CTRIPH Filter Clock Control Register
	ctriplfilclkctl_reg=cmpss->CTRIPLFILCLKCTL.all;     //  CTRIPH Filter Clock Control Register read
	printf("ctriplfilclkctl= 0x%x \n",ctriplfilclkctl_reg);

	cmpss->CTRIPHFILCTL.all=0xbbbbbbbb;      // CTRIPL Filter Control Register
	ctriphfilctl_reg=cmpss->CTRIPHFILCTL.all;     //  CTRIPH Filter Clock Control Register read
	printf("ctriphfilctl= 0x%x \n",ctriphfilctl_reg);

	cmpss->CTRIPHFILCLKCTL.all=0xcccccccc;   // CTRIPH Filter Clock Control Register
	ctriphfilclkctl_reg=cmpss->CTRIPHFILCLKCTL.all;     //  CTRIPH Filter Clock Control Register read
	printf("ctriphfilclkctl= 0x%x \n",ctriphfilclkctl_reg);


    cmpss->COMPDACHCTL.bit.COMPH_HYS=0x1;// COMPH_HYS
    CTRIPH_Filter_reg=cmpss->COMPDACHCTL.bit.COMPH_HYS;     //  CTRIPH Filter Clock Control Register read
	printf("CTRIPH_Filter_reg= 0x%x \n",CTRIPH_Filter_reg);

	EDIS;


}


void pwm_normal_gen(u8 ch, u8 count_mode, u16 tbprd, u16 cmp, u16 tbphs, u8 int_type, u32 p_flag)
{
    //    volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + ch *0x200);
    /* TB */
    uint32_t epwm_base = EPWM1_BASE + ch * 0x200;
    EPWM_setTimeBaseCounterMode(epwm_base, count_mode); /* 计数模式  */
    //    EPWM_enablePhaseShiftLoad(uint32_t base)			/* 不从TBPHS加载TBCTR */
    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_SHADOW_LOAD); /* 启用影子模式读写TBPRD */
    //    EPWM_setPeriodLoadMode(epwm_base, EPWM_PERIOD_DIRECT_LOAD);     /* 启用直接模式读写TBPRD*/
    //    epwm->TBCTL.bit.SYNCOSEL = 0;      		/* 禁用EPWMxSYNCO信号，该信号拉高后会使CTR跳转为TBPHS*/
    EPWM_setSyncOutPulseMode(epwm_base, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);
    /* SWFSYNC，软件强制同步脉冲，应该是动态的，先不管 */
    //    epwm->TBCTL.bit.HSPCLKDIV = 1;     		/* TBCLK = SYSTEM_OUT_CLK/(2 * HSPCLKDIV *
    //    2^CLKDIV)高速基准时钟，为0时只由CLKDIV决定 */ epwm->TBCTL.bit.CLKDIV    = 2;     		/* TBCLK =
    //    SYSTEM_OUT_CLK/(2^CLKDIV) */
    EPWM_setClockPrescaler(epwm_base, 2, 1);
    /* PHSDIR，相位方向位，仅在递增计数时使用*/
    /* FREE_SOFT，仿真模式自由运行*/

    // epwm->TBPHS.bit.TBPHS     = tbphs;
    EPWM_setPhaseShift(epwm_base, tbphs); /* 相位偏移 */
    // epwm->TBPRD               = tbprd;
    EPWM_setTimeBasePeriod(epwm_base, tbprd); /* 时基周期设置 */
    // epwm->TBCTR               = 0;
    EPWM_setTimeBaseCounter(epwm_base, 0); /* 清零时基计数寄存器 */

    /* CC */
    //    epwm->CMPCTL.bit.SHDWAMODE = 0;
    //    epwm->CMPCTL.bit.SHDWBMODE = 0;
    //    epwm->CMPCTL.bit.LOADAMODE = 0;
    //    epwm->CMPCTL.bit.LOADBMODE = 0;
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_C, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base, EPWM_COUNTER_COMPARE_D, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    //	epwm->CMPA.bit.CMPA        = cmp;
    //	epwm->CMPB.bit.CMPB        = cmp / 2;
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_A, cmp);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_B, cmp / 2);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_C, 1);
    EPWM_setCounterCompareValue(epwm_base, EPWM_COUNTER_COMPARE_D, 2);

    /* AQ */
    // 对应赋值1则触发输出0，对应赋值1则触发输出1
    //    epwm->AQCTLA.bit.CAU = 2; /* 当CTR=CMPA且Up增计数时，EPWM1A输出高电平 */
    //    epwm->AQCTLA.bit.CAD = 1; /* 当CTR=CMPA且Down减计数时，EPWM1A输出低电平 */
    //    epwm->AQCTLB.bit.CAU = 2; /* 当CTR=CMPA且Up增计数时，EPWM1B输出高电平 */
    //    epwm->AQCTLB.bit.CAD = 1; /* 当CTR=CMPA且Down减计数时，EPWM1B输出低电平 */
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(
        epwm_base, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    /* DB */
    //    epwm->DBCTL.bit.OUT_MODE = 0; 	/* 死区完全旁路 */
    // 死区没有enable函数，只要不配置就没有

    /* PC */
    //    EPWM_enableChopper(epwm_base);	/* 斩波器完全旁路 */

    /* 是否打开中断触发 */
    if (int_type)
    {
    	Interrupt_enable(INT_EPWM1);
    }
    else
    {
    	Interrupt_disable(INT_EPWM1);
    }
//    if (p_flag)
    {
//        printf("epwm test -> ch:%d, count_mode:%d, tbprd:%d, cmp:%d, tbphs:%d, int_type:%d\n", ch, count_mode, tbprd,
//            cmp, tbphs, int_type);
 }
}

void test_cmpss(){
	puts("test cmpss begin");
#ifdef CASE1

	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1 + (0 << 8));
	SysCtl_TbClkSyncToggle(0);
	pwm_normal_gen(0, EPWM_COUNTER_MODE_UP_DOWN, SYS_CLK / 100000 / 2, SYS_CLK / 100000 / 4, 0, 0, 1);
	uint32_t epwm_base              = EPWM1_BASE + 0 * 0x200;
	volatile struct EPWM_REGS *epwm = (volatile struct EPWM_REGS *)(EPWM1_BASE + 0 * 0x200);
  //配置空窗
	//	epwm->DCFCTL.bit.PULSESEL = 0;	//offset对齐到ctr_eq_zero；ctr_eq_prd清掉ctr
	EPWM_setDigitalCompareBlankingEvent(epwm_base, EPWM_DC_WINDOW_START_TBCTR_ZERO);

	//	epwm->DCFCTL.bit.BLANKE = 1;	//使能blank
	EPWM_enableDigitalCompareBlankingWindow(epwm_base);

	//	epwm->DCFOFFSET = offset;		//空窗偏移
	//	epwm->DCFWINDOW = window;		//空窗期长度
	EPWM_setDigitalCompareWindowOffset(epwm_base, 8);
	EPWM_setDigitalCompareWindowLength(epwm_base, 16);



	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CMPSS1+(0 << 8));
    SysCtl_TbClkSyncToggle(1);

    //cmpss to epwm bar
	//XBAR_enableEPWMMux(XBAR_TRIP5,4);
	EPwmXbarRegs->TRIP4MUXENABLE.all=1;    //  XBAR_TRIP5  mux4
	XBAR_setEPWMMuxConfig(XBAR_TRIP4,XBAR_EPWM_MUX00_CMPSS);
    test_choosecmpss_input();

//	test_cmpss_reg_w_r(0);
//	test_cmpss_compare(0);
	test_cmpss_dac(0);
//	test_cmpss_ramp(0);
//	test_cmpss_fil(0);
//  test_lock_regs(0);

	//cmpss to ouput bar
	XBAR_enableOutputMux(XBAR_OUTPUT1,1);
	XBAR_setOutputLatchMode(XBAR_OUTPUT1,1);
	XBAR_clearOutputLatch(XBAR_OUTPUT1);
	XBAR_setOutputMuxConfig(XBAR_OUTPUT1,XBAR_OUT_MUX00_CMPSS);

	DAC_REGS *dac_regs = (DAC_REGS *)(0x0100d000);
	dac_regs->DACCTL.bit.DACREFSEL=0x00;
	simple_delay(50);
	dac_regs->DACCTL.bit.DACREFSEL=0x01;
	simple_delay(50);
	dac_regs->DACCTL.bit.DACREFSEL=0x2;

	printf("test complete");
#endif
}
