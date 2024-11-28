#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
	Timer();
	Timer(float start);
	virtual ~Timer();

	float Get() const;
	void Set(float value);
	void Reset();

private:
	float MsToSec(float value) const;

	float m_timer;

};

#endif // !TIMER_H
