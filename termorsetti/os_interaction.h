#include <Bridge.h>
#include <Process.h>

#ifndef _LIB_OS_INTERACTION
#define _LIB_OS_INTERACTION

#define FILE_WRITE_DELAY (2000)

const String fileDestinations[4]={"t0","t1","t2","h0"}; // on the filesystem
// namely: far temp, near temp, digital temp, digital humidity

const String shellEntryWriter="/root/orsetti/log.sh";
const String shellDateUpdater="/root/orsetti/dater.sh";
// arguments: <value> <filename>

#endif
