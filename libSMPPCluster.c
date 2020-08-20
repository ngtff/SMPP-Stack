#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>

#include "sirik_core.h"
#include "sirik_socket.h"


#include "libSMPPCluster.h"


int ngtff_smpp__add_esme_info( NGTFF_Esme * NGTFF_Esme)
{
	return 0;
}



// gcc -std=gnu99 -g3 -shared -o libSMPPCluster.so libSMPPCluster.c ../sirik_core.c ../lib_endpoint/sirik_socket.c -I../ -I../lib_endpoint/ -fPIC
