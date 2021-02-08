//=============================================================================
#include "FileManager.h"
//#include "Log.h"
#include "Stringify.h"
#include "CApp.h"

#include <stdio.h>

#ifndef _WIN32
	#include <sys/param.h>
	#include <dirent.h>
	#include <unistd.h>
#else
	#include <Windows.h>
	#endif
	

char *data_path = NULL;
char *pref_path = NULL;


void InitializeDataPath() {

	char *base_path = SDL_GetBasePath();
	if (base_path)
	{
		data_path = base_path;
		SDL_Log("SDL_GetBasePath found\n");
	}
	else
	{
		data_path = SDL_strdup("/");
		SDL_Log("SDL_GetBasePath not found\n");
	}
	
	char *base_path2 = SDL_GetPrefPath("tutorial", "game");
	if (base_path2) {
		pref_path = base_path2;
		SDL_Log("SDL_GetPrefPath found\n");
	}
	else {
		/* Do something to disable writing in-game */
		SDL_Log("SDL_GetPrefPath found\n");
	}


}

//=============================================================================
bool FileManager::SetContents(std::string Filename, std::string Content, bool Relative) {
	if (Filename == "") return false;
	if (Relative) Filename = GetCWD() + DIR_SEPARATOR + Filename;
	std::ofstream FileHandle;
	FileHandle.open(Filename.c_str());
	if (!FileHandle.is_open()) return false;
	FileHandle << Content;
	if (FileHandle)
		FileHandle.close();
	return true;
}
//-----------------------------------------------------------------------------
std::string FileManager::GetContents(std::string Filename, bool Relative) {

	if (Filename == "") return "";
	if (Relative) Filename = GetCWD() + DIR_SEPARATOR + Filename;
	std::string Content;
	std::ifstream FileHandle;
	FileHandle.open(Filename.c_str());
	if (FileHandle.is_open()) {
		while (FileHandle.good()) {
			std::string Buffer;
			getline(FileHandle, Buffer);
			if (Buffer == "") continue;
			Content += Buffer + "\n";
		}
		if (FileHandle)
			FileHandle.close();
	}

	return Content;

}
//-----------------------------------------------------------------------------
std::vector<std::string> FileManager::GetFilesInFolder(std::string Folder) {

	/*
	InitializeDataPath();

	std::string temp_home = Stringify::Char(data_path);
	std::string temp_pref = Stringify::Char(pref_path);

	SDL_Log("current home path: %s\n", temp_home.c_str());
	SDL_Log("current pref path: %s\n", temp_pref.c_str());
	*/

	std::vector<std::string> List;
	std::string CWD = GetCWD();
	std::string Path = CWD;
	std::string asset = "assets";

	
	
	//if (Folder != "") Path += asset + DIR_SEPARATOR + Folder + DIR_SEPARATOR;
	if (Folder != "") Path += Folder;
	
	DIR* DirHandle = NULL;
	dirent* FileHandle = NULL;
	// Needs improved
	if ((DirHandle = opendir(Folder.c_str())) != NULL) 
	{
		while ((FileHandle = readdir(DirHandle)) != NULL) 
		{
			if (std::string(FileHandle->d_name) == ".") continue;
			if (std::string(FileHandle->d_name) == "..") continue;
				
			std::string Filename = Path + DIR_SEPARATOR + FileHandle->d_name;
			SDL_Log("Found File: %s\n", Filename.c_str());
				
			List.push_back(Filename);
		}
		closedir(DirHandle);
	}
	else
	{
		SDL_Log("UNIX: unable to open path %s\n", Path.c_str());
		SDL_Log("UNIX: unable to open dir %s\n", Folder.c_str());
	}

	return List;

}
//-----------------------------------------------------------------------------
std::string FileManager::GetCWD() {

	std::string CWD;

	char Buffer[MAXPATHLEN];
	CWD = (getcwd(Buffer, MAXPATHLEN) ? std::string(Buffer) : std::string(""));
	SDL_Log("UNIX: current dir: %s\n", CWD.c_str());

	return CWD;

}
//-----------------------------------------------------------------------------
std::string FileManager::GetFilenameWithoutExt(std::string Filename) {

	std::vector<std::string> Parts = Stringify::Explode(Filename, DIR_SEPARATOR);
	std::string NewFilename = Parts[Parts.size() - 1];
	// To Do: Filename could potentially have one or more dots
	Parts = Stringify::Explode(NewFilename, ".");
	NewFilename = Parts[0];
	
	return NewFilename;

}
//-----------------------------------------------------------------------------
std::string FileManager::GetFilenameExt(std::string Filename) {

	std::vector<std::string> Parts = Stringify::Explode(Filename, ".");
	
	return (Parts.size() <= 1 ? "" : Parts[Parts.size() - 1]);

}
//=============================================================================