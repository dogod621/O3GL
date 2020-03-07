// O3GL
#include "PrintInfo.hpp"

// Main
int main(int argc, char** argv)
{
	O3GL::PrintFrameCounter<0> printFrameCounter("PrintFrameCounter", 0, 0, 300, 600);
	O3GL::PrintGLVersion<1> printGLVersion("PrintGLVersion", 300, 0, 300, 600);

	O3GL::Window<2> printAllInOne("PrintAllInOne", GLUT_DOUBLE | GLUT_RGBA, 600, 0, 610, 600, 33);
	O3GL::PrintFrameCounter<3> subPrintFrameCounter(printAllInOne, 0, 0, 300, 600);
	O3GL::PrintGLVersion<4> subPrintGLVersion(printAllInOne, 310, 0, 300, 600);

	printFrameCounter->Init();
	printGLVersion->Init();
	printAllInOne->Init();
	subPrintFrameCounter->Init();
	subPrintGLVersion->Init();

	O3GL::EnterMainLoop();
	return EXIT_SUCCESS;
}