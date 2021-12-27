// lptest.cpp : Parallel port access using giveio.sys


// See https://studenti.fisica.unifi.it/~carla/manuali/porta_parallela/porta_parallela.html
// JTAG: https://github.com/openocd-org/openocd/blob/master/src/jtag/drivers/parPort.c 
// https://sourceforge.net/projects/jtagomat/  Tools\JTAG\jtagomat-1.2.5\src

const int parPort = 0x378; // LPT1


#include <Windows.h>
#include <stdio.h>

#include <intrin.h>

static inline unsigned char inb(unsigned short port) { return __inbyte(port); }
static inline void outb(unsigned char value, unsigned short port) { __outbyte(port, value); }

static inline unsigned short inw(unsigned short port) { return __inword(port); }
static inline void outw(unsigned short value, unsigned short port) { __outword(port, value); }

static inline unsigned int indw(unsigned short port) { return __indword(port); }
static inline void outdw(unsigned int value, unsigned short port) { __outdword(port, value); }

// list all inputs/outputs
// bit numbers in int32 combined registers

// SPP



// EPP
// ECP


// TODO: autoconfig JTAG connection?
//   vs. inputs/outputs need to be correct 
//     better programmable direction by pin using an MCU
// 
// search for TDO response to TDI and TCKs
// count combinations of inversions, ...
//    binary search by toggling half of bits first, then quarter, ...
//    ?any danger to TRST?
// IRLen typ. 5


int main() {
  HANDLE h = CreateFile("\\\\.\\giveio", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if (h == INVALID_HANDLE_VALUE) {
    printf("Run as Admin:  /Tools/TAG/givieo.bat to grant access\n");
    system("sc create giveio type = kernel binpath = C:/Users/Admin/Desktop/Tools/JTAG/giveio.sys");
    system("sc start giveio");
    exit(-1);
  }
  CloseHandle(h);

  for (int i = 1; i <= 3; ++i) {
    outb(i, parPort);
    Sleep(500);
  }

#if 0
  outb(1, parPort + 2);  // strobe is inverted

  outb(1, parPort);  // D0 high
  Sleep(500);
  outb(0, parPort);

  Sleep(500);
  outb(0, parPort + 2);  // strobe is inverted

  outdw(0x10001, parPort);
  Sleep(500);
  outdw(0, parPort);
  Sleep(500);
  outdw(0x10000, parPort);

  // 3.4V open circuit
#endif
    
  return 0;
}

