#pragma once

#include <array>

class Input
{
public:
	static bool Pressed( char key );
	static bool Down( char key );
	static bool Released( char key );

	friend int main( void );
private:
	static void Build();

	static std::array<bool, 91> s_pressed;
	static std::array<bool, 91> s_down;
	static std::array<bool, 91> s_released;
};