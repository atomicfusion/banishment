#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include "banishment.h"

//NOTICE: This function is inherintly racey. Make sure that nothing is touching what is being unmounted.
static int banish_once(const char *path) {
	struct stat pathinfo;
	lstat(path,&pathinfo);
	
	if(S_ISDIR(pathinfo.st_mode)) {
		DIR *dir;
		dirent *entry;
		dir = opendir(path);
		
		while((entry = readdir(dir)) != NULL) {
			if(!strcmp(entry->d_name,".")
				||!strcmp(entry->d_name,"..")) {
				continue;
			}
			
			char *entrypath;
			if(asprintf(&entrypath,"%s/%s",path,entry->d_name) >= 0) {
				if(banish(entrypath)) {
					free(entrypath);
					return -1;
				}
			}
			else {
				free(entrypath);
				return -1;
			}
			free(entrypath);
		}
	}
	
	return umount2(path,MNT_DETACH);
}

int banish(const char *path) {
	while(true) {
		if(banish_once(path)) {
			if(errno == EINVAL) {
				return 0;
			}
			else {
				return -1;
			}
		}
	}
}