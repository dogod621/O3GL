// O3GL
#include "DrawPrimitive.hpp"

//
int main()
{
	try
	{
		O3GL::PTR<O3GL::QuadRender> quadRender = O3GL::PTR<O3GL::QuadRender>(new O3GL::QuadRender());
		O3GL::DrawPrimitiveWindow<0> drawPrimitiveWindow(quadRender, "DrawPrimitive", 0, 0, 800, 600, 33);
		O3GL::ModeMenu<0> modeMenu(quadRender);
		drawPrimitiveWindow.Init();
		quadRender->Init();
		quadRender->PrintShaderSources("unlit_vert");
		quadRender->PrintShaderSources("unlit_frag");
		modeMenu.Attach(drawPrimitiveWindow, GLUT_RIGHT_BUTTON);
		O3GL::EnterMainLoop();
	}
	catch (const std::exception & ex)
	{
		PRINT_ERROR(ex.what());
	}
	return EXIT_SUCCESS;
}