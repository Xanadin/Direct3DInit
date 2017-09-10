#include "GameTimer.h"
#include <Windows.h>

GameTimer::GameTimer() :
	mSecondsPerCount(0.0),
	mDeltaTime(-1.0),
	mBaseTime(0),
	mPauseTime(0),
	mPrevTime(0),
	mCurrTime(0),
	mStopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}