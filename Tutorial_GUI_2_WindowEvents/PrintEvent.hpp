#pragma once

// O3GL
#include "O3GL/Core/Utils.hpp"
#include "O3GL/Core/Window.hpp"

//
namespace O3GL
{
	//
	template<int key>
	class PrintEventWindow : public Window<key>
	{
	public:
		PrintEventWindow(const std::string& name, int x, int y, int width, int height, unsigned int tick = 10) :
			Window<key>(name, GLUT_DOUBLE | GLUT_RGBA, x, y, width, height, tick), litTime(100.0)
		{}

		PrintEventWindow(int window, int x, int y, int width, int height, unsigned int tick = 10) :
			Window<key>(window, x, y, width, height, tick), litTime(100.0)
		{}

	public:
		virtual void InitGLStatusEvent() const;

	public:
		virtual void DisplayEvent(const Display::Message& m);
		virtual void TimerEvent(const Timer::Message& m);

	protected:
		double litTime;
	};

	//
	template<int key>
	void PrintEventWindow<key>::InitGLStatusEvent() const
	{
		glClearColor(1.0, 1.0, 1.0, 0.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	}

	template<int key>
	void PrintEventWindow<key>::DisplayEvent(const Display::Message& m)
	{
		// Clear backbuffer
		glClear(GL_COLOR_BUFFER_BIT);

		//
		float lineHeight = 0.06f;
		float wx = -1.0f;
		float wy = -1.0f;

		Text(wx, wy, 0.0f, "Tick elapsed: " + std::to_string(tickElapsed) + " ms", 1.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestDisplayMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestDisplayMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestDisplayMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestOverlayDisplayMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestOverlayDisplayMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestOverlayDisplayMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestReshapeMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestReshapeMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestReshapeMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestKeyboardMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestKeyboardMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestKeyboardMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestKeyboardUpMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestKeyboardUpMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestKeyboardUpMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestSpecialMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestSpecialMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestSpecialMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestSpecialUpMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestSpecialUpMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestSpecialUpMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestMouseMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestMouseMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestMouseMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestMotionMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestMotionMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestMotionMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestPassiveMotionMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestPassiveMotionMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestPassiveMotionMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestVisibilityMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestVisibilityMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestVisibilityMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestEntryMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestEntryMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestEntryMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestCloseMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestCloseMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestCloseMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		if (latestTimerMessage.timeElapsed < litTime)
			Text(wx, wy, 0.0f, std::string(latestTimerMessage), 1.0f, 0.0f, 0.0f, 1.0f);
		else
			Text(wx, wy, 0.0f, std::string(latestTimerMessage), 0.0f, 0.0f, 0.0f, 1.0f);
		wy += lineHeight;

		// Swap buffers
		glutSwapBuffers();
	}

	template<int key>
	void PrintEventWindow<key>::TimerEvent(const Timer::Message& m)
	{
		glutPostRedisplay();
	}
};