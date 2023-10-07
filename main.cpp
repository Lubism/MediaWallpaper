#include"MediaWallpaper/MediaWallPaper.hpp"
#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	UI::MediaWallPaper app(argc, argv);
	return app.exec();
}