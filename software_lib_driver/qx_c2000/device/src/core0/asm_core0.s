# export _core0_start for link script
.global _dsp_core0_start

# declare symbol main for C function main()
.extern system_init

.section .vector
jmp exception_nc||
movigl GR28 0xBF00||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF01||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF02||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF03||
nop||
nop||

jmp pic_group_nc||
movigl GR28 0xBF04||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF05||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF6||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF07||
nop||
nop||

jmp exception_nc||
movigl GR28 0xBF08||
nop||
nop||

jmp pic_group_nc||
movigl GR28 0xBF09||
nop||
nop||

#0 10
nop||
nop||
nop||
nop||

#0 11
nop||
nop||
nop||
nop||

#0 12
nop||
nop||
nop||
nop||

#0 13
nop||
nop||
nop||
nop||

#0 14
nop||
nop||
nop||
nop||

#0 15
nop||
nop||
nop||
nop||

#1 0
jmp trace_isr||
nop||
nop||
nop||

#1 1
jmp wp_exp_isr||
nop||
nop||
nop||

#1 2
jmp adca1_isr||
nop||
nop||
nop||

#1 3
jmp adcb1_isr||
nop||
nop||
nop||

#1 4
jmp adcc1_isr||
nop||
nop||
nop||

#1 5
jmp xint1_isr||
nop||
nop||
nop||

#1 6
jmp xint2_isr||
nop||
nop||
nop||

#1 7
nop||
nop||
nop||
nop||

#1 8
jmp timer0_isr||
nop||
nop||
nop||

#1 9
jmp wake_wdog_isr||
nop||
nop||
nop||

#1 10
nop||
nop||
nop||
nop||

#1 11
nop||
nop||
nop||
nop||

#1 12
nop||
nop||
nop||
nop||

#1 13
nop||
nop||
nop||
nop||

#1 14
nop||
nop||
nop||
nop||

#1 15
nop||
nop||
nop||
nop||

#2 0
jmp epwm1_tz_isr||
nop||
nop||
nop||

#2 1
jmp epwm2_tz_isr||
nop||
nop||
nop||

#2 2
jmp epwm3_tz_isr||
nop||
nop||
nop||

#2 3
jmp epwm4_tz_isr||
nop||
nop||
nop||

#2 4
jmp epwm5_tz_isr||
nop||
nop||
nop||

#2 5
jmp epwm6_tz_isr||
nop||
nop||
nop||

#2 6
jmp epwm7_tz_isr||
nop||
nop||
nop||

#2 7
jmp epwm8_tz_isr||
nop||
nop||
nop||

#2 8
nop||
nop||
nop||
nop||

#2 9
nop||
nop||
nop||
nop||

#2 10
nop||
nop||
nop||
nop||

#2 11
nop||
nop||
nop||
nop||

#2 12
nop||
nop||
nop||
nop||

#2 13
nop||
nop||
nop||
nop||

#2 14
nop||
nop||
nop||
nop||

#2 15
nop||
nop||
nop||
nop||

#3 0
jmp epwm1_isr||
nop||
nop||
nop||

#3 1
jmp epwm2_isr||
nop||
nop||
nop||

#3 2
jmp epwm3_isr||
nop||
nop||
nop||

#3 3
jmp epwm4_isr||
nop||
nop||
nop||

#3 4
jmp epwm5_isr||
nop||
nop||
nop||

#3 5
jmp epwm6_isr||
nop||
nop||
nop||

#3 6
jmp epwm7_isr||
nop||
nop||
nop||

#3 7
jmp epwm8_isr||
nop||
nop||
nop||

#3 8
nop||
nop||
nop||
nop||

#3 9
nop||
nop||
nop||
nop||

#3 10
nop||
nop||
nop||
nop||

#3 11
nop||
nop||
nop||
nop||

#3 12
nop||
nop||
nop||
nop||

#3 13
nop||
nop||
nop||
nop||

#3 14
nop||
nop||
nop||
nop||

#3 15
nop||
nop||
nop||
nop||

#nc 0 reset
jmp _dsp_core0_start||
nop||
nop||
nop||

#nc 1
nop||
nop||
nop||
nop||

#nc 2
nop||
nop||
nop||
nop||

#nc 3
nop||
nop||
nop||
nop||

#nc 4
nop||
nop||
nop||
nop||

#nc 5
nop||
nop||
nop||
nop||

#nc 6
nop||
nop||
nop||
nop||

#nc 7
nop||
nop||
nop||
nop||

#nc 8
nop||
nop||
nop||
nop||

#nc 9
nop||
nop||
nop||
nop||

#nc 10
nop||
nop||
nop||
nop||

#nc 11
nop||
nop||
nop||
nop||

#nc 12
nop||
nop||
nop||
nop||

#nc 13
nop||
nop||
nop||
nop||

#nc 14
nop||
nop||
nop||
nop||

#nc 15
nop||
nop||
nop||
nop||

#4 0
jmp ecap1_isr||
nop||
nop||
nop||

#4 1
jmp ecap2_isr||
nop||
nop||
nop||

#4 2
jmp ecap3_isr||
nop||
nop||
nop||

#4 3
jmp ecap4_isr||
nop||
nop||
nop||

#4 4
jmp ecap5_isr||
nop||
nop||
nop||

#4 5
jmp ecap6_isr||
nop||
nop||
nop||

#4 6
jmp ecap7_isr||
nop||
nop||
nop||

#4 7
nop||
nop||
nop||
nop||

#4 8
nop||
nop||
nop||
nop||

#4 9
nop||
nop||
nop||
nop||

#4 10
nop||
nop||
nop||
nop||

#4 11
nop||
nop||
nop||
nop||

#4 12
nop||
nop||
nop||
nop||

#4 13
jmp ecap6_hrcal_isr||
nop||
nop||
nop||

#4 14
jmp ecap7_hrcal_isr||
nop||
nop||
nop||

#4 15
nop||
nop||
nop||
nop||

#5 0
jmp eqep1_isr||
nop||
nop||
nop||

#5 1
jmp eqep2_isr||
nop||
nop||
nop||

#5 2
nop||
nop||
nop||
nop||

#5 3
nop||
nop||
nop||
nop||

#5 4
nop||
nop||
nop||
nop||

#5 5
nop||
nop||
nop||
nop||

#5 6
nop||
nop||
nop||
nop||

#5 7
nop||
nop||
nop||
nop||

#5 8
jmp sdfm1_isr||
nop||
nop||
nop||

#5 9
nop||
nop||
nop||
nop||

#5 10
nop||
nop||
nop||
nop||

#5 11
nop||
nop||
nop||
nop||

#5 12
jmp sdfm1dr1_isr||
nop||
nop||
nop||

#5 13
jmp sdfm1dr2_isr||
nop||
nop||
nop||

#5 14
jmp sdfm1dr3_isr||
nop||
nop||
nop||

#5 15
jmp sdfm1dr4_isr||
nop||
nop||
nop||

#6 0
jmp spia_m_isr||
nop||
nop||
nop||

#6 1
jmp spia_s_isr||
nop||
nop||
nop||

#6 2
jmp spib_m_isr||
nop||
nop||
nop||

#6 3
jmp spib_s_isr||
nop||
nop||
nop||

#6 4
nop||
nop||
nop||
nop||

#6 5
nop||
nop||
nop||
nop||

#6 6
nop||
nop||
nop||
nop||

#6 7
nop||
nop||
nop||
nop||

#6 8
nop||
nop||
nop||
nop||

#6 9
nop||
nop||
nop||
nop||

#6 10
nop||
nop||
nop||
nop||

#6 11
nop||
nop||
nop||
nop||

#6 12
nop||
nop||
nop||
nop||

#6 13
nop||
nop||
nop||
nop||

#6 14
nop||
nop||
nop||
nop||

#6 15
nop||
nop||
nop||
nop||

#7 0
jmp dma_ch1_isr||
nop||
nop||
nop||

#7 1
jmp dma_ch2_isr||
nop||
nop||
nop||

#7 2
jmp dma_ch3_isr||
nop||
nop||
nop||

#7 3
jmp dma_ch4_isr||
nop||
nop||
nop||

#7 4
jmp dma_ch5_isr||
nop||
nop||
nop||

#7 5
jmp dma_ch6_isr||
nop||
nop||
nop||

#7 6
nop||
nop||
nop||
nop||

#7 7
nop||
nop||
nop||
nop||

#7 8
nop||
nop||
nop||
nop||

#7 9
nop||
nop||
nop||
nop||

#7 10
jmp fsitx_int1_isr||
nop||
nop||
nop||

#7 11
jmp fsitx_int2_isr||
nop||
nop||
nop||

#7 12
jmp fsirx_int1_isr||
nop||
nop||
nop||

#7 13
jmp fsirx_int2_isr||
nop||
nop||
nop||

#7 14
nop||
nop||
nop||
nop||

#7 15
jmp dcc_isr||
nop||
nop||
nop||

#8 0
jmp i2ca_isr||
nop||
nop||
nop||

#8 1
nop||
nop||
nop||
nop||

#8 2
nop||
nop||
nop||
nop||

#8 3
nop||
nop||
nop||
nop||

#8 4
nop||
nop||
nop||
nop||

#8 5
nop||
nop||
nop||
nop||

#8 6
nop||
nop||
nop||
nop||

#8 7
nop||
nop||
nop||
nop||

#8 8
jmp lina_isr||
nop||
nop||
nop||

#8 9
nop||
nop||
nop||
nop||

#8 10
nop||
nop||
nop||
nop||

#8 11
nop||
nop||
nop||
nop||

#8 12
jmp pmbus_isr||
nop||
nop||
nop||

#8 13
nop||
nop||
nop||
nop||

#8 14
nop||
nop||
nop||
nop||

#8 15
nop||
nop||
nop||
nop||

#9 0
jmp scia_isr||
nop||
nop||
nop||

#9 1
jmp scib_isr||
nop||
nop||
nop||

#9 2
nop||
nop||
nop||
nop||

#9 3
nop||
nop||
nop||
nop||

#9 4
jmp cana_isr||
nop||
nop||
nop||

#9 5
jmp canb_isr||
nop||
nop||
nop||

#9 6
nop||
nop||
nop||
nop||

#9 7
nop||
nop||
nop||
nop||

#9 8
nop||
nop||
nop||
nop||

#9 9
nop||
nop||
nop||
nop||

#9 10
nop||
nop||
nop||
nop||

#9 11
nop||
nop||
nop||
nop||

#9 12
nop||
nop||
nop||
nop||

#9 13
nop||
nop||
nop||
nop||

#9 14
nop||
nop||
nop||
nop||

#9 15
nop||
nop||
nop||
nop||

#10 0
jmp adca_evt_isr||
nop||
nop||
nop||

#10 1
jmp adca2_isr||
nop||
nop||
nop||

#10 2
jmp adca3_isr||
nop||
nop||
nop||

#10 3
jmp adca4_isr||
nop||
nop||
nop||

#10 4
jmp adcb_evt_isr||
nop||
nop||
nop||

#10 5
jmp adcb2_isr||
nop||
nop||
nop||

#10 6
jmp adcb3_isr||
nop||
nop||
nop||

#10 7
jmp adcb4_isr||
nop||
nop||
nop||

#10 8
jmp adcc_evt_isr||
nop||
nop||
nop||

#10 9
jmp adcc2_isr||
nop||
nop||
nop||

#10 10
jmp adcc3_isr||
nop||
nop||
nop||

#10 11
jmp adcc4_isr||
nop||
nop||
nop||

#10 12
nop||
nop||
nop||
nop||

#10 13
nop||
nop||
nop||
nop||

#10 14
nop||
nop||
nop||
nop||

#10 15
nop||
nop||
nop||
nop||

#11 0
jmp ipc_0_isr||
nop||
nop||
nop||

#11 1
jmp ipc_1_isr||
nop||
nop||
nop||

#11 2
jmp ipc_2_isr||
nop||
nop||
nop||

#11 3
jmp ipc_3_isr||
nop||
nop||
nop||

#11 4
nop||
nop||
nop||
nop||

#11 5
nop||
nop||
nop||
nop||

#11 6
nop||
nop||
nop||
nop||

#11 7
nop||
nop||
nop||
nop||

#11 8
nop||
nop||
nop||
nop||

#11 9
nop||
nop||
nop||
nop||

#11 10
nop||
nop||
nop||
nop||

#11 11
nop||
nop||
nop||
nop||

#11 12
nop||
nop||
nop||
nop||

#11 13
nop||
nop||
nop||
nop||

#11 14
nop||
nop||
nop||
nop||

#11 15
nop||
nop||
nop||
nop||

#12 0
jmp xint3_isr||
nop||
nop||
nop||

#12 1
jmp xint4_isr||
nop||
nop||
nop||

#12 2
jmp xint5_isr||
nop||
nop||
nop||

#12 3
nop||
nop||
nop||
nop||

#12 4
nop||
nop||
nop||
nop||

#12 5
nop||
nop||
nop||
nop||

#12 6
nop||
nop||
nop||
nop||

#12 7
nop||
nop||
nop||
nop||

#12 8
nop||
nop||
nop||
nop||

#12 9
nop||
nop||
nop||
nop||

#12 10
nop||
nop||
nop||
nop||

#12 11
nop||
nop||
nop||
nop||

#12 12
nop||
nop||
nop||
nop||

#12 13
nop||
nop||
nop||
nop||

#12 14
nop||
nop||
nop||
nop||

#12 15
nop||
nop||
nop||
nop||

#13
jmp timer1_isr||
nop||
nop||
nop||

#14
jmp timer2_isr||
nop||
nop||
nop||

#15
jmp nmi_isr||
nop||
nop||
nop||

_dsp_core0_start:
movigl GR30 0x0000||
movigh GR30 0x0004||
call system_init||
nop||
nop||

myloop:
nop|nop|nop
jmp myloop||
nop|nop|nop
nop|nop|nop

