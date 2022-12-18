#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <menu.h>

void
prnt(const char *string) {
	printf("from common: %s\n", string);
}

#endif 
