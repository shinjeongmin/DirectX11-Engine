#pragma once

// Ÿ�̸� �����ϴ� ���.
// 1. �������� API. // ���� �̰ɷ� ������ ����.
// 2. std::chrono // ������������ �� �� �ִٰ� ����µ�, �ϴ��� �𸣰���.

#include <Windows.h>

class GameTimer
{
public:
	static void Start();
	static double GetTime();
	static double DeltaTime();
	static float DeltaTimef();

	static void Update();

	static void Reset();
	static int FPS();

private:
	static double countsPerSecond;
	static __int64 countStart;
	static int frameCount;
	static int fps;
	static __int64 previousFrameTime;

};