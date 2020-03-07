// O3GL
#include "PrintEvent.hpp"

// Main
int main(int argc, char** argv)
{
	O3GL::PrintEvent<0> printEvent(0, 0, 800, 600);
	printEvent->Start();
	return EXIT_SUCCESS;
}