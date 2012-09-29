#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "banishment.h"

int main(int argc,char **argv) {
	if(argc != 2) {
		return EXIT_FAILURE;
	}
	if(banish(argv[1]) < 0) {
		fprintf(stderr,"Error: %m",errno);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}