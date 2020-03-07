#include "Callbacks.hpp"

void DisplayCallback()
{
	displayCallbackMessage.Active();

	// Clear backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	float lineHeight = 0.06f;
	float wx = -1.0f;
	float wy = -1.0f;

	O3GL::Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_EXTENSIONS)), 0.0f, 0.0f, 0.0f, 1.0f);
	wy += lineHeight;
	O3GL::Text(wx, wy, 0.0f, "GL_EXTENSIONS: ", 0.0f, 1.0f, 0.0f, 1.0f);
	wy += lineHeight;
	
	O3GL::Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_RENDERER)), 0.0f, 0.0f, 0.0f, 1.0f);
	wy += lineHeight;
	O3GL::Text(wx, wy, 0.0f, "GL_RENDERER: ", 0.0f, 1.0f, 0.0f, 1.0f);
	wy += lineHeight;
	
	O3GL::Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_VENDOR)), 0.0f, 0.0f, 0.0f, 1.0f);
	wy += lineHeight;
	O3GL::Text(wx, wy, 0.0f, "GL_VENDOR: ", 0.0f, 1.0f, 0.0f, 1.0f);
	wy += lineHeight;
	
	O3GL::Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)), 0.0f, 0.0f, 0.0f, 1.0f);
	wy += lineHeight;
	O3GL::Text(wx, wy, 0.0f, "GL_SHADING_LANGUAGE_VERSION: ", 0.0f, 1.0f, 0.0f, 1.0f);
	wy += lineHeight;
	
	O3GL::Text(wx, wy, 0.0f, "\t\t" + std::string((char*)glGetString(GL_VERSION)), 0.0f, 0.0f, 0.0f, 1.0f);
	wy += lineHeight;
	O3GL::Text(wx, wy, 0.0f, "GL_VERSION: ", 0.0f, 1.0f, 0.0f, 1.0f);
	wy += lineHeight;
	wy += lineHeight;
	wy += lineHeight;

	//
	displayCallbackMessage.Draw(wx, wy, lineHeight);
	overlayDisplayCallbackMessage.Draw(wx, wy, lineHeight);
	reshapeCallbackMessage.Draw(wx, wy, lineHeight);
	keyboardCallbackMessage.Draw(wx, wy, lineHeight);
	keyboardUpCallbackMessage.Draw(wx, wy, lineHeight);
	specialCallbackMessage.Draw(wx, wy, lineHeight);
	specialUpCallbackMessage.Draw(wx, wy, lineHeight);
	mouseCallbackMessage.Draw(wx, wy, lineHeight);
	motionCallbackMessage.Draw(wx, wy, lineHeight);
	passiveMotionCallbackMessage.Draw(wx, wy, lineHeight);
	visibilityCallbackMessage.Draw(wx, wy, lineHeight);
	entryCallbackMessage.Draw(wx, wy, lineHeight);
	closeCallbackMessage.Draw(wx, wy, lineHeight);
	timerCallbackMessage.Draw(wx, wy, lineHeight);

	// Swap buffers
	glutSwapBuffers();
}

void OverlayDisplayCallback()
{
	overlayDisplayCallbackMessage.Active();
}

void ReshapeCallback(int width, int height)
{
	reshapeCallbackMessage.Active();
	reshapeCallbackMessage.width = width;
	reshapeCallbackMessage.height = height;
}

void KeyboardCallback(unsigned char key, int x, int y)
{
	keyboardCallbackMessage.Active();
	keyboardCallbackMessage.key = key;
	keyboardCallbackMessage.x = x;
	keyboardCallbackMessage.y = y;

	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	}
}

void KeyboardUpCallback(unsigned char key, int x, int y)
{
	keyboardUpCallbackMessage.Active();
	keyboardUpCallbackMessage.key = key;
	keyboardUpCallbackMessage.x = x;
	keyboardUpCallbackMessage.y = y;
}

void SpecialCallback(int key, int x, int y)
{
	specialCallbackMessage.Active();
	specialCallbackMessage.key = key;
	specialCallbackMessage.x = x;
	specialCallbackMessage.y = y;
}

void SpecialUpCallback(int key, int x, int y)
{
	specialUpCallbackMessage.Active();
	specialUpCallbackMessage.key = key;
	specialUpCallbackMessage.x = x;
	specialUpCallbackMessage.y = y;
}

void MouseCallback(int button, int state, int x, int y)
{
	mouseCallbackMessage.Active();
	mouseCallbackMessage.button = button;
	mouseCallbackMessage.state = state;
	mouseCallbackMessage.x = x;
	mouseCallbackMessage.y = y;
}

void MotionCallback(int x, int y)
{
	motionCallbackMessage.Active();
	motionCallbackMessage.x = x;
	motionCallbackMessage.y = y;
}

void PassiveMotionCallback(int x, int y)
{
	passiveMotionCallbackMessage.Active();
	passiveMotionCallbackMessage.x = x;
	passiveMotionCallbackMessage.y = y;
}

void VisibilityCallback(int state)
{
	visibilityCallbackMessage.Active();
	visibilityCallbackMessage.state = state;
}

void EntryCallback(int state)
{
	entryCallbackMessage.Active();
	entryCallbackMessage.state = state;
}

void CloseCallback()
{
	closeCallbackMessage.Active();
}

void TimerCallback(int value)
{
	timerCallbackMessage.Active();
	timerCallbackMessage.value = value;

	glutPostRedisplay();
	glutTimerFunc(33, TimerCallback, 0);
}