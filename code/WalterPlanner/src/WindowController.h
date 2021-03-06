/*
 * WindowController.h
 *
 * Represents control of bot and interactive view
 *
 * Author: JochenAlt
 */

#ifndef UI_BOTWINDOWCTRL_H_
#define UI_BOTWINDOWCTRL_H_

#if defined(_WIN32)
#include <windows.h>  // openGL windows
#endif
#include <thread>

#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <GL/Glui.h>

#include "spatial.h"
#include "Kinematics.h"
#include "BotView.h"
#include "TrajectoryView.h"

class WindowController {
public:
	WindowController() {
		anglesCallback = NULL;
		tcpCallback = NULL;
		eventLoopThread = NULL;
		uiReady = false;
	};

	static WindowController& getInstance() {
			static WindowController instance;
			return instance;
	}

	bool readyForControllerEvent();
	bool isReady() { return uiReady; };
	bool setup(int argc, char** argv);

	void setAnglesCallback(void (* callback)( const JointAngles& angles));
	void setTcpInputCallback(bool (* callback)( const Pose& pose));

	void changedPoseCallback();
	void changedAnglesCallback();
	void notifyNewBotData();

	BotView mainBotView;
	TrajectoryView trajectoryView;

private:
	 void UIeventLoop();
	 GLUI* createInteractiveWindow(int mainWindow);

	 void (*anglesCallback)( const JointAngles& angles);
	 bool (*tcpCallback)( const Pose& pose);
	 std::thread* eventLoopThread;
	 bool uiReady;
};


#endif /* UI_BOTWINDOWCTRL_H_ */
