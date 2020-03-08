// O3GL
#include "FrameCounterMenu.hpp"
#include "Tutorial_GUI_1_Window/PrintInfo.hpp"

//
int main()
{
	try
	{
		O3GL::PrintFrameCounterWindow<0> printFrameCounterWindow("PrintFrameCounter", 0, 0, 300, 600, 33);
		O3GL::PrintGLVersionWindow<1> printGLVersionWindow("PrintGLVersion", 300, 0, 300, 600, 33);

		O3GL::Window<2> printAllInOneWindow("PrintAllInOne", GLUT_DOUBLE | GLUT_RGBA, 600, 0, 610, 600, 33);
		O3GL::PrintFrameCounterWindow<3> printFrameCounterSubWindow(printAllInOneWindow, 0, 0, 300, 600, 33);
		O3GL::PrintGLVersionWindow<4> printGLVersionSubWindow(printAllInOneWindow, 310, 0, 300, 600, 33);

		printFrameCounterWindow.Init();
		printGLVersionWindow.Init();
		printAllInOneWindow.Init();
		printFrameCounterSubWindow.Init();
		printGLVersionSubWindow.Init();

		O3GL::ModifyFrameCounterMenu<0> modifyFrameCounterMenu(&printFrameCounterWindow.frameCounter);
		O3GL::FrameCounterMenu<1> frameCounterMenu(&printFrameCounterWindow.frameCounter);
		O3GL::ModifyFrameCounterMenu<2> modifyFrameCounterMenu2(&printFrameCounterSubWindow.frameCounter);
		O3GL::FrameCounterMenu<3> frameCounterMenu2(&printFrameCounterSubWindow.frameCounter);

		frameCounterMenu.AddMenu("Modify Frame Counter", modifyFrameCounterMenu);
		frameCounterMenu.Attach(*printFrameCounterWindow, GLUT_RIGHT_BUTTON);
		frameCounterMenu2.AddMenu("Modify Frame Counter", modifyFrameCounterMenu2);
		frameCounterMenu2.Attach(*printFrameCounterSubWindow, GLUT_RIGHT_BUTTON);

		O3GL::EnterMainLoop();
	}
	catch (const std::exception & ex)
	{
		PRINT_ERROR(ex.what());
	}
	return EXIT_SUCCESS;
}