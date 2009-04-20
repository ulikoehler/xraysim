#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>
using namespace std;
// Usable AlmostEqual function

#define PI 3.14159265

int main()
{
	int ain;
	cout << "a: ";
	cin >> ain;
	//Convert the input to radians
	double a = (ain/360.0) * PI;
	cout << "a=" << a << "\n";
	float s = 0.0, c = 0.0; //sin, cos
	
	cout << "csin(a)=" << sin(a) << "\n";
	cout << "ccos(a)=" << cos(a) << "\n\n";
	//Test fsin
	cout << "Testing fsin\n";
	asm volatile
	(
		"fsin;wait;fstp %0"
		:"=m"(s)
		:"t"(a)
	);
	cout << "sin=" << s << "\n\n";
	//Test fsincos
	s = 0.0;c = 0.0;
	asm volatile
	(
		"fsincos;wait;fstp %0;fstp %1;wait"
		:"=m"(c),"=m"(s)
		:"t"(a)
	);
	cout << "sin=" << s << "\n";
	cout << "cos=" << c << "\n";
	return 0;
}