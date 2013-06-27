#include "stdafx.h"
#include "record.h"
#include "externals.h"
#include <stdio.h>


unsigned long LastWrite = 0xffffffff;
unsigned long LastPlay = 0;
unsigned int LastPlayTotal;


int output_channels = 2;
int output_samplesize = 4;


unsigned char mixer_playbuf[ SOUNDSIZE ];


FILE *fp_xa2;


#include "dsound.cpp"
#include "xaudio_2.cpp"
//#include "openal.cpp"


/*
0 = DirectSound
1 = XAudio2 stereo
2 = XAudio2 5.1
3 = XAudio2 7.1
4 = OpenAL
*/


void SetupSound(void)
{
	switch( iOutputDriver ) {
		case 0: DSound_SetupSound(); break;
		case 1: XAudio2_SetupSound(); break;
		case 2: XAudio2_SetupSound(); break;
		case 3: XAudio2_SetupSound(); break;
		//case 4: OpenAL_SetupSound(); break;
	}
}


void RemoveSound(void)
{
	if(iDoRecord) RecordStop();
	
	switch( iOutputDriver ) {
		case 0: DSound_RemoveSound(); break;
		case 1: XAudio2_RemoveSound(); break;
		case 2: XAudio2_RemoveSound(); break;
		case 3: XAudio2_RemoveSound(); break;
		//case 4: OpenAL_RemoveSound(); break;
	}
}


int SoundBufferReady()
{
	switch( iOutputDriver ) {
		//case 4: return OpenAL_SoundBufferReady(); break;
	}

	return 1;
}


int SoundGetBytesBuffered()
{
	switch( iOutputDriver ) {
		case 0: return DSound_SoundGetBytesBuffered(); break;
		case 1: return XAudio2_SoundGetBytesBuffered(); break;
		case 2: return XAudio2_SoundGetBytesBuffered(); break;
		case 3: return XAudio2_SoundGetBytesBuffered(); break;
		//case 4: return OpenAL_SoundGetBytesBuffered(); break;
	}

	return 0;
}


int SoundGetSamplesBuffered()
{
	return SoundGetBytesBuffered() / output_samplesize;
}


void SoundFeedStreamData(unsigned char* pSound,long lBytes)
{
	if(iDoRecord) RecordBuffer(pSpuBuffer,((unsigned char *)pS)-((unsigned char *)pSpuBuffer));


	switch( iOutputDriver ) {
		case 0: DSound_SoundFeedStreamData( pSound, lBytes ); break;
		case 1: XAudio2_SoundFeedStreamData( pSound, lBytes ); break;
		case 2: XAudio2_SoundFeedStreamData( pSound, lBytes ); break;
		case 3: XAudio2_SoundFeedStreamData( pSound, lBytes ); break;
		//case 4: OpenAL_SoundFeedStreamData( pSound, lBytes ); break;
	}
}


void SoundPhantomPad()
{
	switch( iOutputDriver ) {
		case 0: DSound_SoundPhantomPad(); break;
		case 1: break;
		case 2: break;
		case 3: break;
		//case 4: OpenAL_SoundFeedStreamData( pSound, lBytes ); break;
	}
}


void SoundRecordStreamData(unsigned char* pSound,long lBytes)
{
	// win32 feature
	if(iDoRecord) RecordBuffer(pSpuBuffer,((unsigned char *)pS)-((unsigned char *)pSpuBuffer));
}


void ResetSound()
{
	// fast-forward lag?
	CDDAPlay  = CDDAStart;
	CDDAFeed  = CDDAStart;
	
	XAPlay  = XAStart;
	XAFeed  = XAStart;


	LastWrite = 0xffffffff;
}
