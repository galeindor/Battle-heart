#pragma once

class Timer
{
public:
	Timer(const float cooldown) : m_cooldown(cooldown), m_timeLeft(0.f) {}
	void updateTimer(const float deltaTime) { this->m_timeLeft -= deltaTime; }
	void setTimer() { this->m_timeLeft = this->m_cooldown; }
	bool isTimeUp() const { return this->m_timeLeft <= 0; }

private:
	float m_cooldown;
	float m_timeLeft;
};
