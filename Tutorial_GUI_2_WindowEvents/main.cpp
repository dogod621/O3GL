// O3GL
#include "PrintEvent.hpp"
#include "Tutorial_GUI_1_Window/PrintInfo.hpp"

// Main
int main(int argc, char** argv)
{
	O3GL::PrintEvent<0> printEvent("PrintEvent", 0, 0, 500, 600);

	O3GL::Window<1> printAllInOne("PrintAllInOne", GLUT_DOUBLE | GLUT_RGBA, 500, 0, 810, 600, 33);
	O3GL::PrintFrameCounter<3> subPrintFrameCounter(printAllInOne, 0, 0, 300, 600);
	O3GL::PrintEvent<2> subPrintEvent(printAllInOne, 310, 0, 500, 600);
	
	printEvent->Init();
	printAllInOne->Init();
	subPrintFrameCounter->Init();
	subPrintEvent->Init();

	O3GL::EnterMainLoop();
	return EXIT_SUCCESS;
}