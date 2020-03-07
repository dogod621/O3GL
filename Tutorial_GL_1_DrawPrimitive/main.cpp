// O3GL
#include "DrawPrimitive.hpp"

//
int main()
{
	try
	{
		O3GL::DrawPrimitive<0> drawPrimitive("DrawPrimitive", 0, 0, 800, 600);
		drawPrimitive->Init();
		O3GL::EnterMainLoop();
	}
	catch (const std::exception & ex)
	{
		PRINT_ERROR(ex.what());
	}
	return EXIT_SUCCESS;
}