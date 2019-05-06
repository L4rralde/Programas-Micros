#include "msecbase.h"

void pause( unsigned short msvalue ){
	for (unsigned short x=0; x<=msvalue; x++) msecbase();				//Jump to millisec delay routine
}