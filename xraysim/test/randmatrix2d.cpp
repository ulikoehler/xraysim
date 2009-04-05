#include "../include/include.hpp"
#include "../include/matrix.hpp"
#include "../include/matrixtask.hpp"

#include <tr1/random>

using namespace std;
using namespace std::tr1;

int main(int argc, char** argv)
{
	mt19937 rng(time(0));
	int xdim = atoi(argv[2]);
	int ydim = xdim;
	Matrix2d matrix(xdim, ydim);
	for(int ix = 0; ix < xdim; ix++)
	{
		for(int iy = 0; iy < ydim; iy++)
		{
			matrix[ix][iy] = rng();
		}
	}
	
	ofstream f(argv[1]);
	matrix.writeTo(f);
	f.close();
	return EXIT_SUCCESS;
}