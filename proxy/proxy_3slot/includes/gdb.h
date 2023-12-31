/*$$HEADER*/
/******************************************************************************/
/*                                                                            */
/*                    H E A D E R   I N F O R M A T I O N                     */
/*                                                                            */
/******************************************************************************/

// Project Name                   : OpenRISC Debug Proxy
// File Name                      : gdb.h
// Prepared By                    : jb, rmd
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
// 081101		First revision, adapted from existing "jp" 
//                      debug proxy.                               jb, rmd

#ifndef GDB_H
#define GDB_H

#include <sys/types.h>
#include <inttypes.h>

extern void HandleServerSocket(void);
//void handle_rsp ();
int GetServerSocket(const char* name, const char* proto, int port);
extern void JTAGRequest(void);
void setup_or32(void);
void gdb_close();
uint32_t reversebytes_uint32t(uint32_t value);
extern int err;

extern int kernel_debug;

/* All JTAG chains.  */
enum jtag_chains
  {
    SC_GLOBAL,      /* 0 Global BS Chain */
    SC_RISC_DEBUG,  /* 1 RISC Debug Interface chain */
    SC_RISC_TEST,   /* 2 RISC Test Chain */
    SC_TRACE,       /* 3 Trace Chain */
    SC_REGISTER,    /* 4 Register Chain */
    SC_WISHBONE,    /* 5 Memory chain */
    SC_BLOCK,       /* 6 Block Chains */
  };

/* See JTAG documentation about these.  */
#define JI_SIZE (4)
enum jtag_instr
  {
    JI_EXTEST,
    JI_SAMPLE_PRELOAD,
    JI_IDCODE,
    JI_CHAIN_SELECT,
    JI_INTEST,
    JI_CLAMP,
    JI_CLAMPZ,
    JI_HIGHZ,
    JI_DEBUG,
    JI_BYPASS = 0xF
  };

/* JTAG registers.  */
#define JTAG_MODER  (0x0)
#define JTAG_TSEL   (0x1)
#define JTAG_QSEL   (0x2)
#define JTAG_SSEL   (0x3)
#define JTAG_RISCOP (0x4)
#define JTAG_RECWP0 (0x10)
#define JTAG_RECBP0 (0x1b)

/* This is repeated from gdb tm-or1k.h There needs to be
   a better mechanism for tracking this, but I don't see
   an easy way to share files between modules. */
typedef enum {
  JTAG_COMMAND_READ = 1,
  JTAG_COMMAND_WRITE = 2,
  JTAG_COMMAND_BLOCK_READ = 3,
  JTAG_COMMAND_BLOCK_WRITE = 4,
  JTAG_COMMAND_CHAIN = 5,
} JTAG_proxy_protocol_commands;

/* Each transmit structure must begin with an integer
   which specifies the type of command. Information
   after this is variable. Make sure to have all information
   aligned properly. If we stick with 32 bit integers, it
   should be portable onto every platform. These structures
   will be transmitted across the network in network byte
   order.
*/
typedef struct {
  uint32_t command;
  uint32_t length;
  uint32_t address;
  uint32_t data_H;
  uint32_t data_L;
} JTAGProxyWriteMessage;

typedef struct {
  uint32_t command;
  uint32_t length;
  uint32_t address;
} JTAGProxyReadMessage;

typedef struct {
  uint32_t command;
  uint32_t length;
  uint32_t address;
  int32_t  nRegisters;
  uint32_t data[1];
} JTAGProxyBlockWriteMessage;

typedef struct {
  uint32_t command;
  uint32_t length;
  uint32_t address;
  int32_t  nRegisters;
} JTAGProxyBlockReadMessage;

typedef struct {
  uint32_t command;
  uint32_t length;
  uint32_t chain;
} JTAGProxyChainMessage;

/* The responses are messages specific, however convention
   states the first word should be an error code. Again,
   sticking with 32 bit integers should provide maximum
   portability. */

typedef struct {
  int32_t status;
} JTAGProxyWriteResponse;

typedef struct {
  int32_t status;
  uint32_t data_H;
  uint32_t data_L;
} JTAGProxyReadResponse;
  
typedef struct {
  int32_t status;
} JTAGProxyBlockWriteResponse;

typedef struct {
  int32_t status;
  int32_t nRegisters;
  uint32_t data[1];
  /* uint32_t data[nRegisters-1] still unread */
} JTAGProxyBlockReadResponse;

typedef struct {
  int32_t status;
} JTAGProxyChainResponse;


#define open1_func_code			1
#define open2_func_code			2
#define close_func_code			3
#define read_func_code			4
#define write_func_code			5
#define lseek_func_code			6
#define rename_func_code		7
#define unlink_func_code		8
#define stat_func_code			9
#define fstat_func_code			10
#define gettime_func_code		11
#define isatty_func_code		12
#define system_func_code		13

// #define S_IFREG        0100000
// #define S_IFDIR         040000
// #define S_IFCHR         020000
// #define S_IRUSR           0400
// #define S_IWUSR           0200
// #define S_IXUSR           0100
// #define S_IRWXU           0700
// #define S_IRGRP            040
// #define S_IWGRP            020
// #define S_IXGRP            010
// #define S_IRWXG            070
// #define S_IROTH             04
// #define S_IWOTH             02
// #define S_IXOTH             01
// #define S_IRWXO             07
#define bytes_per_word       4

#endif /* GDB_H */
