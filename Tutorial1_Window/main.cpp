// O3GL
#include "VisCallbacks.hpp"

// Main
int main(int argc, char** argv)
{
	O3GL::VisCallbacks visCallbacks(0, 0, 800, 600);
	visCallbacks->Start();
	return EXIT_SUCCESS;
}