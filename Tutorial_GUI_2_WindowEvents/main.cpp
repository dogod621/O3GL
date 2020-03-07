// O3GL
#include "PrintEvent.hpp"

// Main
int main(int argc, char** argv)
{
	O3GL::PrintEvent<0> printEvent("PrintEvent", 0, 0, 800, 600);
	printEvent->Init();
	O3GL::EnterMainLoop();
	return EXIT_SUCCESS;
}