// O3GL
#include "PrintEvent.hpp"
#include "Demos/Window/PrintInfo.hpp"

// Main
int main(int argc, char** argv)
{
	try
	{
		O3GL::PrintEventWindow<0> printEventWindow("PrintEvent", 0, 0, 500, 600, 33);

		O3GL::Window<1> printAllInOneWindow("PrintAllInOne", GLUT_DOUBLE | GLUT_RGBA, 500, 0, 810, 600, 33);
		O3GL::PrintFrameCounterWindow<3> printFrameCounterSubWindow(*printAllInOneWindow, 0, 0, 300, 600, 33);
		O3GL::PrintEventWindow<2> printEventSubWindow(*printAllInOneWindow, 310, 0, 500, 600, 33);

		printEventWindow.Init();
		printAllInOneWindow.Init();
		printFrameCounterSubWindow.Init();
		printEventSubWindow.Init();

		O3GL::EnterMainLoop();
	}
	catch (const std::exception & ex)
	{
		PRINT_ERROR(ex.what());
	}
	return EXIT_SUCCESS;
}