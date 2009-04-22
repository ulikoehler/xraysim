#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>
using namespace std;
// Usable AlmostEqual function

#define PI 3.14159265

struct Point
{
	float x;
	float y;
}

struct Point calcG(double alpha, float r, float r_e,)
{
	struct Point g;
	uint rads = r + r_e;
	asm volatile
	(
		"fsincos;" //cos(alpha) on top, sin(alpha) on st(1)
		"fmul %4;" //Multiply the cos with rads (=param 4)
		"fmul %%st(1), %4;" //Multiply the sin with rads (=param 4)
		:"=m"(g.x),"=m"(g.y)
		:"t"(alpha), "f"(rads)
	);
}

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
		"fsin;fstp %0"
		:"=m"(s)
		:"t"(a)
	);
	cout << "sin=" << s << "\n\n";
	//Test fsincos
	s = 0.0;c = 0.0;
	asm volatile
	(
		"fsincos;fstp %0;fstp %1;"
		:"=m"(c),"=m"(s)
		:"t"(a)
	);
	cout << "sin=" << s << "\n";
	cout << "cos=" << c << "\n";
	return 0;
}