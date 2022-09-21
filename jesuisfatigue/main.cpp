#include<string>
#include<iostream>
#include "MediaPlayer.h"
using namespace std;

void main()
{
	wstring path_input = L"C:/Users/Aicha/Desktop/Laboratoire1-architecture-des-logiciels--main/Laboratoire1-architecture-des-logiciels--main/Example.avi"; // cette partie il faut aller copier l'emplacement de la video et venir le collé ici pourque ça fonctionne 
	LPCUWSTR path = path_input.c_str();
	MediaPlayer mediaPlayer(path);
	mediaPlayer.Run();

}

