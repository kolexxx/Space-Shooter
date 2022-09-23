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

	static std::array<bool, 91> s_Pressed;
	static std::array<bool, 91> s_Down;
	static std::array<bool, 91> s_Released;
};