#include <sys/stat.h>
#include "crash.h"
#include "parse.h"
#include "userfs.h"
#include <stdbool.h>

/* GLOBAL  VARIABLES */
int virtual_disk;
char nullblock[4096] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
/*Use these variable as a staging space before they get writen out to disk*/
superblock sb;
BIT bit_map[BIT_MAP_SIZE];
dir_struct dir;
inode curr_inode;
char buffer[BLOCK_SIZE_BYTES]; /* assert( sizeof(char) ==1)); */

/*
  man 2 read
  man stat
  man memcopy
*/

void usage (char * command) {
	fprintf(stderr, "Usage: %s -reformat disk_size_bytes file_name\n", command);
	fprintf(stderr, "        %s file_ame\n", command);
}

char * buildPrompt() {
	return  "%";
}


int main(int argc, char** argv) {
	char * cmd_line;
	/* info stores all the information returned by parser */
	parseInfo *info;
	/* stores cmd name and arg list for one command */
	struct commandType *cmd;

	init_crasher();

	if ((argc == 4) && (argv[1][1] == 'r')) {
		/* ./userfs -reformat diskSize fileName */
		if (!u_format(atoi(argv[2]), argv[3])) {
			fprintf(stderr, "Unable to reformat\n");
			exit(-1);
		}
	} else if (argc == 2) {
		/* ./userfs fileName will attempt to recover a file. */
		if ((!recover_file_system(argv[1]))) {
			fprintf(stderr, "Unable to recover virtual file system from file: %s\n", argv[1]);
			exit(-1);
		}
	} else {
		usage(argv[0]);
		exit(-1);
	}

	/* before begin processing set clean_shutdown to FALSE */
	sb.clean_shutdown = 0;
	lseek(virtual_disk, BLOCK_SIZE_BYTES*SUPERBLOCK_BLOCK, SEEK_SET);
	crash_write(virtual_disk, &sb, sizeof(superblock));
	sync();
	fprintf(stderr, "userfs available\n");

	while(1) {
		cmd_line = readline(buildPrompt());
		if (cmd_line == NULL) {
			fprintf(stderr, "Unable to read command\n");
			continue;
		}

		/* calls the parser */
		info = parse(cmd_line);
		if (info == NULL) {
			free(cmd_line);
			continue;
		}

		/* com contains the info. of command before the first "|" */
		cmd = &info->CommArray[0];
		if ((cmd == NULL) || (cmd->command == NULL)) {
			free_info(info);
			free(cmd_line);
			continue;
		}

		/************************   u_import ****************************/
		if (strncmp(cmd->command, "u_import", strlen("u_import")) == 0){
			if (cmd->VarNum != 3){
				fprintf(stderr, "u_import externalFileName userfsFileName\n");
			} else {
				if (!u_import(cmd->VarList[1], cmd->VarList[2])) {
					fprintf(stderr, "Unable to import external file %s into userfs file %s\n", cmd->VarList[1], cmd->VarList[2]);
				}
			}


		/************************   u_export ****************************/
		} else if (strncmp(cmd->command, "u_export", strlen("u_export")) == 0){
			if (cmd->VarNum != 3){
				fprintf(stderr, "u_export userfsFileName externalFileName \n");
			} else {
				if (!u_export(cmd->VarList[1], cmd->VarList[2])) {
					fprintf(stderr, "Unable to export userfs file %s to external file %s\n", cmd->VarList[1], cmd->VarList[2]);
				}
			}


		/************************   u_del ****************************/
		} else if (strncmp(cmd->command, "u_del", strlen("u_del")) == 0) {
			if (cmd->VarNum != 2){
				fprintf(stderr, "u_del userfsFileName \n");
			} else {
				if (!u_del(cmd->VarList[1]) ){
					fprintf(stderr, "Unable to delete userfs file %s\n", cmd->VarList[1]);
				}
			}


		/******************** u_ls **********************/
		} else if (strncmp(cmd->command, "u_ls", strlen("u_ls")) == 0) {
			u_ls();


		/********************* u_quota *****************/
		} else if (strncmp(cmd->command, "u_quota", strlen("u_quota")) == 0) {
			int free_blocks = u_quota();
			fprintf(stderr, "Free space: %d bytes %d blocks\n", free_blocks * BLOCK_SIZE_BYTES, free_blocks);


		/***************** exit ************************/
		} else if (strncmp(cmd->command, "exit", strlen("exit")) == 0) {
			/* 
			 * take care of clean shut down so that u_fs
			 * recovers when started next.
			 */
			if (!u_clean_shutdown()){
				fprintf(stderr, "Shutdown failure, possible corruption of userfs\n");
			}
			exit(1);


		/****************** other ***********************/
		} else {
			fprintf(stderr, "Unknown command: %s\n", cmd->command);
			fprintf(stderr, "\tTry: u_import, u_export, u_ls, u_del, u_quota, exit\n");
		}


		free_info(info);
		free(cmd_line);
	}
}

/*
 * Initializes the bit map.
 */
void init_bit_map() {
	int i;
	for (i = 0; i < BIT_MAP_SIZE; i++) {
		bit_map[i] = 0;
	}
}

void allocate_block(int blockNum) {
	assert(blockNum < BIT_MAP_SIZE);
	bit_map[blockNum] = 1;
}

void free_block(int blockNum) {
	assert(blockNum < BIT_MAP_SIZE);
	bit_map[blockNum] = 0;
}

int superblockMatchesCode() {
	if (sb.size_of_super_block != sizeof(superblock)){
		return 0;
	}
	if (sb.size_of_directory != sizeof (dir_struct)){
		return 0;
	}
	if (sb.size_of_inode != sizeof(inode)){
		return 0;
	}
	if (sb.block_size_bytes != BLOCK_SIZE_BYTES){
		return 0;
	}
	if (sb.max_file_name_size != MAX_FILE_NAME_SIZE){
		return 0;
	}
	if (sb.max_blocks_per_file != MAX_BLOCKS_PER_FILE){
		return 0;
	}
	return 1;
}

void init_superblock(int diskSizeBytes) {
	sb.disk_size_blocks  = diskSizeBytes/BLOCK_SIZE_BYTES;
	sb.num_free_blocks = u_quota();
	sb.clean_shutdown = 1;

	sb.size_of_super_block = sizeof(superblock);
	sb.size_of_directory = sizeof (dir_struct);
	sb.size_of_inode = sizeof(inode);

	sb.block_size_bytes = BLOCK_SIZE_BYTES;
	sb.max_file_name_size = MAX_FILE_NAME_SIZE;
	sb.max_blocks_per_file = MAX_BLOCKS_PER_FILE;
}

int compute_inode_loc(int inode_number) {
	int whichInodeBlock;
	int whichInodeInBlock;
	int inodeLocation;

	whichInodeBlock = inode_number/INODES_PER_BLOCK;
	whichInodeInBlock = inode_number%INODES_PER_BLOCK;

	inodeLocation = (INODE_BLOCK + whichInodeBlock) *BLOCK_SIZE_BYTES +
		whichInodeInBlock*sizeof(inode);

	return inodeLocation;
}

int write_inode(int inode_number, inode * in) {
	int inodeLocation;
	assert(inode_number < MAX_INODES);

	inodeLocation = compute_inode_loc(inode_number);

	lseek(virtual_disk, inodeLocation, SEEK_SET);
	crash_write(virtual_disk, in, sizeof(inode));

	sync();

	return 1;
}


int read_inode(int inode_number, inode * in) {
	int inodeLocation;
	assert(inode_number < MAX_INODES);

	inodeLocation = compute_inode_loc(inode_number);

	lseek(virtual_disk, inodeLocation, SEEK_SET);
	read(virtual_disk, in, sizeof(inode));

	return 1;
}


/*
 * Initializes the directory.
 */
void init_dir() {
	int i;
	for (i = 0; i< MAX_FILES_PER_DIRECTORY; i++) {
		dir.u_file[i].free = 1;
		dir.u_file[i].inode_number = -1; //free files have inode num of -1
	}

}


/*
 * Returns the number of free blocks in the file system.
 */
int u_quota() {
	int freeCount=0;

	/* It might be advantageous to return sb.num_free_blocks if you keep it up to
	   date, which is up to you to do. Do keep in mind when that number might be
	   invalid and thus requires the following. */

	// Calculate the number of free blocks
	int i;
	for (i = 0; i < sb.disk_size_blocks; i++) {
		/* Right now we are using a full unsigned int
		   to represent each bit - we really should use
		   all the bits in there for more efficient storage */
		if (bit_map[i] == 0) {
			freeCount++;
		}
	}
	return freeCount;
}

//find size of file helper function
int sizeOfFile(const char *fname) {
	struct stat st;

	stat(fname, &st);
	return (st.st_size);
}

//check if file exists helper function
bool fileExists(const char *fname) {
	struct stat st;

	int exist = stat(fname, &st);
	return exist == 0;//if exist equals 0 then file exists, 
}

/*
 * Imports a linux file into the u_fs
 * Need to take care in the order of modifying the data structures 
 * so that it can be revored consistently.
 *
 * Returns 1 on success, 0 on failure.
 *
 * TODO: Implement the rest of this function.
 */
int u_import(char* linux_file, char* u_file) {
	int free_space;
	free_space = u_quota();

	//above max file size
	int size = sizeOfFile(linux_file);
	if(size >  BLOCK_SIZE_BYTES * MAX_BLOCKS_PER_FILE) {
		fprintf(stderr, "Unable to import, file above max size\n");
		return 0;
	}

	//not enough space
	if(size >  (free_space * BLOCK_SIZE_BYTES)) {
		fprintf(stderr, "Unable to import, not enough free space\n");
		fprintf(stderr, "size: %d\nspace: %d\n", size, free_space * BLOCK_SIZE_BYTES);
		return 0;
	}

	//find spot in dir
	int i = 0;
	while ((i< MAX_FILES_PER_DIRECTORY) && !(dir.u_file[i].free)) {
		i++;
	}

	if(i ==  MAX_FILES_PER_DIRECTORY) {
		fprintf(stderr, "Unable to import, no space in directory\n");
		return 0;
	}
	int fnum= i;
	


	//find an inode
	for(i = 0; i < MAX_INODES; i++) {
		read_inode(i, &curr_inode);
		if(curr_inode.free) {
			break;
		}
	}
	if(i == MAX_INODES) {
		fprintf(stderr, "Unable to import, no available inodes\n");
		return 0;
	}
	int inodenum = i;
	
	

	int handle = open(linux_file, O_RDONLY);
	if (handle == -1) {
		fprintf(stderr, "error, opening file %s\n", linux_file);
		return 0;
	}
	

	// crashNow(); //tested
	int blocks = 0;
	int readret = read(handle,&buffer,BLOCK_SIZE_BYTES);
	while (readret != 0) {
		
		//find open block
		for(i = 0; i < BIT_MAP_SIZE; i++) {
			if(bit_map[i] == 0) {
				allocate_block(i);
				//update bitmap
				lseek(virtual_disk, BLOCK_SIZE_BYTES*BIT_MAP_BLOCK, SEEK_SET);
				crash_write(virtual_disk, bit_map, sizeof(BIT)*BIT_MAP_SIZE);
				break;
			}
		}
		//seek to block i
		lseek(virtual_disk, BLOCK_SIZE_BYTES*i, SEEK_SET);
		//read a block of file and write to block i
		
		// crashNow(); //tested

		// if(blocks == 3) {//crash 3 blocks into writing
		// 	crashNow(); //tested
		// }
				
		crash_write(virtual_disk, &buffer, readret);
		curr_inode.blocks[blocks] = i;
		blocks++;
		readret = read(handle,&buffer,BLOCK_SIZE_BYTES);
	}

	

	close(handle);
	//fill inode
	curr_inode.free = 0;
	curr_inode.num_blocks = blocks;
	curr_inode.file_size_bytes = size;
	time(&curr_inode.last_modified);
	//printf("updating inode\n");
	// crashNow(); //crash before inode write(tested)
	write_inode(inodenum, &curr_inode);

	//put in directory
	dir.u_file[fnum].free = 0;
	file_struct file;
	file.inode_number = inodenum;
	strcpy(file.file_name, u_file);
	file.free = 0;
	dir.u_file[fnum] = file;
	dir.num_files++;//decrement num files


	//seek to and write write directory
	lseek(virtual_disk, BLOCK_SIZE_BYTES*DIRECTORY_BLOCK, SEEK_SET);
	// crashNow(); //crash before dir write (tested)
	crash_write(virtual_disk, &dir, sizeof(dir_struct));
	
	/* Here are some things to think about as you write this code. This isn't an
	 * exhaustive list nor is this the order of operations you should follow.
	 *
	 * - Is there free space within the metadata allocations (inodes, directory,
	 *   etc) for a new file?
	 * - Is the file data too big to import?
	 * - What order should file system metadata be updated?
	 */

	return 1;
}



/*
 * Exports a u_file to linux.
 * Need to take care in the order of modifying the data structures 
 * so that it can be recovered consistently.
 *
 * Return 1 on success, 0 on failure.
 *
 * TODO: Implement this function.
 */
int u_export(char* u_file, char* linux_file) {
	if(fileExists(linux_file)) {
		printf("File %s already exist\n", linux_file);
		return 1;
	}
	int fnum = 0;
	while(strcmp(dir.u_file[fnum].file_name, u_file) != 0) {
		if(fnum < MAX_FILES_PER_DIRECTORY) {
			fnum++;
		}else {
			fprintf(stderr, "Unable to find file: %s\n", u_file);
			return 0;
		}
	}
	int node = dir.u_file[fnum].inode_number;
	
	int handle = open(linux_file, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if (handle == -1) {
		fprintf(stderr, "error, writing file %s\n", linux_file);
		return 0;
	}
	
	read_inode(node, &curr_inode);

	// crashNow(); //crash before read (tested)
	int numblocks = curr_inode.num_blocks;
	int block;
	for (block = 0; block < numblocks; block++) {
		if(block == numblocks - 1) {
			//last block
			// crashNow(); //crash on last block to simulate crash mid read (tested)
			int bytesleft = curr_inode.file_size_bytes - (block*BLOCK_SIZE_BYTES);
			lseek(virtual_disk, BLOCK_SIZE_BYTES*curr_inode.blocks[block], SEEK_SET);
			int readres = crash_read(virtual_disk, &buffer, bytesleft);
			if(readres == -1) {
				fprintf(stderr, "error, reading file %s\n", u_file);
				return 0;
			}else {
				if(write(handle, buffer, readres) == -1) {
					fprintf(stderr, "error, writing file %s\n", linux_file);
					return 0;
				}
			}
		}else {
			lseek(virtual_disk, BLOCK_SIZE_BYTES*curr_inode.blocks[block], SEEK_SET);
			if(crash_read(virtual_disk, &buffer, BLOCK_SIZE_BYTES) == -1) {
				fprintf(stderr, "error, reading file %s\n", u_file);
				return 0;
			}else {
				if(write(handle, buffer, BLOCK_SIZE_BYTES) == -1) {
					fprintf(stderr, "error, writing file %s\n", linux_file);
					return 0;
				}
			}
		}
	}
	close(handle);
	return 1;
}


/*
 * Deletes the file from u_fs.
 * Keep the order of updates to data structures in mind to ensure consistency.
 *
 * Return 1 on success, 0 on failure.
 *
 * TODO: Implement this function.
 */
int u_del(char* u_file) {
	int fnum = 0;
	while(strcmp(dir.u_file[fnum].file_name, u_file) != 0) {
		if(fnum < MAX_FILES_PER_DIRECTORY) {
			fnum++;
		}else {
			fprintf(stderr, "Unable to find file: %s\n", u_file);
			return 0;
		}
	}
	int node = dir.u_file[fnum].inode_number;

	//remove from directory
	dir.u_file[fnum].free = 1;
	dir.u_file[fnum].inode_number = -1;
	dir.num_files--;//decrement numfiles


	
	read_inode(node, &curr_inode);
	int blocks = curr_inode.num_blocks;
	int i;

	//free blocks in inode
	for (i = 0; i < blocks; i++){
		free_block(curr_inode.blocks[i]);
		
		// crashNow();//crash before erasing data (tested)
		//fill block with null chars to erase data
		lseek(virtual_disk, BLOCK_SIZE_BYTES*curr_inode.blocks[i], SEEK_SET);
		crash_write(virtual_disk, nullblock, BLOCK_SIZE_BYTES);

		// crashNow(); //beteen erasing data and updating bitmap (tested)
		/*
		Erase data first so that if a crash occurs here
		there are no blocks with data that aren't allocated.
		This makes it so blocks filled with nulls will be recovered as orphans and
		can be deleted by the user
		*/

		//update bitmap
		lseek(virtual_disk, BLOCK_SIZE_BYTES*BIT_MAP_BLOCK, SEEK_SET);
		crash_write(virtual_disk, bit_map, sizeof(BIT)*BIT_MAP_SIZE);

		// if (i == 4) {//crash after removing 4 blocks
			//  crashNow(); //tested
		// }

		//erase data from inode (wont change until inode write later on)
		curr_inode.blocks[i] = 0;
	}
	
	// //update bitmap
	// lseek(virtual_disk, BLOCK_SIZE_BYTES*BIT_MAP_BLOCK, SEEK_SET);
	// crash_write(virtual_disk, bit_map, sizeof(BIT)*BIT_MAP_SIZE);

	//free inode
	curr_inode.num_blocks = 0;
	curr_inode.file_size_bytes = 0;
	curr_inode.free = 1;
	time(&curr_inode.last_modified);

	// crashNow(); //before updating inode (tested)

	//write inode
	write_inode(node, &curr_inode);

	// crashNow(); //before updating dir (tested)
	//seek to and write write directory
	lseek(virtual_disk, BLOCK_SIZE_BYTES*DIRECTORY_BLOCK, SEEK_SET);
	crash_write(virtual_disk, &dir, sizeof(dir_struct));

	return 1;
}

/*
 * Checks the file system for consistency.
 * Detects if there are orphaned inodes or blocks, and tries its best
 * to recover these objects.
 *
 * Return 1 on success, 0 on failure.
 *
 * TODO: Implement this function.
 */
int u_fsck() {
	//get free inode to take in orphaned blocks
	inode orphanageINode;
	int orphanageNum;
	for(orphanageNum = 0; orphanageNum < MAX_INODES; orphanageNum++) {
		read_inode(orphanageNum, &orphanageINode);
		if(orphanageINode.free) {
			break;
		}
	}
	int dirspot = 0;
	while ((dirspot< MAX_FILES_PER_DIRECTORY) && !(dir.u_file[dirspot].free)) {
		dirspot++;//Ooen spot in dir
	}
	int i = 0;// will be used for orphaned blocks
	int block;
	for (block = 8; block < BIT_MAP_SIZE; block++) {//go through blocks(start on block 8, don't need to look at metadata blocks)
		//fprintf(stdout, "Looking in block %d\n", block);
		if(bit_map[block]) {//block taken
			int node;
			bool blockFound = false;
			//fprintf(stdout, "Block %d taken\n", block);
			for (node = 0; node < MAX_INODES; node++) {
				read_inode(node, &curr_inode);
				if (!curr_inode.free) {//search for inode with allocated block
					//
					int ibl;
					for(ibl = 0; ibl < curr_inode.num_blocks; ibl++) {
						if(curr_inode.blocks[ibl] == block) {//block has an inode assigned to it
							blockFound = true;
							//fprintf(stdout, "Found inode for block, inode: %d\n", node);
							break;//block iteration
						}
					}
				}
				if (blockFound) {//block has an inode assigned to it
					int fnum;
					bool fileFound = false;
					for (fnum = 0; fnum < MAX_FILES_PER_DIRECTORY; fnum++) {// find file in dir for inode
						if (!dir.u_file[fnum].free) {//non free files
							if (dir.u_file[fnum].inode_number == node) {// found file
								fileFound = true;
								//fprintf(stdout, "Found file for block, file: %d\n", fnum);
								break;// file iteration
							}
						}
					}
					if (!fileFound) {// entry missing in dir
						//fix dir
						fprintf(stderr, "Inconsistency found, missing file in directory\n");
						dir.u_file[dirspot].free = 0;
						file_struct file;
						file.inode_number = node;
						char * fname;
						fprintf(stdout, "Please give file name for recovered file\n");
						fname = readline(buildPrompt());
						strncpy(file.file_name, fname, MAX_FILE_NAME_SIZE);
						file.free = 0;
						dir.u_file[dirspot] = file;
						dir.num_files++;
						lseek(virtual_disk, BLOCK_SIZE_BYTES*DIRECTORY_BLOCK, SEEK_SET);
						crash_write(virtual_disk, &dir, sizeof(dir_struct));
						fprintf(stdout, "File reclaimed\n");
					}
					break;//inode iteration
				}
			}
			if (!blockFound) {//failed to find inode for allocated block
				//fix inode and directory
				fprintf(stderr, "Inconsistency found, missing inode\n");
				if(!orphanageINode.free && i ==0) {//inode is taken and i is still zero means no available inodes
					fprintf(stderr, "No inodes available for orphaned block, deleting block\n");
					free_block(block);
				}else if(dirspot == MAX_FILES_PER_DIRECTORY) {//inode is taken and i is still zero means no available inodes
					fprintf(stderr, "No spots in directory available for orphaned block, deleting block\n");
					free_block(block);
				}else {
					fprintf(stderr, "Applying orphaned block to orphanage inode\n");
					orphanageINode.free = 0;
					orphanageINode.blocks[i] = block;
					i++;
					orphanageINode.num_blocks = i;
					orphanageINode.file_size_bytes = i * BLOCK_SIZE_BYTES;
				}
			}
		}
	}

	if(i > 0) {//orphanage used
		time(&orphanageINode.last_modified);
		write_inode(orphanageNum, &orphanageINode);
		//put in directorystrlen
		dir.u_file[dirspot].free = 0;
		file_struct file;
		file.inode_number = orphanageNum;
		char * fname;
		fprintf(stdout, "Please give file name for orphaned blocks\n");
		fname = readline(buildPrompt());
		strncpy(file.file_name, fname, MAX_FILE_NAME_SIZE);
		file.free = 0;
		dir.u_file[dirspot] = file;
		dir.num_files++;
		lseek(virtual_disk, BLOCK_SIZE_BYTES*DIRECTORY_BLOCK, SEEK_SET);
		crash_write(virtual_disk, &dir, sizeof(dir_struct));
		fprintf(stdout, "File reclaimed but may be incomplete\n");
	}

	//check for things pointing at erased data
	int fitr;//file iterator
	for (fitr = 0; fitr < MAX_FILES_PER_DIRECTORY; fitr++) {
		if(!dir.u_file[fitr].free) {//file is taken
			//
			int inodenum = dir.u_file[fitr].inode_number;
			read_inode(inodenum, &curr_inode);
			if(curr_inode.free) {//problem occured during delete
				fprintf(stderr, "Inconsistency found, file points to free inode\n");
				fprintf(stderr, "Deleting file\n");
				dir.u_file[fitr].inode_number = -1;
				dir.u_file[fitr].free = 1;
				dir.num_files--;
				//write dir
				lseek(virtual_disk, BLOCK_SIZE_BYTES*DIRECTORY_BLOCK, SEEK_SET);
				crash_write(virtual_disk, &dir, sizeof(dir_struct));
			}else {//no problem with inode 
				//look for issues with bitmap
				int blockitr;//block interator
				int numblcoks = curr_inode.num_blocks;
				bool startErasing = false;
				for(blockitr = 0; blockitr < numblcoks; blockitr++) {
					int bl = curr_inode.blocks[blockitr];
					if(startErasing) {//erase remaining blocks in inode
						if(bl != 0) {//make sure i dont overwrite superblock
							bit_map[bl] = 0;
							//fill block with null chars to erase data
							lseek(virtual_disk, BLOCK_SIZE_BYTES*curr_inode.blocks[i], SEEK_SET);
							crash_write(virtual_disk, nullblock, BLOCK_SIZE_BYTES);
							curr_inode.blocks[blockitr] = 0;
						}
					}else if(!bit_map[bl]) {//block is free
						fprintf(stderr, "Inconsistency found, inode points to free block\n");
						fprintf(stderr, "Deleting file\n");
						startErasing = true;
					}
					
				}
				if(startErasing) {//need to delete things
					curr_inode.file_size_bytes = 0;
					curr_inode.num_blocks = 0;
					curr_inode.free = 1;
					time(&curr_inode.last_modified);
					//write inode
					write_inode(inodenum, &curr_inode);
					dir.u_file[fitr].inode_number = -1;
					dir.u_file[fitr].free = 1;
					dir.num_files--;
					//write dir
					lseek(virtual_disk, BLOCK_SIZE_BYTES*DIRECTORY_BLOCK, SEEK_SET);
					crash_write(virtual_disk, &dir, sizeof(dir_struct));
				}
			}
		}
	}
	return 1;
}

/*
 * Iterates through the directory and prints the 
 * file names, size and last modified date and time.
 */
void u_ls() {
	struct tm *loc_tm;
	int numFilesFound = 0;
	int i;
	for (i = 0; i< MAX_FILES_PER_DIRECTORY; i++) {
		if (!(dir.u_file[i].free)) {
			numFilesFound++;
			/* file_name size last_modified */
			
			read_inode(dir.u_file[i].inode_number, &curr_inode);
			loc_tm = localtime(&curr_inode.last_modified);
			fprintf(stderr,"%s\t%d\t%d/%d\t%d:%d\n",dir.u_file[i].file_name, 
				curr_inode.num_blocks*BLOCK_SIZE_BYTES, 
				loc_tm->tm_mon, loc_tm->tm_mday, loc_tm->tm_hour, loc_tm->tm_min);

		}
	}

	if (numFilesFound == 0){
		fprintf(stdout, "Directory empty\n");
	}

}

/*
 * Formats the virtual disk. Saves the superblock
 * bit map and the single level directory.
 */
int u_format(int diskSizeBytes, char* file_name) {
	int minimumBlocks;

	/* create the virtual disk */
	if ((virtual_disk = open(file_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR)) < 0) {
		fprintf(stderr, "Unable to create virtual disk file: %s\n", file_name);
		return 0;
	}


	fprintf(stderr, "Formatting userfs of size %d bytes with %d block size in file %s\n", diskSizeBytes, BLOCK_SIZE_BYTES, file_name);

	minimumBlocks = 3+ NUM_INODE_BLOCKS+1;
	if (diskSizeBytes/BLOCK_SIZE_BYTES < minimumBlocks) {
		/* If it's impossible to have the superblock, bitmap,
		   directory, inodes and at least one datablock then
			 there no point attempting to continue. */
		fprintf(stderr, "Minimum size virtual disk is %d bytes %d blocks\n", BLOCK_SIZE_BYTES*minimumBlocks, minimumBlocks);
		fprintf(stderr, "Requested virtual disk size %d bytes results in %d bytes %d blocks of usable space\n", diskSizeBytes, BLOCK_SIZE_BYTES*minimumBlocks, minimumBlocks);
		return 0;
	}


	/*************************  BIT MAP **************************/
	assert(sizeof(BIT)* BIT_MAP_SIZE <= BLOCK_SIZE_BYTES);
	fprintf(stderr, "%d blocks %d bytes reserved for bitmap (%ld bytes required)\n", 1, BLOCK_SIZE_BYTES, sizeof(BIT)*BIT_MAP_SIZE);
	fprintf(stderr, "\tImplies Max size of disk is %ld blocks or %ld bytes\n", BIT_MAP_SIZE, BIT_MAP_SIZE*BLOCK_SIZE_BYTES);

	if (diskSizeBytes >= BIT_MAP_SIZE* BLOCK_SIZE_BYTES) {
		fprintf(stderr, "Unable to format a userfs of size %d bytes\n", diskSizeBytes);
		return 0;
	}

	init_bit_map();

	/* first three blocks will be taken with the 
	   superblock, bitmap and directory */
	allocate_block(BIT_MAP_BLOCK);
	allocate_block(SUPERBLOCK_BLOCK);
	allocate_block(DIRECTORY_BLOCK);
	/* next NUM_INODE_BLOCKS will contain inodes */
	int i;
	for (i = 3; i < 3+NUM_INODE_BLOCKS; i++) {
		allocate_block(i);
	}

	lseek(virtual_disk, BLOCK_SIZE_BYTES*BIT_MAP_BLOCK, SEEK_SET);
	crash_write(virtual_disk, bit_map, sizeof(BIT)*BIT_MAP_SIZE);


	/***********************  DIRECTORY  ***********************/
	assert(sizeof(dir_struct) <= BLOCK_SIZE_BYTES);

	fprintf(stderr, "%d blocks %d bytes reserved for the userfs directory (%ld bytes required)\n", 1, BLOCK_SIZE_BYTES, sizeof(dir_struct));
	fprintf(stderr, "\tMax files per directory: %d\n", MAX_FILES_PER_DIRECTORY);
	fprintf(stderr,"Directory entries limit filesize to %d characters\n", MAX_FILE_NAME_SIZE);

	init_dir();
	lseek(virtual_disk, BLOCK_SIZE_BYTES*DIRECTORY_BLOCK, SEEK_SET);
	crash_write(virtual_disk, &dir, sizeof(dir_struct));


	/***********************  INODES ***********************/
	fprintf(stderr, "userfs will contain %ld inodes (directory limited to %d)\n", MAX_INODES, MAX_FILES_PER_DIRECTORY);
	fprintf(stderr,"Inodes limit filesize to %d blocks or %d bytes\n", MAX_BLOCKS_PER_FILE, MAX_BLOCKS_PER_FILE* BLOCK_SIZE_BYTES);

	curr_inode.free = 1;
	//int i;
	for (i = 0; i < MAX_INODES; i++) {
		write_inode(i, &curr_inode);
	}


	/***********************  SUPERBLOCK ***********************/
	assert(sizeof(superblock) <= BLOCK_SIZE_BYTES);
	fprintf(stderr, "%d blocks %d bytes reserved for superblock (%ld bytes required)\n", 1, BLOCK_SIZE_BYTES, sizeof(superblock));
	init_superblock(diskSizeBytes);
	fprintf(stderr, "userfs will contain %d total blocks: %d free for data\n", sb.disk_size_blocks, sb.num_free_blocks);
	fprintf(stderr, "userfs contains %ld free inodes\n", MAX_INODES);

	lseek(virtual_disk, BLOCK_SIZE_BYTES*SUPERBLOCK_BLOCK, SEEK_SET);
	crash_write(virtual_disk, &sb, sizeof(superblock));
	sync();

	/* when format complete there better be at 
	   least one free data block */
	assert(u_quota() >= 1);
	fprintf(stderr,"Format complete!\n");

	return 1;
}

/*
 * Attempts to load a file system given the virtual disk name
 * It will perform an automated fsck, which will try to recover any
 * potentially lost data and fix inconsistencies.
 */
int recover_file_system(char *file_name) {
	if ((virtual_disk = open(file_name, O_RDWR)) < 0) {
		printf("virtual disk open error\n");
		return 0;
	}

	/* read the superblock */
	lseek(virtual_disk, BLOCK_SIZE_BYTES*SUPERBLOCK_BLOCK, SEEK_SET);
	read(virtual_disk, &sb, sizeof(superblock));

	/* read the bit_map */
	lseek(virtual_disk, BLOCK_SIZE_BYTES*BIT_MAP_BLOCK, SEEK_SET);
	read(virtual_disk, bit_map, sizeof(BIT)*BIT_MAP_SIZE);

	/* read the single level directory */
	lseek(virtual_disk, BLOCK_SIZE_BYTES* DIRECTORY_BLOCK, SEEK_SET);
	read(virtual_disk, &dir, sizeof(dir_struct));

	if (!superblockMatchesCode()) {
		fprintf(stderr, "Unable to recover: userfs appears to have been formatted with another code version\n");
		return 0;
	}
	if (!sb.clean_shutdown) {
		/* Try to recover your file system */
		fprintf(stderr, "u_fsck in progress......\n");
		if (u_fsck()) {
			fprintf(stderr, "Recovery complete\n");
			return 1;
		} else {
			fprintf(stderr, "Recovery failed\n");
			return 0;
		}
	} else {
		fprintf(stderr, "Clean shutdown detected\n");
		return 1;
	}
}

/* Cleanly performs a shutdown and ensures everything is consistent.
 * Pay attention to what order you update values in case a crash occurs during
 * the shutdown.
 *
 * Returns 1 on success, 0 on failure.
 *
 * TODO: Finish implementing this function.
 */
int u_clean_shutdown() {
	sb.num_free_blocks = u_quota();
	sb.clean_shutdown = 1;

	lseek(virtual_disk, BLOCK_SIZE_BYTES* SUPERBLOCK_BLOCK, SEEK_SET);
	crash_write(virtual_disk, &sb, sizeof(superblock));
	sync();

	close(virtual_disk);
	/* is this all that needs to be done on clean shutdown? */
	return 1;
}
