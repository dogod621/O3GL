// O3GL
#include "PrintInfo.hpp"

// Main
int main(int argc, char** argv)
{
	O3GL::PrintInfo<0> printInfo(0, 0, 800, 600);
	printInfo->Start();
	return EXIT_SUCCESS;
}