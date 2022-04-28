// processing events
#include "EventHandler.h"
#include <ctime>
// creating a basic gameobject
#include "Objects/ColourBlock.h"
#include "../Graphics.h"

#include <iostream>
#include <fstream>
#include <stdio.h>

//Rendering images
#include <SDL.h> 
#include <string.h>
#include <SDL_ttf.h>



using namespace std;


void ButtonMasher(); //Function To Play Button Masher Game

// GameState
bool GameRunning = true;

//The main player data struct for saving and loading.
struct Player {
	int daysSurvived;
	int resMetal;
	int resPlastic;
	int resPower;
}playerData;

//Initializes the player struct to its default values. 
void InitializePlayerData() {
	playerData.daysSurvived = 0;
	playerData.resMetal = 235;
	playerData.resPlastic = 100;
	playerData.resPower = 100;
}

//Saves the current Player Data to a file
void SavePlayerData() {
	ofstream savedData("PlayerSave.txt");
	savedData << playerData.daysSurvived << ' ' << playerData.resMetal << ' ' << playerData.resPlastic << ' ' << playerData.resPower;
	savedData.close();
}

//Loads the Player Data from the file and writes it to the current Player struct
void LoadPlayerData() {
	Player playerData;
	ifstream savedData("PlayerSave.txt");
	savedData >> playerData.daysSurvived >> playerData.resMetal >> playerData.resPlastic >> playerData.resPower;
	savedData.close();
}


// argc and argv here are command line parameters passed to the program when running the program. 
// we won't actually use them but our 2D Graphics Library requires the main setup like this.
// Argc: the number of arguments pass
// argv[] : a char array of each of the params passed in ( each space is a new param)
int main( int argc, char *argv[] )
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;


	srand(time(NULL));

	Player playerData;
	InitializePlayerData();
	SavePlayerData();

	//Runs Automatically, Use Whenever Necessary
	ButtonMasher();


	//close off the SDL window
	SDL_Quit();

	
	return true;
}


//Loads Sprites & Button Masher Minigame
void ButtonMasher() {


	bool gameDone = false; //Win Condition


	//Initialization For Window
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Button Masher Minigame",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Surface* screen = SDL_GetWindowSurface(window);


	//Setting Background To White
	Uint32 white = SDL_MapRGB(screen->format, 255, 255, 255); 
	SDL_FillRect(screen, NULL, white);
	SDL_UpdateWindowSurface(window);


	//Position Of Button
	SDL_Rect button_pos;
	button_pos.w = 381;
	button_pos.h = 73;
	button_pos.y = 250;
	button_pos.x = 140;


	//Button (Unpushed) Sprite
	SDL_Surface* button_surface = NULL;
	SDL_Texture* button_texture = NULL;

	//Background Sprite
	SDL_Surface* background_surface = NULL;
	SDL_Texture* background_texture = NULL;

	//Button (Pushed) Sprite
	SDL_Surface* buttonpush_surface = NULL;
	SDL_Texture* buttonpush_texture = NULL;

	//Load BG Image
	background_surface = SDL_LoadBMP("background.bmp");
	background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);

	//Load Button (Unpushed) Image
	button_surface = SDL_LoadBMP("Button_NoPush.bmp");
	button_texture = SDL_CreateTextureFromSurface(renderer, button_surface);

	//Load Button (Pushed) Image
	buttonpush_surface = SDL_LoadBMP("Button_Push.bmp");
	buttonpush_texture = SDL_CreateTextureFromSurface(renderer, buttonpush_surface);
	
	//Amount Of Clicks.
	int buttonClicks = 0;

	//Implement Joystick Config Here
	while (gameDone == false)
	{
		if (1) //Change Value '1' To Button (A?) Pressed.
		{

			//Delay Can Be Updated For Faster Click-Rate
			SDL_Delay(100);


			//Changes Sprite To Pushed Button
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, background_texture, NULL, NULL);
			SDL_RenderCopy(renderer, buttonpush_texture, NULL, &button_pos);
			SDL_RenderPresent(renderer);


			buttonClicks++; //Increases Click Amount
		}

		
		//Delay Can Be Updated For Faster Click-Rate
		SDL_Delay(100); 




		//Process the score into a string and then a character
		//string dDisplayScore = to_string(buttonClicks);
		//const char* displayChar = dDisplayScore.c_str();
		//Display the score
		//Graphics::DrawText("Score:", 0, 0, 100, 50);
		//Graphics::DrawText(displayChar, 100, 0, 50, 50);



		//Changes Sprite To Unpushed Button
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background_texture, NULL, NULL);
		SDL_RenderCopy(renderer, button_texture, NULL, &button_pos);
		SDL_RenderPresent(renderer);


		//Win Condition
		if (buttonClicks >= 1000)
		{
			gameDone = true;
		}

	}
	

	//Delay Before Closing, Can Be Deleted.
	SDL_Delay(5000);


	//Cleanup
	SDL_DestroyTexture(button_texture);
	SDL_FreeSurface(button_surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
}
