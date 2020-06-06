#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	Timer();
	Timer(const Timer&);
	~Timer();
	bool Initialize();
	void Frame();
	float GetTime();
private:
	INT64 m_frequency;
	float m_ticksPerMs;
	INT64 m_startTime;
	float m_frameTime;
};
#endif