#pragma once
#ifndef MODULE_H
#define MODULE_H
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Module
{
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	static const int SCREEN_WIDTH = 640;
	static const int SCREEN_HEIGHT = 480;
	int xMouse, yMouse;
	SDL_Color textColor, redColor;
	TTF_Font *font, *font2;
	bool GameRunning;
	bool Paused = 0;
	bool fullscreen;
	bool savedGameAvailable = 1;

	std::vector<std::pair<int, std::string>> highScores;

	SDL_Rect rScoreNum[5], rScoreName[5], rScoreValue[5];
	SDL_Texture *scoreNum[5], *scoreName[5], *scoreValue[5];
	
	SDL_Event event;

	Module();
	~Module();
	string HighestScoreInput(int);
	void StartNewGame();
	void StartMenu();
	bool ResumeMenu(SDL_Window *windowfromgame, SDL_Renderer *rendererfromgame);
	void HighestScoreMenu();
	void WinScreen();
	void SettingsMenu();
	void GoFullscreen();
	void GotoWindow();
	void Exit();
	void Pause();
	void Resume();
	void LoadMedia();
	void LoadSettingsMedia();
	void InstructionMenu();
	void LoadInstructionMedia();
	void DestroyInstructionMedia();
	void DestroySettingsMedia();
	void LoadScoreData();
	void AddHighScore(int x);
	void ClearScore();
	void LoadScoreMedia();
	void DestroyScoreMedia();
	void LoadResumeMedia();
	void DestroyResumeMedia();
	int HandleEnterinResume(int currentOption);
	void HandleArrowinResume(int currentOption);


	void DestroyMedia();
	SDL_Texture* LoadText(TTF_Font *font, const char *Text, SDL_Color color);
	SDL_Texture* woodback, *greenBack, *background, *background2, *playButton, *scoreButton, *settingsButton, *instructionsButton, *exitButton, *continueButton, *arrowIndicator, *gameTitle;
	SDL_Texture *settingsTitle, *highScoreTitle, *pausedTitle, *backfromScore, *resetScore, *instructionTitle;
	SDL_Texture *gamePaused, *resumeButton, *leaveGame, *saveandLeave, *resumeArrow;
	SDL_Texture *settingsBack, *fullscreenTitle, *fullscreenOn, *fullscreenOff;

	SDL_Texture *moveInstruction, *shootInstruction, *jumpInstruction, *pauseInstruction;
	SDL_Rect forMoveInstruction, forShootInstruction, forJumpInstruction, forPauseInstruction, forWoodBack;

	SDL_Texture *enemyKill, *coinCollection, *keyCollection, *backIns;
	SDL_Rect forEnemyKill, forCoinCollection, forKeyCollection, forBackIns;

	//SDL_Texture *howToPlay[5];
	SDL_Rect forScoreButton, forPlayButton, forInstuctionButton, forSettingsButton, forContinueButton, forExitButton, totalScreen, forArrowIndicator, backgroundSrcRect, forGameTitle, forScoreBack;
	SDL_Rect forSettingsTitle, forHighScoreTitle, forPausedTitle, forResetScore, forInstructionTilte;
	SDL_Rect forSettingsBack, forFullscreen, forFullscreenToggle;
	SDL_Rect forGamePaused, forResumeButton, forLeaveGame, forSaveAndLeave, forResumeArrow;
	SDL_Texture * LoadImage(const char* ImgName);
	int isContinue = 0;
	void HandleArrow(int currentOption);
	void HandleEnterKeyPress(int currentOption);
	//bool cmp(int a, int b);
	void CreateWindowRenderer();
	void DestroyWindowRenderer();
	bool isInside(int x, int y, SDL_Rect box);
	void AnimateBackground();
};

#endif

