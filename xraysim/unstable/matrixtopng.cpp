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
	
	stringstream s;
	s << matrix;
	
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
	cairo_surface_t* s = cairo_image_surface_create(CAIRO_FORMAT_RGB24, matrix.getXExtent(), matrix.getYExtent());
	cairo_t* c = cairo_create(s);
	
	cairo_set_source_rgb(c, 1,1,1);
	cairo_set_operator(c, CAIRO_OPERATOR_SOURCE);
	cairo_paint(c);	
	
	uint xExt = matrix.getXExtent();
	uint yExt = matrix.getXExtent();
	
	for(int ix = 0; ix < xExt; ix++)
	{
		for(int iy = 0; iy < yExt; iy++)
		{
			double val = (255 - matrix[ix][iy]) / 255.0;
			cairo_set_source_rgb(c, val, val,val);
			cairo_rectangle(c, ix, iy, 1, 1);
			cairo_stroke(c);
		}
	}	
	cairo_surface_write_to_png(s, "x.png");
	return 0;
}