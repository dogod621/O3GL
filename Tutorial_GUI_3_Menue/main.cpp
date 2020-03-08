// O3GL
#include "FrameCounterMenu.hpp"
#include "Tutorial_GUI_1_Window/PrintInfo.hpp"

//
int main()
{
	try
	{
		O3GL::PrintFrameCounter<0> printFrameCounter("PrintFrameCounter", 0, 0, 300, 600);
		O3GL::PrintGLVersion<1> printGLVersion("PrintGLVersion", 300, 0, 300, 600);

		O3GL::Window<2> printAllInOne("PrintAllInOne", GLUT_DOUBLE | GLUT_RGBA, 600, 0, 610, 600, 33);
		O3GL::PrintFrameCounter<3> subPrintFrameCounter(printAllInOne, 0, 0, 300, 600);
		O3GL::PrintGLVersion<4> subPrintGLVersion(printAllInOne, 310, 0, 300, 600);

		printFrameCounter.Init();
		printGLVersion.Init();
		printAllInOne.Init();
		subPrintFrameCounter.Init();
		subPrintGLVersion.Init();

		O3GL::ModifyFrameCounterMenu<0> modifyFrameCounterMenu(&printFrameCounter.frameCounter);
		O3GL::FrameCounterMenu<1> frameCounterMenu(&printFrameCounter.frameCounter);
		O3GL::ModifyFrameCounterMenu<2> modifyFrameCounterMenu2(&subPrintFrameCounter.frameCounter);
		O3GL::FrameCounterMenu<3> frameCounterMenu2(&subPrintFrameCounter.frameCounter);

		frameCounterMenu.AddMenu("Modify Frame Counter", modifyFrameCounterMenu);
		frameCounterMenu.Attach(*printFrameCounter, GLUT_RIGHT_BUTTON);
		frameCounterMenu2.AddMenu("Modify Frame Counter", modifyFrameCounterMenu2);
		frameCounterMenu2.Attach(*subPrintFrameCounter, GLUT_RIGHT_BUTTON);

		O3GL::EnterMainLoop();
	}
	catch (const std::exception & ex)
	{
		PRINT_ERROR(ex.what());
	}
	return EXIT_SUCCESS;
}