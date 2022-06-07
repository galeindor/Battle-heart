#pragma once

class Timer
{
public:
	Timer(const float cooldown) : m_cooldown(cooldown), m_timeLeft(cooldown) {}

	float updateTimer()
	{
		auto delta = m_clock.restart().asSeconds();
		this->m_timeLeft -= delta;
		return delta;
	}
	void updateTimer(const float deltaTime) { m_timeLeft -= deltaTime; }
	void setTimer() { this->m_timeLeft = this->m_cooldown; }
	bool isTimeUp() const { return this->m_timeLeft <= 0; }

private:
	float m_cooldown;
	sf::Clock m_clock;
	float m_timeLeft;
};
