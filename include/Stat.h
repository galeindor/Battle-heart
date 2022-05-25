#pragma once

class Stat
{
public:
	Stat(int initVal);
	~Stat() = default;

	virtual bool handleStat(int amount);
	int getStatCopy() { return this->m_val; }

protected:
	int& getStat() { return this->m_val; }

private:
	int m_val;
};