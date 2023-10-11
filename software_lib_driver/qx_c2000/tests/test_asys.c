#include "common.h"

void test_TSNS()
{
    puts("test_TempertureSensor");
    ASysCtl_enableTemperatureSensor();
}

void test_AsysCtl_VREFHI_A_Forbidden_Model()
{
    puts("test_reference_A__start");
    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIA, ASYSCTL_VOL_2_0V);
    // Set Forbidden model
    AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_A    = 1;
    AnalogSubsysRegs->ANAREFCTL.bit.EN_VREFBI_A = 1;
    puts("test_reference_A");
}

void test_AsysCtl_VREFHI_BC_Forbidden_Model()
{
    puts("test_reference_BC_Forbidden_Model__start");
    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIBC, ASYSCTL_VOL_2_0V);
    // Set Forbidden model
    AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_BC    = 1;
    AnalogSubsysRegs->ANAREFCTL.bit.EN_VREFBI_BC = 1;
    puts("test_reference_BC_Forbidden_Model");
}

void test_referenceA_High_Resistenace_State()
{
    puts("test_reference_A__start");
    ASysCtl_setAnalogReferenceExternal(ASYSCTL_VREFHIA);
    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIA, ASYSCTL_VOL_2_5V);
    puts("test_reference_A_High_Resistenace_State");
}

void test_referenceBC_High_Resistenace_State()
{
    puts("test_reference_B__start");
    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIBC, ASYSCTL_VOL_2_5V);
    ASysCtl_setAnalogReferenceExternal(ASYSCTL_VREFHIBC);
    puts("test_reference_B_High_Resistenace_State");
}

void test_referenceA_2_50V()
{
    puts("test_reference_A__start");

    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIA, ASYSCTL_VOL_2_5V);
    ASysCtl_setAnalogReferenceInternal(ASYSCTL_VREFHIA);
    puts("test_reference_A");
}

void test_referenceA_2_00V()
{
    puts("test_reference_A_2_00V_start");
    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIA, ASYSCTL_VOL_2_0V);
    ASysCtl_setAnalogReferenceInternal(ASYSCTL_VREFHIA);
    puts("test_reference_A");
}

void test_referenceA_1_65V()
{
    puts("test_reference_A_1_65V_start");
    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIA, ASYSCTL_VOL_1_65V);
    ASysCtl_setAnalogReferenceInternal(ASYSCTL_VREFHIA);
    puts("test_reference_A");
}

void test_referenceBC_2_50V()
{
    puts("test_reference_BC__start");
    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIBC, ASYSCTL_VOL_2_5V);
    ASysCtl_setAnalogReferenceInternal(ASYSCTL_VREFHIBC);
    puts("test_reference_BC");
}

void test_referenceBC_2_00V()
{
    puts("test_reference_BC__start");
    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIBC, ASYSCTL_VOL_2_0V);
    ASysCtl_setAnalogReferenceInternal(ASYSCTL_VREFHIBC);

    puts("test_reference_BC");
}

void test_referenceBC_1_65V()
{
    puts("test_reference_BC__start");
    ASysCtl_setAnalogReferenceInternal(ASYSCTL_VREFHIBC);
    ASysCtl_setAnalogReferenceVol(ASYSCTL_VREFHIBC, ASYSCTL_VOL_1_65V);

    puts("test_reference_BC");
}

void test_cmpss_mux(void)
{
    int i = 0;

    for (i = 0; i < 8; i++)
    {
        AnalogSubsysRegs->CMPHPMXSEL.bit.CMP1HPMXSEL = i;
        AnalogSubsysRegs->CMPHPMXSEL.bit.CMP2HPMXSEL = i;
        AnalogSubsysRegs->CMPHPMXSEL.bit.CMP3HPMXSEL = i;
        AnalogSubsysRegs->CMPHPMXSEL.bit.CMP4HPMXSEL = i;
        AnalogSubsysRegs->CMPHPMXSEL.bit.CMP5HPMXSEL = i;
        AnalogSubsysRegs->CMPHPMXSEL.bit.CMP6HPMXSEL = i;
        AnalogSubsysRegs->CMPHPMXSEL.bit.CMP7HPMXSEL = i;

        AnalogSubsysRegs->CMPLPMXSEL.bit.CMP1LPMXSEL = i;
        AnalogSubsysRegs->CMPLPMXSEL.bit.CMP2LPMXSEL = i;
        AnalogSubsysRegs->CMPLPMXSEL.bit.CMP3LPMXSEL = i;
        AnalogSubsysRegs->CMPLPMXSEL.bit.CMP4LPMXSEL = i;
        AnalogSubsysRegs->CMPLPMXSEL.bit.CMP5LPMXSEL = i;
        AnalogSubsysRegs->CMPLPMXSEL.bit.CMP6LPMXSEL = i;
        AnalogSubsysRegs->CMPLPMXSEL.bit.CMP7LPMXSEL = i;
    }

    for (i = 0; i < 4; i++)
    {
        AnalogSubsysRegs->CMPHNMXSEL.bit.CMP1HNMXSEL = i;
        AnalogSubsysRegs->CMPHNMXSEL.bit.CMP2HNMXSEL = i;
        AnalogSubsysRegs->CMPHNMXSEL.bit.CMP3HNMXSEL = i;
        AnalogSubsysRegs->CMPHNMXSEL.bit.CMP4HNMXSEL = i;
        AnalogSubsysRegs->CMPHNMXSEL.bit.CMP5HNMXSEL = i;
        AnalogSubsysRegs->CMPHNMXSEL.bit.CMP6HNMXSEL = i;
        AnalogSubsysRegs->CMPHNMXSEL.bit.CMP7HNMXSEL = i;

        AnalogSubsysRegs->CMPLNMXSEL.bit.CMP1LNMXSEL = i;
        AnalogSubsysRegs->CMPLNMXSEL.bit.CMP2LNMXSEL = i;
        AnalogSubsysRegs->CMPLNMXSEL.bit.CMP3LNMXSEL = i;
        AnalogSubsysRegs->CMPLNMXSEL.bit.CMP4LNMXSEL = i;
        AnalogSubsysRegs->CMPLNMXSEL.bit.CMP5LNMXSEL = i;
        AnalogSubsysRegs->CMPLNMXSEL.bit.CMP6LNMXSEL = i;
        AnalogSubsysRegs->CMPLNMXSEL.bit.CMP7LNMXSEL = i;
    }
}

void test_tsns(void)
{
    int i = 0;

    puts("test asys reg config...");

    AnalogSubsysRegs->TSNSCTL.bit.ENABLE = 1;
    AnalogSubsysRegs->TSNSCTL.bit.ENABLE = 0;

    AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_A       = 1;
    AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_A       = 0;
    AnalogSubsysRegs->ANAREFCTL.bit.EN_VREFBI_A    = 1;
    AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_A = 3;
    AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_A = 2;
    AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_A = 1;
    AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_A = 0;

    AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_BC       = 1;
    AnalogSubsysRegs->ANAREFCTL.bit.EN_HIZ_BC       = 0;
    AnalogSubsysRegs->ANAREFCTL.bit.EN_VREFBI_BC    = 1;
    AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_BC = 3;
    AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_BC = 2;
    AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_BC = 1;
    AnalogSubsysRegs->ANAREFCTL.bit.SEL_VREFBIBI_BC = 0;

    AnalogSubsysRegs->ANAREFCTL.bit.rsvd1 = 1; // EN_VR_EX
    AnalogSubsysRegs->ANAREFCTL.bit.rsvd1 = 0; // EN_VR_EX
}

void test_pm(void)
{
    int i = 0;

    AnalogSubsysRegs->VMONCTL.bit.BORLVMONDIS = 1;
    AnalogSubsysRegs->VMONCTL.bit.BORLVMONDIS = 0;

    for (i = 0; i < 8; i++) // ADJ_PVD
        AnalogSubsysRegs->VMONCTL.bit.rsvd1 = i;

    AnalogSubsysRegs->DCDCCTL.bit.DCDCEN = 1;
    AnalogSubsysRegs->DCDCCTL.bit.DCDCEN = 0;

    for (i = 0; i < 4; i++) // work mode
        AnalogSubsysRegs->DCDCCTL.bit.rsvd1 = i;

    for (i = 0; i < 4; i++) // offset detail
        AnalogSubsysRegs->DCDCCTL.bit.rsvd2 = i;

    for (i = 0; i < 4; i++) // Current adjust detail
        AnalogSubsysRegs->DCDCCTL.bit.rsvd3 = i;

    for (i = 0; i < 4; i++) // Ripple adjust detail
        AnalogSubsysRegs->DCDCCTL.bit.rsvd4 = i;

    for (i = 0; i < 16; i++) // frequency adjust
        AnalogSubsysRegs->DCDCCTL.bit.rsvd5 = i;
    // operation mode
    AnalogSubsysRegs->DCDCCTL.bit.rsvd6 = 1;
    AnalogSubsysRegs->DCDCCTL.bit.rsvd6 = 0;

    for (i = 0; i < 4; i++)
        AnalogSubsysRegs->DCDCCTL.bit.MD_LXDET = i;
}

void test_asys()
{
//     test_TSNS();
	   test_referenceA_2_50V();
//     test_referenceA_2_00V();
//     test_referenceA_1_65V();
//     test_referenceBC_2_50V();
//     test_referenceBC_2_00V();
// 	   test_referenceBC_1_65V();
//	   test_AsysCtl_VREFHI_A_Forbidden_Model();
//	   test_AsysCtl_VREFHI_BC_Forbidden_Model();
//     test_referenceA_High_Resistenace_State();
//     test_referenceBC_High_Resistenace_State();
// 	   test_dcdc();
    // test_cmpss_mux();
    // test_tsns();
//    test_pm();

}
