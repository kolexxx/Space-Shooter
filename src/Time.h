#pragma once

class Time
{
public:
	/// <returns>The delta between the last tick and the current one.</returns>
	static float Delta();
	/// <returns>The time since startup.</returns>
	static float Now();
	/// <returns>The number of ticks that have been processed</returns>
	static unsigned int Tick();

	friend int main( void );
private:
	static float s_delta;
	static unsigned int s_tick;
};