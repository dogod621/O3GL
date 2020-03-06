// std
#include<sstream>

// O3GL
#include "Callbacks.hpp"

// Global vars
static int windowWidth = 1280;
static int windowHeight = 720;


// GL operators
void InitGLStatus();

void InitGLObjects();


// Main
int main(int argc, char** argv)
{
	try
	{
		// Create GLUT window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowPosition(0, 0);
		glutInitWindowSize(windowWidth, windowHeight);
		glutCreateWindow("GLUT Window");

		// Init glew after window has been created
		glewInit();
		InitGLStatus();
		InitGLObjects();

		// Set glut callback before start
		glutDisplayFunc(DisplayCallback);
		glutOverlayDisplayFunc(OverlayDisplayCallback);
		glutReshapeFunc(ReshapeCallback);
		glutKeyboardFunc(KeyboardCallback);
		glutKeyboardUpFunc(KeyboardUpCallback);
		glutSpecialFunc(SpecialCallback);
		glutSpecialUpFunc(SpecialUpCallback);
		glutMouseFunc(MouseCallback);
		glutMotionFunc(MotionCallback);
		glutPassiveMotionFunc(PassiveMotionCallback);
		glutVisibilityFunc(VisibilityCallback);
		glutEntryFunc(EntryCallback);
		glutCloseFunc(CloseCallback); // Close callback
		glutTimerFunc(33, TimerCallback, 0);

		// Start the glut main loop thread
		glutMainLoop();
	}
	catch (const std::exception & ex)
	{
		PRINT_ERROR(ex.what());
	}

	system("PAUSE");
	return EXIT_SUCCESS;
}

void InitGLStatus()
{
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClearDepth(1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void InitGLObjects()
{
}