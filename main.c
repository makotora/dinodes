#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "difile.h"
#include "dirlist.h"
#include "blocks.h"
#include "metadata.h"

int main(int argc, char *argv[])
{
	
	int fd;
	int i = 1;
	int compression = 0;
	
	while(i < argc)
	{
		if(strcmp(argv[i], "-c") == 0)
		{
			int j;
			if (strcmp(argv[i+1], "-j") == 0)
			{
				compression = 1;
				i++;
			}

			listofdirs * dirlist;
			dirlist_create(&dirlist);
			for (j = i+2; j < argc; ++j)
			{
				if(argv[j][ strlen(argv[j]) -1 ] == '/')
					argv[j][strlen(argv[j])-1] = '\0';
				dirlist_add_dir(dirlist, argv[j]);
			}
			char *name = malloc((strlen(argv[i+1]) + 4)*sizeof(char));
			name[0] = '\0';
			strcat(name, argv[i+1]);
			strcat(name, ".di");

			di_createfile(name, dirlist, compression);

			free(name);
		    dirlist_free(&dirlist);
		    return 0;

		}
		else if (strcmp(argv[i], "-a") == 0)
		{
			int j;
			if (strcmp(argv[i+1], "-j") == 0)
			{
				compression = 1;
				i++;
			}

			listofdirs * dirlist;
			dirlist_create(&dirlist);
			for (j = i+2; j < argc; ++j)
			{
				dirlist_add_dir(dirlist, argv[j]);
			}
			
			di_append(argv[i+1],dirlist,compression);

		    dirlist_free(&dirlist);
		    return 0;
		}
		else if (strcmp(argv[i], "-x") == 0)
		{
			fd = OpenFile(argv[i+1]);
			listofdirs * dirlist;
            dirlist_create(&dirlist);

            for (int j = i+2; j < argc; ++j)
            {
                dirlist_add_dir(dirlist, argv[j]);
            }


		      extractDiFile(fd, argv[i+1], dirlist);

		      CloseFile(fd);
            dirlist_free(&dirlist);

		    return 0;			
		}
		else if (strcmp(argv[i], "-d") == 0)
		{
		}
		else if (strcmp(argv[i], "-m") == 0)
		{
			fd = OpenFile(argv[i+1]);
			printMetadata(fd);		
		    CloseFile(fd);

		    return 0;
		}
		else if (strcmp(argv[i], "-q") == 0)
		{
			fd = OpenFile(argv[i+1]);
			
			listofdirs * dirlist;
			dirlist_create(&dirlist);
			for (int j = i+2; j < argc; ++j)
			{
				dirlist_add_dir(dirlist, argv[j]);
			}

		    di_find_dirlist(fd, dirlist);

    		dirlist_free(&dirlist);
			CloseFile(fd);
			return 0;			
		}
		else if (strcmp(argv[i], "-p") == 0)
		{
			fd = OpenFile(argv[i+1]);
			printHierarchy(fd);					
		    CloseFile(fd);

		    return 0;
		}
		i++;
	}

	return 0;
}