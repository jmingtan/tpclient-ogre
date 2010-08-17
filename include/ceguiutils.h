#ifndef CEGUIUTILS__H
#define CEGUIUTILS__H

#include <CEGUI.h>
#include <OIS.h>

CEGUI::MouseButton convertOISButtonToCEGUI(int buttonID) {
	if (buttonID == OIS::MB_Left)
		return CEGUI::LeftButton;
	if (buttonID == OIS::MB_Right)
		return CEGUI::RightButton;
	if (buttonID == OIS::MB_Middle)
		return CEGUI::MiddleButton;
	if (buttonID == OIS::MB_Button3)
		return CEGUI::X1Button;
	return CEGUI::LeftButton;
}

#endif
