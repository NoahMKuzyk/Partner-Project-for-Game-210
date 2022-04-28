#pragma once

#include "windows.h"
#include "xinput.h"
#include "main.cpp"


class Controller
{
	//const float MAX_ANALOG_VALUE = 32767.0f; // No longer needed.
	//float cursor_x = WINDOW_WIDTH / 2;
	//float cursor_y = WINDOW_HEIGHT / 2; // Cursor is 17x17 pixels. Might be too small idk.  //* Cursor is no longer needed.

public:
	Controller();
	~Controller();

	void Update(); //Function to check if mouse or controller is used.
	void ProcessControllerEvent(); //Function makes A button work (hopefully).
	void ProcessMouseEvent(SDL_Event* Event); //Function makes mouse clicking work (hopefully).
	void Poke(); //Function with Clare's button stuff.

	bool IsAPressed() { return (controllerState.Gamepad.wButtons & XINPUT_GAMEPAD_A); }
	//float GetLeftStickXValue() { return controllerState.Gamepad.sThumbLX / MAX_ANALOG_VALUE; }
	//float GetLeftStickYValue() { return controllerState.Gamepad.sThumbLY / MAX_ANALOG_VALUE; }

private:

	XINPUT_STATE controllerState;
	bool ControllerConnected;
};

