#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
HANDLE hMapFile;
LPVOID lpMapAddress;

hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,          // read/write permission
                           FALSE,                        // Do not inherit the name
                           TEXT("SharedObject")); // of the mapping object.

if (hMapFile == NULL)
{
   printf("Could not open file mapping object (%d).\n", GetLastError());
   return -1;
}

lpMapAddress = MapViewOfFile(hMapFile,            // handle to mapping object
                             FILE_MAP_ALL_ACCESS, // read/write permission
                             0,                   // max. object size
                             0,                   // size of hFile
                             0);                  // map entire file

if (lpMapAddress == NULL)
{
   printf("Could not map view of file (%d).\n", GetLastError());
   return -1;
}

printf("%s\n",lpMapAddress);

UnmapViewOfFile(lpMapAddress);
CloseHandle(hMapFile);

}

//consumer
//producer

#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
HANDLE hFile, hMapFile;
LPVOID mapAddress;

	// first create/open the file
	hFile = CreateFile("temp.txt",
						GENERIC_READ | GENERIC_WRITE,
						0,
						NULL,
						OPEN_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);

	if (hFile == INVALID_HANDLE_VALUE) {
   		fprintf(stderr,"Could not open file temp.txt (%d).\n",GetLastError());
   		return -1;
	}

	// now obtain a mapping for it

	hMapFile = CreateFileMapping(hFile,
									NULL,
									PAGE_READWRITE,
									0,
									0,
									TEXT("SharedObject"));

	if (hMapFile == NULL) {
		fprintf(stderr,"Could not create mapping (%d).\n", GetLastError());
   		return -1;
	}

	// now establish a mapped viewing of the file

	mapAddress = MapViewOfFile(hMapFile,FILE_MAP_ALL_ACCESS,0,0,0);

	if(mapAddress == NULL) {
		printf("Could not map view of file (%d).\n", GetLastError());
		return -1;
	}

	// write to shared memory

	sprintf((char *)mapAddress,"%s","Shared memory message");

	while (1);
	// remove the file mapping
	UnmapViewOfFile(mapAddress);

	// close all handles
	CloseHandle(hMapFile);
	CloseHandle(hFile);
}

