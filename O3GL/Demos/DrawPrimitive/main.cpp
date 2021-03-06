// O3GL
#include "DrawPrimitive.hpp"

//
int main()
{
	try
	{
		O3GL::DrawPrimitiveWindow<0> drawPrimitiveWindow("DrawPrimitive", 0, 0, 800, 600, 33);
		drawPrimitiveWindow.Init();
		drawPrimitiveWindow.GetRender("quad")->PrintShaderSources("unlit_vert");
		drawPrimitiveWindow.GetRender("quad")->PrintShaderSources("unlit_frag");
		O3GL::EnterMainLoop();
	}
	catch (const std::exception & ex)
	{
		PRINT_ERROR(ex.what());
	}
	return EXIT_SUCCESS;
}