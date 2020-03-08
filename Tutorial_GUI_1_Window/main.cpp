// O3GL
#include "PrintInfo.hpp"

// Main
int main(int argc, char** argv)
{
	try
	{
		O3GL::PrintFrameCounterWindow<0> printFrameCounterWindow("PrintFrameCounter", 0, 0, 300, 600);
		O3GL::PrintGLVersionWindow<1> printGLVersionWindow("PrintGLVersionWindow", 300, 0, 300, 600);

		O3GL::Window<2> printAllInOneWindow("PrintAllInOne", GLUT_DOUBLE | GLUT_RGBA, 600, 0, 610, 600, 33);
		O3GL::PrintFrameCounterWindow<3> printFrameCounterSubWindow(printAllInOneWindow, 0, 0, 300, 600);
		O3GL::PrintGLVersionWindow<4> printGLVersionSubWindow(printAllInOneWindow, 310, 0, 300, 600);

		printFrameCounterWindow.Init();
		printGLVersionWindow.Init();
		printAllInOneWindow.Init();
		printFrameCounterSubWindow.Init();
		printGLVersionSubWindow.Init();

		O3GL::EnterMainLoop();
	}
	catch (const std::exception & ex)
	{
		PRINT_ERROR(ex.what());
	}
	return EXIT_SUCCESS;
}