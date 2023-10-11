/*$$HEADER*/
/******************************************************************************/
/*                                                                            */
/*                    H E A D E R   I N F O R M A T I O N                     */
/*                                                                            */
/******************************************************************************/

// Project Name                   : OpenRISC Debug Proxy
// File Name                      : or_debug_proxy.h
// Prepared By                    : jb
// Project Start                  : 2008-10-01

/*$$COPYRIGHT NOTICE*/
/******************************************************************************/
/*                                                                            */
/*                      C O P Y R I G H T   N O T I C E                       */
/*                                                                            */
/******************************************************************************/
/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation;
  version 2.1 of the License, a copy of which is available from
  http://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*$$CHANGE HISTORY*/
/******************************************************************************/
/*                                                                            */
/*                         C H A N G E  H I S T O R Y                         */
/*                                                                            */
/******************************************************************************/

// Date		Version	Description
//------------------------------------------------------------------------
// 081101		First revision           			jb

#ifndef _OR_DEBUG_PROXY_H_
#define _OR_DEBUG_PROXY_H_

#ifndef DEBUG_CMDS
#define DEBUG_CMDS 0  // Output the actual commands being sent to the debug unit
#endif

#ifndef DEBUG_USB_DRVR_FUNCS
#define DEBUG_USB_DRVR_FUNCS 0 // Generate debug output from the USB driver functions
#endif

#ifndef DEBUG_GDB_BLOCK_DATA
#define DEBUG_GDB_BLOCK_DATA 0  // GDB Socket Block data print out
#endif

// This one is defined sometimes in the makefile, so check first
#ifndef DEBUG_GDB
#define DEBUG_GDB 1 // GDB RSP Debugging output enabled
#endif

#ifndef DEBUG_GDB_DUMP_DATA
#define DEBUG_GDB_DUMP_DATA 0  // GDB Socket Debugging - output all data we return to GDB client
#endif

/* debug mode */
typedef enum {
  NON_STOP_MODE = 0,
  STOP_MODE = 1
} ProxyDebugModeType;
extern ProxyDebugModeType g_option_debug_mode;

/* Option controlling whether to print various DSP internel PC when received a GDB packet
 * 0 (default) - not to show PC
 * 1           - show PC
 */
extern int g_option_show_pc;

#define Boolean uint32_t
#define false 0
#define true 1

/* Selects crc trailer size in bits. Currently supported: 8 */
#define CRC_SIZE (8)

#include <stdint.h>

extern int serverPort;
extern int server_fd;

extern int vpi_fd; // should be the descriptor for our connection to the VPI server

extern int current_chain;
extern int dbg_chain;

extern int no_cpu; /* Don't provide access to anything in the cpu */

#define DBGCHAIN_SIZE           4 // Renamed from DC_SIZE due to definition clash with something in <windows.h> --jb 090302
#define DC_STATUS_SIZE    4

#define DC_WISHBONE       0
#define DC_CPU0           1
#define DC_CPU1           2

// Defining access types for wishbone
#define DBG_WB_WRITE8           0
#define DBG_WB_WRITE16          1
#define DBG_WB_WRITE32          2
#define DBG_WB_READ8            4
#define DBG_WB_READ16           5
#define DBG_WB_READ32           6

// Defining access types for wishbone
#define DBG_CPU_WRITE            2
#define DBG_CPU_READ             6

// Manually figure the 5-bit reversed values again if they change
#define DI_GO          0
#define DI_READ_CMD    1
#define DI_WRITE_CMD   2
#define DI_READ_CTRL   3
#define DI_WRITE_CTRL  4

#define DBG_CRC_SIZE      32
#define DBG_CRC_POLY      0x04c11db7

#define DBG_ERR_OK        0
#define DBG_ERR_INVALID_ENDPOINT 3
#define DBG_ERR_CRC       8

#define NUM_SOFT_RETRIES  3
#define NUM_HARD_RETRIES  3
#define NUM_ACCESS_RETRIES 10

#include <semaphore.h>

/*by qwt 为了解决双核调试两个线程的全局变量问题，把所有全局变量调整到这里封装到一个struct里面，
然后把这个struct作为参数传给两个线程的入口函数并且修改所有涉及到全局变量的函数的调用链保证这个包含
全局变量的struct能一直调用下去*/
//gdb.c的结构体和枚举前置声明在这里
enum mp_type {
  BP_MEMORY = 0,		// software-breakpoint Z0  break 
  BP_HARDWARE = 1,	// hardware-breakpoint Z1  hbreak 
  WP_WRITE = 2,		// write-watchpoint    Z2  watch  
  WP_READ = 3,		// read-watchpoint     Z3  rwatch  
  WP_ACCESS = 4		// access-watchpoint   Z4  awatch
};

struct mp_entry {
  enum mp_type type;	/*!< Type of matchpoint */
  uint32_t addr;		/*!< Address with the matchpoint */
  uint32_t instr;		/*!< Substituted instruction */
  struct mp_entry* next;	/*!< Next entry with this hash */
};

enum stallStates {
    STALLED,
    UNSTALLED,
    UNKNOWN
};

struct global_rsp {
  int cpu_no;
  int client_waiting;	/*!< Is client waiting a response? */
  // Not used  int                proto_num;            /*!< Number of the protocol used */
  int client_fd;		/*!< FD for talking to GDB */
  int sigval;		/*!< GDB signal for any exception */
  uint32_t start_addr;	/*!< Start of last run */
  uint32_t trap_imm;
  struct mp_entry* mp_hash[1021];	/*!< Matchpoint hash table */
  //or_debug_proxy.c
  int current_chain;//这个好像就应该是只有一个的，因为两个线程的current应该只有一个current
  int dbg_chain;//这个每次用的时候会先赋值，应该也不用分两个
  //int err;  这玩意如果生效了就说明出错了啊，就当他两个都停了吧，不用双线程了，祈祷别出问题吧，这个改起来可太爆炸了
  //win_usb_driver
  // Global USB JTAG device handle
  //FTC_HANDLE ftHandle;   这玩意不用双线程各一个，一定是公用的
  //usb_functions.c
  unsigned long dwNumBytesReturned;//看起来没经过赋值，不确定是否要一个线程一个
  uint32_t id_read_at_reset;//只在这里usb_dbg_reset赋值，没有双线程
  //int retry_no = 0;看起来不用分两个线程，每次retry成功都会置0
  //uint32_t retries; 每次调用都会初始化0，也不用分两个线程
  //static uint32_t reg_adr = 0;每次需要用到的时候一定会先传给他一个值，没有使用上个周期值的时候，因此也不用分。
  //win_usb_driver与linux_usb_driver这两部分的代码不会涉及到双线程的控制问题，应该也不用放在这里
  //vpi_functions似乎是Verilog仿真时候的接口
  //gdb.c  这个是最爆炸的，大量全局变量都在这里面。。。。
  enum stallStates stallState;
  int npcIsCached;		//!< Is the NPC cached - should be bool
  uint32_t npcCachedValue;	//!< Cached value of the NPC
  int serverPort;
  //int server_fd;//default 0这个好像没用上
  //int gdb_fd = 0;  这东西没用上好像是没有修改值的函数
  int gdb_chain;//default -1  待解决  这东西好像每次用之前都会set一下，理论上应该不用一个线程一个

  int current_stat;//0--origin 1--s 2--c
  //int current_filefunc = 0;//这东西的调用好像每次调都会先初始化为一个值，应该一个就够用了
  //int traping=0;貌似没用上
};

/* setup connection with the target */
void dbg_test();
/* perform a reset of the debug chain (not of system!) */
int dbg_reset();
/* set instruction register of JTAG TAP */
int dbg_set_tap_ir(uint32_t ir);
/* Set "scan chain" of debug unit (NOT JTAG TAP!) */
int dbg_set_chain(uint32_t chain);
/* read a byte from wishbone */
int dbg_wb_write8(uint32_t adr, uint8_t data);
/* read a byte from wishbone */
int dbg_wb_read8(uint32_t adr, uint8_t* data);
/* read a word from wishbone */
int dbg_wb_read32(uint32_t adr, uint32_t* data);
/* write a word to wishbone */
int dbg_wb_write32(uint32_t adr, uint32_t data);
/* read a block from wishbone */
int dbg_wb_read_block32(uint32_t adr, uint32_t* data, uint32_t len);
/* write a block to wishbone */
int dbg_wb_write_block32(uint32_t adr, uint32_t* data, uint32_t len);
/* read a register from cpu */
int dbg_cpu0_read(uint32_t adr, uint32_t* data, uint32_t length);
/* read a register from cpu module */
int dbg_cpu0_read_ctrl(uint32_t adr, unsigned char* data);
/* write a cpu register */
int dbg_cpu0_write(uint32_t adr, uint32_t* data, uint32_t length);
/* write a cpu module register */
int dbg_cpu0_write_ctrl(uint32_t adr, unsigned char data);

void print_usage(); // Self explanatory

void check(char* fn, uint32_t l, uint32_t i);

/* Possible errors are listed here.  */
enum enum_errors  /* modified <chris@asics.ws> CZ 24/05/01 */
{
  /* Codes > 0 are for system errors */

  ERR_NONE = 0,
  ERR_CRC = -1,
  ERR_MEM = -2,
  JTAG_PROXY_INVALID_COMMAND = -3,
  JTAG_PROXY_SERVER_TERMINATED = -4,
  JTAG_PROXY_NO_CONNECTION = -5,
  JTAG_PROXY_PROTOCOL_ERROR = -6,
  JTAG_PROXY_COMMAND_NOT_IMPLEMENTED = -7,
  JTAG_PROXY_INVALID_CHAIN = -8,
  JTAG_PROXY_INVALID_ADDRESS = -9,
  JTAG_PROXY_ACCESS_EXCEPTION = -10, /* Write to ROM */
  JTAG_PROXY_INVALID_LENGTH = -11,
  JTAG_PROXY_OUT_OF_MEMORY = -12,
};

#endif /* _OR_DEBUG_PROXY_H_ */

