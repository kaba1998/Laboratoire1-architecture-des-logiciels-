#include<string>
#include<iostream>
#include "MediaPlayer.h"
using namespace std;

void main()
{
	wstring path_input = L"C:/Users/Aicha/source/repos/jesuisfatigue/Example.avi";
	LPCUWSTR path = path_input.c_str();
	MediaPlayer mediaPlayer(path);
	mediaPlayer.Run();

}

