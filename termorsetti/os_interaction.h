#include <Bridge.h>
#include <Process.h>

#ifndef _LIB_OS_INTERACTION
#define _LIB_OS_INTERACTION

const String fileDestinations[5]={"t0","t1","t2","h0","hi"}; // on the filesystem
// namely: far temp, near temp, digital temp, digital humidity

const String shellEntryWriter="/root/orsetti/log.sh";
// arguments: <value> <filename>

#endif
