// O3GL
#include "PrintInfo.hpp"

// Main
int main(int argc, char** argv)
{
	O3GL::PrintFrameCounter<0> printFrameCounter("PrintFrameCounter", 0, 0, 400, 600);
	O3GL::PrintGLVersion<1> printGLVersion("PrintGLVersion", 500, 0, 400, 600);
	printFrameCounter->Init();
	printGLVersion->Init();
	O3GL::EnterMainLoop();
	return EXIT_SUCCESS;
}