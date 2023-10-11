#include "common.h"

#define EVENT0_INT 16
#define EVENT1_INT 17
#define EVENT2_INT 18
#define EVENT3_INT 19

// core1 uart
// #define IPC_FUNC0
// core1 set interrupt(disabled, use FUNC9 instead)
// #define IPC_FUNC1
// core0 set interrupt(disabled, use FUNC10 instead)
// #define IPC_FUNC2
// core0 to core1 reg
// #define IPC_FUNC3
// core1 to core0 reg
// #define IPC_FUNC4
// shared ram0
// #define IPC_FUNC5
// shared ram1
// #define IPC_FUNC6
// core0 clr
// #define IPC_FUNC7
// core1 clr
// #define IPC_FUNC8
// core1 to core0
// #define IPC_FUNC9
// core0 to core1
#define IPC_FUNC10

// core0 test and intr_func
#ifdef QX_C2000_CORE0

void ipc_func0()
{
    while (1)
        ;
}

void ipc_func1()
{
    StdOutInit(SciaRegs);
    printf("core0 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    IPC_ack(IPC_EVENT1);
    printf("dual core has booted\n");
    Interrupt_enable(PIC_GROUP6);

    int counter = 1000;
    while (counter--)
        ;

    printf("core0 test end\n");
}

void ipc_func2()
{
    StdOutInit(SciaRegs);
    // printf("core0 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);
    Interrupt_enable(PIC_GROUP6);

    // printf("dual core has booted\n");

    IPC_set(IPC_EVENT1); // core1 set interrupt

    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    // printf("core0 test end\n");
}

void ipc_func3()
{
    StdOutInit(SciaRegs);
    // printf("core0 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    // printf("dual core has booted\n");

    int sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }

    int reply = IPC_read_share_reg(IPC_SHARE_REG_R0);
    int com   = IPC_read_share_reg(IPC_SHARE_REG_R1);
    int addr  = IPC_read_share_reg(IPC_SHARE_REG_R3);
    int data  = IPC_read_share_reg(IPC_SHARE_REG_R4);

    if (reply == 4 && com == 1 && addr == 2 && data == 3)
    {
        IPC_ack(IPC_EVENT1);
    }

    // printf("core0 test end\n");
}

void ipc_func4()
{
    StdOutInit(SciaRegs);
    // printf("core0 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    IPC_ack(IPC_EVENT1);

    // printf("dual core has booted\n");

    IPC_write_share_reg(IPC_SHARE_REG_WR0, 1);
    IPC_write_share_reg(IPC_SHARE_REG_WR1, 2);
    IPC_write_share_reg(IPC_SHARE_REG_WR2, 3);
    IPC_write_share_reg(IPC_SHARE_REG_WR3, 4);

    IPC_set(IPC_EVENT1);

    int flg = 0;
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    // printf("core0 test end\n");
}

void ipc_func5()
{
    StdOutInit(SciaRegs);
    // printf("core0 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    IPC_ack(IPC_EVENT1);

    // printf("dual core has booted\n");

    int *a = (int *)(0x00100000);
    *a     = 0x55aa;
    int *b = (int *)(0x00101000);
    *b     = 0x55aa;

    IPC_set(IPC_EVENT1);

    int flg = 0;
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    // printf("core0 test end\n");
}

void ipc_func6()
{
    StdOutInit(SciaRegs);
    // printf("core0 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    IPC_ack(IPC_EVENT1);

    // printf("dual core has booted\n");

    sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }

    int *a = (int *)(0x00100000);
    int *b = (int *)(0x00101000);

    if (*a != 0x55aa && *b == 0x55aa)
    {
        IPC_ack(IPC_EVENT1);
        // 	printf("core0 test end\n");
    }
}

void ipc_func7()
{
    StdOutInit(SciaRegs);
    // printf("core0 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    IPC_ack(IPC_EVENT1);

    // printf("dual core has booted\n");

    IPC_set(IPC_EVENT2);
    if (IPC_flag(IPC_EVENT2) == 0)
    {
        // printf("core0 set failed\n");
        return;
    }
    sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT3);
    }
    IPC_clear(IPC_EVENT2);
    if (IPC_flag(IPC_EVENT2) == 0)
    {
        IPC_ack(IPC_EVENT3);
        // printf("core0 test end\n");
    }
}

void ipc_func8()
{
    StdOutInit(SciaRegs);
    // printf("core0 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    IPC_ack(IPC_EVENT1);

    // printf("dual core has booted\n");

    sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT2);
    }

    IPC_set(IPC_EVENT3);
    int flg = 0;
    do
    {
        sts = IPC_status(IPC_EVENT2);
    } while (sts);
    do
    {
        flg = IPC_flag(IPC_EVENT3);
    } while (flg);
    // printf("core0 test end\n");
}

void ipc_func9()
{
    StdOutInit(SciaRegs);
    printf("core0 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    IPC_ack(IPC_EVENT1);
    printf("dual core has booted\n");
    Interrupt_enable(PIC_GROUP6);

    int counter = 100;
    while (counter--)
        ;

    printf("core0 test end\n");
}

void ipc_func10()
{
    // StdOutInit(SciaRegs);
    // printf("core0 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    IPC_ack(IPC_EVENT1);

    // printf("dual core has booted\n");

    int *p      = (int *)(0x00100000);
    int counter = 0;
    while (counter < 10)
    {
        *p = counter;
        counter++;
        p++;
    }

    IPC_write_share_reg(IPC_SHARE_REG_WR0, 10);
    IPC_write_share_reg(IPC_SHARE_REG_WR1, 0x00100000);

    IPC_set(IPC_EVENT0); // core1 set interrupt

    int flg = 0;
    do
    {
        flg = IPC_flag(IPC_EVENT0);
    } while (flg);

    // printf("core0 test end\n");
}

void pic_isr_ipc(unsigned int int_flag)
{
    switch (int_flag)
    {
        case EVENT0_INT:
            printf("event0 intr handled\n");
            int com     = IPC_read_share_reg(IPC_SHARE_REG_R1);
            int addr    = IPC_read_share_reg(IPC_SHARE_REG_R3);
            int *p      = (int *)addr;
            int counter = 0;
            while (counter < com)
            {
                printf("%d ", *p);
                counter++;
                p++;
            }
            printf("\n");
            IPC_ack(IPC_EVENT0);
            break;
        case EVENT1_INT:
            printf("event1 intr handled\n");
            IPC_ack(IPC_EVENT1);
            break;
        case EVENT2_INT:
            printf("event2 intr handled\n");
            IPC_ack(IPC_EVENT2);
            break;
        case EVENT3_INT:
            printf("event3 intr handled\n");
            IPC_ack(IPC_EVENT2);
            break;
        default:
            printf("invalid intr!\n");
    }
}

void test_ipc(void)
{

#ifdef IPC_FUNC0
    ipc_func0();
#endif

#ifdef IPC_FUNC1
    ipc_func1();
#endif

#ifdef IPC_FUNC2
    ipc_func2();
#endif

#ifdef IPC_FUNC3
    ipc_func3();
#endif

#ifdef IPC_FUNC4
    ipc_func4();
#endif

#ifdef IPC_FUNC5
    ipc_func5();
#endif

#ifdef IPC_FUNC6
    ipc_func6();
#endif

#ifdef IPC_FUNC7
    ipc_func7();
#endif

#ifdef IPC_FUNC8
    ipc_func8();
#endif

#ifdef IPC_FUNC9
    ipc_func9();
#endif

#ifdef IPC_FUNC10
    ipc_func10();
#endif
}

#endif

// core1 test and intr_func
#ifdef QX_C2000_CORE1

void ipc_func0()
{
    StdOutInit(SciaRegs);
    printf("core1 test start...\n");
    while (1)
        ;
}

void ipc_func1()
{
    // StdOutInit(SciaRegs);
    // printf("core1 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);
    // Interrupt_enable(PIC_GROUP6);

    // printf("dual core has booted\n");

    IPC_set(IPC_EVENT1); // core1 set interrupt

    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    // printf("core1 test end\n");
}

void ipc_func2()
{
    StdOutInit(SciaRegs);
    printf("core1 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    Interrupt_enable(PIC_GROUP6);
    IPC_ack(IPC_EVENT1);

    printf("dual core has booted\n");

    int counter = 0;
    while (1)
    {
        counter++;
        sts = IPC_status(IPC_EVENT1);
        if (sts != 0)
        {
            break;
        }
    }
    IPC_ack(IPC_EVENT1);
    printf("core1 test end\n");
}

void ipc_func3()
{
    StdOutInit(SciaRegs);
    printf("core1 test start...\n");

    IPC_EVENT_INDEX sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }
    IPC_ack(IPC_EVENT1);

    printf("dual core has booted\n");
    IPC_write_share_reg(IPC_SHARE_REG_WR0, 1);
    IPC_write_share_reg(IPC_SHARE_REG_WR1, 2);
    IPC_write_share_reg(IPC_SHARE_REG_WR2, 3);
    IPC_write_share_reg(IPC_SHARE_REG_WR3, 4);

    IPC_set(IPC_EVENT1);

    int flg = 0;
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    printf("core1 test end\n");
}

void ipc_func4()
{
    StdOutInit(SciaRegs);
    printf("core1 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    printf("dual core has booted\n");

    int sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }

    int reply = IPC_read_share_reg(IPC_SHARE_REG_R0);
    int com   = IPC_read_share_reg(IPC_SHARE_REG_R1);
    int addr  = IPC_read_share_reg(IPC_SHARE_REG_R3);
    int data  = IPC_read_share_reg(IPC_SHARE_REG_R4);

    if (reply == 4 && com == 1 && addr == 2 && data == 3)
    {
        IPC_ack(IPC_EVENT1);
    }

    printf("core1 test end\n");
}

void ipc_func5()
{
    StdOutInit(SciaRegs);
    printf("core1 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    printf("dual core has booted\n");

    int sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT1);
    }

    int *a = (int *)(0x00100000);
    int *b = (int *)(0x00101000);
    if (*a == 0x55aa && *b != 0x55aa)
    {
        IPC_ack(IPC_EVENT1);
    }

    printf("core1 test end\n");
}

void ipc_func6()
{
    StdOutInit(SciaRegs);
    printf("core1 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    printf("dual core has booted\n");

    int *a = (int *)(0x00100000);
    int *b = (int *)(0x00101000);
    *a     = 0x55aa;
    *b     = 0x55aa;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);
    printf("core1 test end\n");
}

void ipc_func7()
{
    StdOutInit(SciaRegs);
    printf("core1 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    printf("dual core has booted\n");

    int sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT2);
    }

    IPC_set(IPC_EVENT3);
    do
    {
        sts = IPC_status(IPC_EVENT2);
    } while (sts);
    do
    {
        flg = IPC_flag(IPC_EVENT3);
    } while (flg);
    printf("core1 test end\n");
}

void ipc_func8()
{
    StdOutInit(SciaRegs);
    printf("core1 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);

    printf("dual core has booted\n");
    IPC_set(IPC_EVENT2);
    if (IPC_flag(IPC_EVENT2) == 0)
    {
        printf("core0 set failed\n");
        return;
    }
    int sts = 0;
    while (!sts)
    {
        sts = IPC_status(IPC_EVENT3);
    }
    IPC_clear(IPC_EVENT2);
    if (IPC_flag(IPC_EVENT2) == 0)
    {
        IPC_ack(IPC_EVENT3);
        printf("core1 test end\n");
    }
}

void ipc_func9()
{
    // StdOutInit(SciaRegs);
    // printf("core1 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);
    // Interrupt_enable(PIC_GROUP6);

    // printf("dual core has booted\n");

    int *p      = (int *)(0x00101000);
    int counter = 0;
    while (counter < 10)
    {
        *p = counter;
        counter++;
        p++;
    }

    IPC_write_share_reg(IPC_SHARE_REG_WR0, 10);
    IPC_write_share_reg(IPC_SHARE_REG_WR1, 0x00101000);

    IPC_set(IPC_EVENT0); // core1 set interrupt

    do
    {
        flg = IPC_flag(IPC_EVENT0);
    } while (flg);

    // printf("core1 test end\n");
}

void ipc_func10()
{
    StdOutInit(SciaRegs);
    printf("core1 test start...\n");

    IPC_EVENT_INDEX flg = 0;
    IPC_set(IPC_EVENT1);
    do
    {
        flg = IPC_flag(IPC_EVENT1);
    } while (flg);
    printf("dual core has booted\n");
    Interrupt_enable(PIC_GROUP6);

    int counter = 100;
    while (counter--)
        ;

    printf("core1 test end\n");
}

void pic_isr_ipc(unsigned int int_flag)
{
    switch (int_flag)
    {
        case EVENT0_INT:
            printf("event0 intr handled\n");
            int com  = IPC_read_share_reg(IPC_SHARE_REG_R1);
            int addr = IPC_read_share_reg(IPC_SHARE_REG_R3);
            printf("com is %d\n", com);
            printf("addr is %x\n", addr);
            int *p      = (int *)addr;
            int counter = 0;
            while (counter < com)
            {
                printf("%d ", *p);
                counter++;
                p++;
            }
            printf("\n");
            IPC_ack(IPC_EVENT0);
            break;
        case EVENT1_INT:
            printf("event1 intr handled\n");
            IPC_ack(IPC_EVENT1);
            break;
        case EVENT2_INT:
            printf("event2 intr handled\n");
            IPC_ack(IPC_EVENT2);
            break;
        case EVENT3_INT:
            printf("event3 intr handled\n");
            IPC_ack(IPC_EVENT2);
            break;
        default:
            printf("invalid intr!\n");
    }
}

void test_ipc(void)
{

#ifdef IPC_FUNC0
    ipc_func0();
#endif

#ifdef IPC_FUNC1
    ipc_func1();
#endif

#ifdef IPC_FUNC2
    ipc_func2();
#endif

#ifdef IPC_FUNC3
    ipc_func3();
#endif

#ifdef IPC_FUNC4
    ipc_func4();
#endif

#ifdef IPC_FUNC5
    ipc_func5();
#endif

#ifdef IPC_FUNC6
    ipc_func6();
#endif

#ifdef IPC_FUNC7
    ipc_func7();
#endif

#ifdef IPC_FUNC8
    ipc_func8();
#endif

#ifdef IPC_FUNC9
    ipc_func9();
#endif

#ifdef IPC_FUNC10
    ipc_func10();
#endif
}

#endif
