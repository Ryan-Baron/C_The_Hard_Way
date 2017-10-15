/* The Stack, Scope, and Globals

#include <stdio.h>
#include "ex22.h"
#inclde "dbg.h"

int THE_SIZE = 1000;

static int THE_AGE = 37;

int get_age()
{
	return THE_AGE;
}
