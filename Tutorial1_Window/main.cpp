// O3GL
#include "VisualizeEvent.hpp"

// Main
int main(int argc, char** argv)
{
	O3GL::VisualizeEvent visualizeEvent(0, 0, 800, 600);
	visualizeEvent->Start();
	return EXIT_SUCCESS;
}