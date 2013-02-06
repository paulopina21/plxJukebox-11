#include "PFCBuilder.h"
#include <iostream>
#include <string>
#include <stdlib.h>

//#include <libplx/linux.h>

#define BUTTERFLY "0x33, 0x4F, 0x47, 0x79, 0xFA, 0x2F, 0x5D, 0xF0, 0x9C, 0x46, 0x16, 0x8F, 0x20, 0xAF, 0x44, 0x92, 0x37, 0x0E, 0x17, 0x35, 0xA1, 0xCF, 0xF5, 0x68, 0x51, 0xE9, 0x61, 0x9A, 0xF1, 0xB6, 0x14,0xD6"

using namespace std;

void printhelp() {
  cout << "\n USAGE:";
  cout << " PFCMaker -i <INPUT XML File> -o <OUTPUT folder> \n";
//  cout << "Creating New PFC: \n pfsbuilder -c -p <PFSNAME>\n\n";
//  cout << "-c Creates the Plexus File System\n";
//  cout << "-p PFS name\n\n\n";
//  cout << "Inserting Files to an existing Pfs:\n pfsbuilder -p <PFSNAME> -i <FILENAME> -n <INTERNALNAME>\n\n";
//  cout << "-i Insert File\n";
//  cout << "-n Internal File Name\n";
//  cout << "-p PFS name\n";
//  getch();
}

//enum {PFSOP_INSERT, PFSOP_LIST, PFSOP_EXTRACT};

int main(int argc, char* argv[]) {
  cout << " Hello world!! I am PFCMaker v" << RPF_VERSION;

  if (argc == 1) {
      printhelp();
      return 0;
  }

 #ifdef _DEBUG
  cout << "\n" << SEPARATOR;
  cout << " As I'm in debug mode I'll tell you my dirty little secrets...";
  cout << "\n Header size: " << HEADERSIZE << " bytes";
  cout << "\n Binary Data size: Variable";
  cout << "\n File Descriptor (unity) size: " << ENTRYSIZE << " bytes";
  cout << "\n some love...";
  cout << "\n and some weed!!!";
  cout << "\n" << SEPARATOR;
#endif

  //  CFilePfc* testpak = new CFilePfc();

  //testpak->Open("c:\\test.pfs");
  //testpak->InsertFile("D:\\xbox360cemu.ini","xbox360cemu.ini", RPF_ENTRY_TYPE_SYSTEM, false);
  //testpak->InsertFile("D:\\Downloads\\TED__Salman_Khan__Let's_use_video_to_reinvent_educ[V005526091].mp4","Reinvent_Education.mp4", RPF_ENTRY_TYPE_FILE, true);
  //testpak->ExtractFile("Reinvent_Education.mp4","C:\\Reinvent_Education.mp4");

  char* XMLFilePath;
  char* OutputFolderPath;

	for (int c = 0; c <= argc - 1; c++) {
		string arg = argv[c];

		if (arg == "-i")
		{
			XMLFilePath = argv[c + 1];
		}

		if (arg == "-o")
		{
			OutputFolderPath = argv[c + 1];
		}

	}

  CPFCBuilder Builder;
  Builder.CreateFromFile(XMLFilePath, OutputFolderPath);

  return 0;

}
