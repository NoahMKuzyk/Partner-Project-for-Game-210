#include <iostream>

#include "Controller.h"

Controller::Controller()
{
	ControllerConnected = false;
}

Controller::~Controller()
{

}

//===========================================================================\\

// Replace the Poke() function's code that's in ButtonMasher() with this function's declaration.

void Controller::Update()
{
	Sleep(20);
	system("cls");

	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	XInputGetState(0, &controllerState);

	if (XInputGetState(0, &controllerState) == ERROR_SUCCESS)
	{
		ControllerConnected = true;
		std::cout << "Controller is connected." << std::endl;
		ProcessControllerEvent();
	}
	else
	{
		SDL_Event Event;

		ControllerConnected = false;
		std::cout << "No controller is connected." << std::endl;
		while (SDL_PollEvent(&Event))
		{
			ProcessMouseEvent(&Event);
		}
	}
	//std::cout << "Cursor is at x: " << cursor_x << " and y: " << cursor_y << "." << std::endl; // Ancient relic code, no longer needed.
}
//===========================================================================\\

void Controller::Poke()
{
		//Delay Can Be Updated For Faster Click-Rate 
		SDL_Delay(10);


		//Changes Sprite To Pushed Button
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background_texture, NULL, NULL);
		SDL_RenderCopy(renderer, buttonpush_texture, NULL, &button_pos);
		SDL_RenderPresent(renderer);


		buttonClicks++; //Increases Click Amount


		//Delay Can Be Updated For Faster Click-Rate
		SDL_Delay(10);


		//Changes Sprite To Unpushed Button
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background_texture, NULL, NULL);
		SDL_RenderCopy(renderer, button_texture, NULL, &button_pos);
		SDL_RenderPresent(renderer);
}

void Controller::ProcessControllerEvent()
{
	//if (GetLeftStickXValue() > 0)
	//{
	//	cursor_x += GetLeftStickXValue() * 5;
	//
	//}
	//if (GetLeftStickYValue() > 0)
	//{
	//	cursor_y += GetLeftStickYValue() * 5;
	//} // Ancient relic code, no longer needed.
	if (IsAPressed() == true)
	{
		Poke();
	}
}

void Controller::ProcessMouseEvent(SDL_Event* Event)
{
	switch (Event->type)
	{
	//case SDL_MOUSEMOTION:
	//	SDL_GetMouseState(&mouse_x, &mouse_y);
	//	break; // Ancient relic code, no longer needed.

	case SDL_MOUSEBUTTONDOWN:
		Poke();
		break;
	}
}

