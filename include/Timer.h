#pragma once

class Timer
{
public:
	Timer(const float cooldown) : m_cooldown(cooldown), m_timeLeft(0) {}

	float updateTimer()
	{
		auto delta = m_clock.restart().asSeconds();
		this->m_timeLeft -= delta;
		return delta;
	}

	float	getCooldown() const { return m_cooldown; }
	bool	isTimeUp() const { return this->m_timeLeft <= 0; }
	void	updateTimer(const float deltaTime) { m_timeLeft -= deltaTime; }
	void	setCooldown(int newCD) { m_cooldown = newCD; }
	void	setTimer() { this->m_timeLeft = this->m_cooldown; }
	float	getTimeLeft() const { return m_timeLeft; }

private:
	float m_cooldown;
	sf::Clock m_clock;
	float m_timeLeft;
};
