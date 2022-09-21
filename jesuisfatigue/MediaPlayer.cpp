#pragma comment(lib, "Strmiids.lib")
#include <dshow.h>
#include<conio.h>
#include "MediaPlayer.h"
#include <iostream>


MediaPlayer::MediaPlayer(LPCWSTR filein)
{
    pGraph = NULL;
    pControl = NULL;
    pEvent = NULL;
    pSeeking = NULL;

    file = filein;
    // Initialize the COM library.
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return;
    }

    // Create the filter graph manager and query for interfaces.
    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&pGraph);
    if (FAILED(hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
        return;
    }

    hr = pGraph->QueryInterface(IID_IMediaControl, (void**)&pControl);
    hr = pGraph->QueryInterface(IID_IMediaEvent, (void**)&pEvent);
    hr = pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeeking);

    // Build the graph. IMPORTANT: Change this string to a file on your system.
    hr = pGraph->RenderFile(file, NULL);

    hr = pSeeking->GetCurrentPosition(&starPos);
}
void MediaPlayer::Play_Pause_video()
{
    if (state == STATE_RUNNIG)
    {
        pControl->Pause();                // pour mettre pause et play pour la video 
        state = STATE_STOPPED;
    }
    else if (state == STATE_STOPPED)
    {
        pControl->Run();
        state = STATE_RUNNIG;
    }
}

void MediaPlayer::Acceleration()
{
    double rate;
    hr = pSeeking->GetRate(&rate);
    if (rate > 1.5)
        hr = pSeeking->SetRate(1.0);   // pour acceleration de la video
    else
        hr = pSeeking->SetRate(2.0);
}

void MediaPlayer::Repeat()
{
    if (state == STATE_RUNNIG)
    {
        pControl->Pause();            // retour en arriére 
        state = STATE_STOPPED;
    }
    pSeeking->SetPositions(&starPos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    pControl->Run();
    state = STATE_RUNNIG;

}
void MediaPlayer::Quitter()
{
    cout << "QUITTE LE PROGRAMME..." << endl;

    pControl->Release();
    pEvent->Release();
    pGraph->Release();
    CoUninitialize();

    state = STATE_STOPPED;

}

MediaPlayer::~MediaPlayer()
{
    if (state == STATE_STOPPED)      // pour arreter la video 
        return;

    Quitter();
}
void MediaPlayer::Run()
{
    char choix;

    if (SUCCEEDED(hr))
    {
        // Run the graph.
        hr = pControl->Run();
        if (SUCCEEDED(hr))
        {
            state = STATE_RUNNIG;
            while (true)
            {
                choix = _getch();
                switch (choix)
                {
                case 'p':
                case 'P':
                    Play_Pause_video();
                    break;
                case 'a':
                case 'A':
                    Acceleration();
                    break;
                case 'r':
                case'R':
                    Repeat();
                    break;
                case 'q':
                case 'Q':
                    Quitter();
                    return;
                    break;

                }
            }
        }
    }

}













