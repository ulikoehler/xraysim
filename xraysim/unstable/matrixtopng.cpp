#include "../include/include.hpp"
#include "../include/matrix.hpp"
#include "../include/matrixtask.hpp"

#include <tr1/random>
#include <cairo/cairo.h>

using namespace std;
using namespace std::tr1;

int main(int argc, char** argv)
{
	ifstream f(argv[1]);
	Matrix2d matrix(f);
	f.close();
	cairo_surface_t* s = cairo_image_surface_create(CAIRO_FORMAT_RGB24, matrix.getXExtent(), matrix.getYExtent());
	cairo_t* c = cairo_create(s);
	
	cairo_set_source_rgb(c, 1,1,1);
	cairo_set_operator(c, CAIRO_OPERATOR_SOURCE);
	cairo_paint(c);
	
	cairo_set_source_rgb(c, 1,1,1);
	
	uint xExt = matrix.getXExtent();
	uint yExt = matrix.getXExtent();
	
	for(int ix = 0; ix < xExt; ix++)
	{
		for(int iy = 0; iy < yExt; iy++)
		{
			int val = matrix[ix][iy];
			cairo_set_source_rgb(c, val, val, val);
			cairo_rectangle(c, ix, iy, 1, 1);
		}
	}
	cairo_stroke(c);
	
	cairo_surface_write_to_png(s, "x.png");
	return 0;
}