#pragma once
#pragma once
#include<dshow.h>
#include<string>
using namespace std;

enum PlaybackState
{
	STATE_NO_GRAPH,
	STATE_RUNNIG,
	STATE_PAUSED,
	STATE_STOPPED,
};
class MediaPlayer
{
private:
	IGraphBuilder* pGraph;
	IMediaControl* pControl;
	IMediaEvent* pEvent;
	IMediaSeeking* pSeeking;
	HRESULT hr;

	PlaybackState state;

	LPCUWSTR file;

	LONGLONG starPos, stopPos;

public:
	MediaPlayer(LPCUWSTR filein);
	~MediaPlayer();


	//MediaPlayer(LPCWSTR filein);

	void Play_Pause_video();
	void Acceleration();
	void Repeat();
	void Run();
	void Quitter();



};

