#pragma once

#include <iostream>
#include <string>
#include <SDL.h>

std::string getResourcePath(const std::string &subDir = "") {
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	static std::string baseRes;
	if (baseRes.empty()){
		char *basePath = SDL_GetBasePath();

		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		} else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}

		int pos = -1;
		if (baseRes.find("bin") != std::string::npos) {
			pos = baseRes.rfind("bin");
		} else if (baseRes.find("build") != std::string::npos) {
			pos = baseRes.rfind("build");
		} if (pos == -1) return "";

		baseRes = baseRes.substr(0, pos) + "assets" + PATH_SEP;
	} return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}
