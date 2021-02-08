//
//  Author: Shervin Aflatooni
//

#include "Asset.h"


#ifndef ANDROID
#include <fstream>
#else
#include "AndroidAssetManager.h"
#endif

Asset::Asset(const std::string &fileName)
{
	this->fileName = fileName;
	buffer = NULL;
	size = 0;
}

Asset::~Asset(void)
{
	delete buffer;
}

const char *Asset::read(void)
{
	if (!buffer) {
		SDL_Log("Reading file: %s from disk", fileName.c_str());
#ifndef ANDROID
		std::ifstream temp("../assets/" + fileName, std::ifstream::binary);

		temp.seekg(0, std::ios::end);
		size = temp.tellg();

		buffer = new char[size + 1];
		buffer[size] = '\0';

		temp.seekg(0);

		temp.read(buffer, size);

		temp.close();
#else
		AAsset* aAsset = AAssetManager_open(AndroidAssetManager::getAssetManager(), fileName.c_str(), AASSET_MODE_UNKNOWN);

		if (aAsset)
		{
			size = AAsset_getLength(aAsset);


			buffer = new char[size + 1];

			if (int r = AAsset_read(aAsset, buffer, size) < 0)
				SDL_Log("Could not read asset: %i", r);

			buffer[size] = '\0';

			AAsset_close(aAsset);
		}
		else {
			SDL_Log("Could not read file: %s", fileName.c_str());
		}
#endif
	}

	return buffer;
}

size_t Asset::getSize(void)
{
	return size;
}

std::string Asset::getFileName(void)
{
	return fileName;
}