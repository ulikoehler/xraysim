#include "../include/include.hpp"
#include "../include/matrix.hpp"
#include "../include/matrixtask.hpp"
#include <cassert>

#include <tr1/random>
#include <cairo/cairo.h>

using namespace std;
using namespace std::tr1;

int main(int argc, char** argv)
{
	ifstream f(argv[1]);
	Matrix2d matrix(f);
	f.close();
	
	/* //Generate a random matrix
	//To be replaced by the code above when the matrix deserializing works
	//Start	
	mt19937 rng(time(0));
	Matrix2d matrix(350,350);
	uint xExt = matrix.getXExtent();
		//assert(xExt == 100);
	uint yExt = matrix.getXExtent();
		//assert(yExt == 100);
	for(int ix = 0; ix < xExt; ix++)
	{
		for(int iy = 0; iy < yExt; iy++)
		{
			matrix[ix][iy] = rng() % 255;
		}
	} */
	//End
	matrix.writeToPNG("x.png");
	return 0;
}