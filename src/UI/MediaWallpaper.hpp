#pragma once
#include"UI/Core/APP/APPCore.hpp"

class MediaWallpaper :private UI::APPCore
{
public:
	inline MediaWallpaper(int& argc, char**& argv)
		:APPCore(argc, argv) {}

	inline virtual ~MediaWallpaper() {}
public:
	inline int runProgram() { return APPCore::run(); }
};
