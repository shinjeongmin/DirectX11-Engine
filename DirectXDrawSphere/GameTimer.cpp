#include "GameTimer.h"

double GameTimer::countsPerSecond;
__int64 GameTimer::countStart;
int GameTimer::frameCount;
int GameTimer::fps;
__int64 GameTimer::previousFrameTime;

void GameTimer::Start()
{
	LARGE_INTEGER frequencyCount;

	// �ϵ���� Ŭ�� ��.
	QueryPerformanceFrequency(&frequencyCount);

	// �ʴ� �ϵ���� Ÿ�̸��� ���� ��.
	countsPerSecond = (double)(frequencyCount.QuadPart); // ���� 1�ʴ� 100�� �����Ѵٰ� ĥ ��,

	// ���� ������ ������ ���� ��.
	QueryPerformanceCounter(&frequencyCount); // ���⼭ 50�� ��ϵǸ�, 0.5�� �����ٰ� �����Ѵ�.
	countStart = frequencyCount.QuadPart;
}

double GameTimer::GetTime()
{
	// ������ ���۵� �ķκ��� ���� �ð�.
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	double time = (double)(currentTime.QuadPart - countStart) / countsPerSecond;

	return time;
}

double GameTimer::DeltaTime()
{
	return 0.0;
}

float GameTimer::DeltaTimef()
{
	return 0.0f;
}

void GameTimer::Update()
{
}

void GameTimer::Reset()
{
}

int GameTimer::FPS()
{
	return 0;
}