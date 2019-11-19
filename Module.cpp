#include "Module.h"
#include "game.h"


bool compareScores(pair<int, string> a, pair<int, string> b)
{
	return a.first > b.first;
}

Module::Module()
{
	fullscreen = 0;
}


Module::~Module()
{
	//DestroyWindowRenderer();
}

void Module::StartNewGame()
{
	//SDL_ShowCursor(SDL_DISABLE);
	game g(window, renderer, this);
	if(isContinue)
	{
		g.isContinue = 1;
	}
	else g.isContinue = 0;
	g.start();
	SDL_ShowCursor(SDL_ENABLE);
	return;
}

void Module::StartMenu()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	CreateWindowRenderer();
	
	GameRunning = 1;
	std::cout << "REX LOADING..." << endl;
	bool onceFlag = 1;
	int TotalOptions = 6;
	int currentOption = 0;
	while (GameRunning)
	{
		if(savedGameAvailable) TotalOptions = 6;
		else TotalOptions = 5;
		HandleArrow(currentOption);
		
		AnimateBackground();
		//std::cout << "MAIN MENU" << endl;
		SDL_RenderCopy(renderer, background, &backgroundSrcRect, NULL);
		SDL_RenderCopy(renderer, gameTitle, NULL, &forGameTitle);
		SDL_RenderCopy(renderer, scoreButton, NULL, &forScoreButton);
		SDL_RenderCopy(renderer, playButton, NULL, &forPlayButton);
		SDL_RenderCopy(renderer, settingsButton, NULL, &forSettingsButton);
		SDL_RenderCopy(renderer, arrowIndicator, NULL, &forArrowIndicator);
		SDL_RenderCopy(renderer, exitButton, NULL, &forExitButton);
		SDL_RenderCopy(renderer, instructionsButton, NULL, &forInstuctionButton);
		if(savedGameAvailable) SDL_RenderCopy(renderer, continueButton, NULL, &forContinueButton);
		SDL_RenderPresent(renderer);
		/*
		SDL_GetMouseState(&xMouse, &yMouse);
		if (isInside(xMouse, yMouse, totalScreen))SDL_ShowCursor(SDL_DISABLE);
		else SDL_ShowCursor(SDL_ENABLE);
		*/
		
		if (onceFlag)
		{
			std::cout << "0 - Start" << endl
				<< "1 - Highest Scores" << endl
				<< "2 - Settings" << endl
				<< "3 - Exit" << endl;
			onceFlag = 0;
			//if(currentOption == 4) cout << forArrowIndicator.y << endl;
			//else cout << currentOption << endl;
		}
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				GameRunning = false;
				DestroyWindowRenderer();
				break;
			case SDL_KEYDOWN:
				std::cout << "Keypress detected" << endl;
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
					isContinue = 0;
					StartNewGame();
					onceFlag = 1;
					break;
				case SDLK_s:
					SettingsMenu();
					onceFlag = true;
					break;
				case SDLK_h:
					HighestScoreMenu();
					onceFlag = true;
					break;
				case SDLK_ESCAPE:
					Exit();
					DestroyWindowRenderer();
					break;
				case SDLK_DOWN:
					currentOption++;
					currentOption %= TotalOptions;
					onceFlag = true;
					//cout << currentOption << endl;
					break;
				case SDLK_UP:
					currentOption--;
					currentOption += TotalOptions;
					currentOption %= TotalOptions;
					onceFlag = true;
					//cout << currentOption << endl;
					break;
				case SDLK_KP_ENTER:
					std::cout << "You Pressed Enter!" << endl;
					HandleEnterKeyPress(currentOption);
					onceFlag = 1;
					break;
				case SDLK_RETURN:
					std::cout << "You Pressed Enter!" << endl;
					HandleEnterKeyPress(currentOption);
					onceFlag = 1;
					break;
				case SDLK_p :
					savedGameAvailable = !savedGameAvailable;
					if(savedGameAvailable) TotalOptions = 6;
					else TotalOptions = 5;
					currentOption %= TotalOptions;
					HandleArrow(currentOption);
					cout << currentOption << endl;
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "Mouse Pressed" << endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				if(savedGameAvailable && isInside(xMouse, yMouse, forContinueButton))
				{
					isContinue = 1;

					StartNewGame();
					//cout << "HEllo " << endl;
				}
				else if (isInside(xMouse, yMouse, forScoreButton))
				{
					HighestScoreMenu();
					onceFlag = true;
				}
				else if(isInside(xMouse, yMouse, forInstuctionButton))
				{
					cout << "Instructions" << endl;
					InstructionMenu();
				}
				else if (isInside(xMouse, yMouse, forPlayButton))
				{
					isContinue = 0;
					StartNewGame();
					onceFlag = true;
				}
				else if (isInside(xMouse, yMouse, forSettingsButton))
				{
					SettingsMenu();
					onceFlag = true;
				}
				else if (isInside(xMouse, yMouse, forExitButton))
				{
					Exit();
					DestroyWindowRenderer();
				}
				break;
			case SDL_MOUSEMOTION:
				//std::cout << "MOUSE MOVED" << endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				if( savedGameAvailable && isInside(xMouse, yMouse, forContinueButton))
				{
					currentOption = 5;
				}
				if (isInside(xMouse, yMouse, forScoreButton))
				{
					currentOption = 2;
				}
				if (isInside(xMouse, yMouse, forInstuctionButton))
				{
					currentOption = 1;
				}
				else if (isInside(xMouse, yMouse, forPlayButton))
				{
					currentOption = 0;
				}
				else if (isInside(xMouse, yMouse, forSettingsButton))
				{
					currentOption = 3;
				}
				else if (isInside(xMouse, yMouse, forExitButton))
				{
					currentOption = 4;
				}
				break;
			}
		}
	}
		
		/*
		int InputOption;
		std::cin >> InputOption;
		switch (InputOption)
		{
		case 0:
			StartNewGame();
			break;
		case 1:
			HighestScoreMenu();
			break;
		case 2:
			SettingsMenu();
			break;
		case 3:
			Exit();
			DestroyWindowRenderer();
			break;
		default:
			break;
		}
		
		*/
	DestroyWindowRenderer();
}

bool Module::ResumeMenu(SDL_Window *windowfromgame, SDL_Renderer *rendererfromgame)
{
	window = windowfromgame; renderer = rendererfromgame;
	TTF_Init();
	SDL_ShowCursor(SDL_ENABLE);
	Paused = 1;
	int TotalOptions = 2;
	int currentOption = 0;
	bool onceFlag = 1;
	bool returnValue;
	LoadMedia();
	LoadResumeMedia();
	while (Paused)
	{
		HandleArrowinResume(currentOption);
		AnimateBackground();
		SDL_RenderCopy(renderer, background, &backgroundSrcRect, NULL);
		SDL_RenderCopy(renderer, gamePaused, NULL, &forGamePaused);
		SDL_RenderCopy(renderer, resumeButton, NULL, &forResumeButton);
		SDL_RenderCopy(renderer, leaveGame, NULL, &forLeaveGame);
		SDL_RenderCopy(renderer, resumeArrow, NULL, &forResumeArrow);
		//SDL_RenderCopy(renderer, saveandLeave, NULL, &forSaveAndLeave);
		SDL_RenderPresent(renderer);
		if (onceFlag) {
			std::cout << "You paused the game!" << endl
				<< "Press space to resume." << endl
				<< "Press escape to Quit." << endl;
			onceFlag = false;
		}
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				Resume();
				returnValue = 0;
				Exit();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
					Resume();
					returnValue = 1;
					break;
				case SDLK_ESCAPE:
					Resume();
					returnValue = 0;
					break;
				case SDLK_UP:
					currentOption--;
					currentOption += TotalOptions;
					currentOption %= TotalOptions;
					break;
				case SDLK_DOWN:
					currentOption++;
					currentOption %= TotalOptions;
					break;
				case SDLK_RETURN:
					returnValue = HandleEnterinResume(currentOption);
					break;
				case SDLK_KP_ENTER:
					returnValue = HandleEnterinResume(currentOption);
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "Mouse Pressed" << endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				if (isInside(xMouse, yMouse, forResumeButton))
				{
					Resume();
					returnValue = 1;
				}
				else if (isInside(xMouse, yMouse, forLeaveGame))
				{
					Resume();
					returnValue = 0;
				}
				/*
				else if (isInside(xMouse, yMouse, forSaveAndLeave))
				{
					Resume();
					returnValue = 0;
				}
				*/
				break;
			case SDL_MOUSEMOTION:
				//std::cout << "MOUSE MOVED" << endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				if (isInside(xMouse, yMouse, forResumeButton))
				{
					currentOption = 0;
				}
				else if (isInside(xMouse, yMouse, forLeaveGame))
				{
					currentOption = 1;
				}
				break;
			}
		}
		/*
		int Input;
		std::cin >> Input;
		if (Input == 0) {
			Resume(); returnValue = 1;
		}
		else if (Input == 1)
		{
			Resume();
			returnValue = 0;
		}
		*/
	}
	DestroyResumeMedia();
	DestroyMedia();
	SDL_ShowCursor(SDL_DISABLE);
	return returnValue;
}
void Module::InstructionMenu()
{
	
	///HighestScoreInput(500);
	bool inInstructionMenu = 1;
	bool onceFlag = true;
	LoadInstructionMedia();
	while (inInstructionMenu)
	{
		AnimateBackground();
		SDL_RenderCopy(renderer, background, &backgroundSrcRect, NULL);
		SDL_RenderCopy(renderer, woodback, NULL, &forWoodBack);
		SDL_RenderCopy(renderer, instructionTitle, NULL, &forInstructionTilte);
		SDL_RenderCopy(renderer, moveInstruction, NULL, &forMoveInstruction);
		SDL_RenderCopy(renderer, jumpInstruction, NULL, &forJumpInstruction);
		SDL_RenderCopy(renderer, shootInstruction, NULL, &forShootInstruction);
		SDL_RenderCopy(renderer, pauseInstruction, NULL, &forPauseInstruction);
		SDL_RenderCopy(renderer, enemyKill, NULL, &forEnemyKill);
		SDL_RenderCopy(renderer, coinCollection, NULL, &forCoinCollection);
		SDL_RenderCopy(renderer, keyCollection, NULL, &forKeyCollection);
		SDL_RenderCopy(renderer, backIns, NULL, &forBackIns);
		//SDL_RenderCopy(renderer, backfromScore, NULL, &forScoreBack);
		//SDL_RenderCopy(renderer, resetScore, NULL, &forResetScore);

		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				Exit();
				inInstructionMenu = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					inInstructionMenu = false;
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "Mouse Pressed" << endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				if (isInside(xMouse, yMouse, forBackIns))
				{
					inInstructionMenu = false;
				}
				break;
			}

		}
	}
	DestroyInstructionMedia();
}
void Module::LoadInstructionMedia()
{
	instructionTitle = LoadText(font, "Instructions", redColor);
	//forInstructionTilte = forHighScoreTitle;

	forInstructionTilte.x = 180;
	forInstructionTilte.y = 20;
	forInstructionTilte.w = 260;
	forInstructionTilte.h = 70;

	SDL_Color textColor = { 0, 0, 0 };

	char ins1[100] = "Press LEFT or RIGHT to move horizontally.";
	moveInstruction = LoadText(font2, ins1, textColor);

	forMoveInstruction.x = 60;
	forMoveInstruction.y = 100;
	forMoveInstruction.w = strlen(ins1) * 13;
	forMoveInstruction.h = 32;

	char ins2[100] = "Press SPACE or UP to jump.";
	jumpInstruction = LoadText(font2, ins2, textColor);

	forJumpInstruction.x = forMoveInstruction.x;
	forJumpInstruction.y = forMoveInstruction.y + 40;
	forJumpInstruction.w = strlen(ins2) * 13;
	forJumpInstruction.h = forMoveInstruction.h;

	char ins3[100] = "Press F to shoot and kill enimies.";

	shootInstruction = LoadText(font2, ins3, textColor);

	forShootInstruction.x = forMoveInstruction.x;
	forShootInstruction.y = forJumpInstruction.y + 40;
	forShootInstruction.w = strlen(ins3) * 13;
	forShootInstruction.h = forMoveInstruction.h;

	char ins4[100] = "Press ESC to pause game.";

	pauseInstruction = LoadText(font2, ins4, textColor);

	forPauseInstruction.x = forMoveInstruction.x;
	forPauseInstruction.y = forShootInstruction.y + 40;
	forPauseInstruction.w = strlen(ins4) * 13;
	forPauseInstruction.h = forMoveInstruction.h;

	char ins5[100] = "Kill an enemy to score 100 points.";
	char ins6[100] = "Collect a coin to score 10 points.";
	char ins7[100] = "Collect the key to go to the next level.";

	enemyKill = LoadText(font2, ins5, textColor);
	coinCollection = LoadText(font2, ins6, textColor);
	keyCollection = LoadText(font2, ins7, textColor);

	forEnemyKill.x = forMoveInstruction.x;
	forEnemyKill.y = forPauseInstruction.y + 40;
	forEnemyKill.w = strlen(ins5) * 13;
	forEnemyKill.h = forMoveInstruction.h;

	forCoinCollection.x = forMoveInstruction.x;
	forCoinCollection.y = forEnemyKill.y + 40;
	forCoinCollection.w = strlen(ins6) * 13;
	forCoinCollection.h = forMoveInstruction.h;

	forKeyCollection.x = forMoveInstruction.x;
	forKeyCollection.y = forCoinCollection.y + 40;
	forKeyCollection.w = strlen(ins7) * 13;
	forKeyCollection.h = forMoveInstruction.h;

	backIns = LoadText(font, "BACK", textColor);
	forBackIns.x = SCREEN_WIDTH - 110;
	forBackIns.h = 40;
	forBackIns.w = 90;
	forBackIns.y = 20;

	forWoodBack.x = 40;
	forWoodBack.y = forInstructionTilte.y + forInstructionTilte.h + 2;
	forWoodBack.w = SCREEN_WIDTH - 80;
	forWoodBack.h = forKeyCollection.y + 40 - forWoodBack.y;
}

void Module::DestroyInstructionMedia()
{
	SDL_DestroyTexture(instructionTitle);
	SDL_DestroyTexture(moveInstruction);
	SDL_DestroyTexture(jumpInstruction);
	SDL_DestroyTexture(shootInstruction);
	SDL_DestroyTexture(pauseInstruction);
	SDL_DestroyTexture(enemyKill);
	SDL_DestroyTexture(coinCollection);
	SDL_DestroyTexture(keyCollection);
	SDL_DestroyTexture(backIns);
}
void Module::HighestScoreMenu()
{
	///HighestScoreInput(500);
	bool inHighScoreMenu = 1;
	bool onceFlag = true;
	LoadScoreMedia();
	while (inHighScoreMenu)
	{
		AnimateBackground();
		SDL_RenderCopy(renderer, background, &backgroundSrcRect, NULL);
		SDL_RenderCopy(renderer, woodback, NULL, &forWoodBack);
		SDL_RenderCopy(renderer, highScoreTitle, NULL, &forHighScoreTitle);
		SDL_RenderCopy(renderer, backfromScore, NULL, &forScoreBack);
		SDL_RenderCopy(renderer, resetScore, NULL, &forResetScore);
		if (onceFlag) {
			std::cout << "You entered Highest Score Menu!" << endl;
			LoadScoreData();
			std::cout << "Press Escape to return to main menu." << endl;
			onceFlag = false;
		}
		for (int i = 0; i < 5; i++)
		{
			//std::cout << "Rendering Numbers" << endl;
			SDL_RenderCopy(renderer, scoreNum[i], NULL, &rScoreNum[i]);
			SDL_RenderCopy(renderer, scoreName[i], NULL, &rScoreName[i]);
			SDL_RenderCopy(renderer, scoreValue[i], NULL, &rScoreValue[i]);
		}
		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				Exit();
				inHighScoreMenu = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					inHighScoreMenu = false;
					break;
				case SDLK_c:
					ClearScore();
					LoadScoreData();
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "Mouse Pressed" << endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				if (isInside(xMouse, yMouse, forScoreBack))
				{
					inHighScoreMenu = false;
				}
				else if (isInside(xMouse, yMouse, forResetScore))
				{
					ClearScore(); LoadScoreData();
				}
				break;
			}

		}
	}
	DestroyScoreMedia();
}

void Module::SettingsMenu()
{
	bool inSettingsMenu = 1;
	bool onceFlag = true;
	LoadSettingsMedia();
	while (inSettingsMenu)
	{
		AnimateBackground();
		SDL_RenderCopy(renderer, background, &backgroundSrcRect, NULL);
		SDL_RenderCopy(renderer, settingsTitle, NULL, &forSettingsTitle);
		SDL_RenderCopy(renderer, settingsBack, NULL, &forSettingsBack);
		SDL_RenderCopy(renderer, fullscreenTitle, NULL, &forFullscreen);
		SDL_RenderCopy(renderer, fullscreen ? fullscreenOn : fullscreenOff, NULL, &forFullscreenToggle);
		SDL_RenderPresent(renderer);
		if (onceFlag)
		{
			std::cout << "You entered Settings Menu!" << endl
				<< "Press Space to switch fullscreen" << endl
				<< "Press Escape to return to main menu." << endl;
			onceFlag = false;
		}
		while (SDL_PollEvent(&event) && event.key.repeat == 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				Exit();
				inSettingsMenu = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					inSettingsMenu = false;
					break;
				case SDLK_SPACE:
					if (!fullscreen) GoFullscreen();
					else GotoWindow();
					DestroySettingsMedia();
					LoadSettingsMedia();
					//inSettingsMenu = false;
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "Mouse Pressed" << endl;
				SDL_GetMouseState(&xMouse, &yMouse);
				if (isInside(xMouse, yMouse, forSettingsBack))
				{
					inSettingsMenu = false;
				}
				else if (isInside(xMouse, yMouse, forFullscreenToggle))
				{
					if (!fullscreen) GoFullscreen();
					else GotoWindow();
					DestroySettingsMedia();
					LoadSettingsMedia();
					//inSettingsMenu = false;
				}
				break;
			}
		}
		/*
		int Input;
		std::cin >> Input;
		if (Input == 0) inSettingsMenu = 0;
		else if(Input == 1) {
			if (!fullscreen) GoFullscreen();
			else GotoWindow();
		}
		*/
	}
	DestroySettingsMedia();
}

void Module::GoFullscreen()
{
	fullscreen = 1;
	DestroyWindowRenderer();
	CreateWindowRenderer();
}

void Module::GotoWindow()
{
	fullscreen = 0;
	DestroyWindowRenderer();
	CreateWindowRenderer();
}

void Module::Exit()
{
	GameRunning = 0;
}

void Module::Pause()
{
	Paused = 1;
}

void Module::Resume()
{
	Paused = 0;
}

void Module::LoadMedia()
{
	//font = TTF_OpenFont("ARCADE.TTF", 150);
	font = TTF_OpenFont("Okay.ttf", 150);
	font2 = TTF_OpenFont("Arial.ttf", 150);
	textColor = { 255,165,0 };
	redColor = { 255,0,0 };

	//totalScreen

	background = LoadImage("mario.png");

	totalScreen.x = 0;
	totalScreen.y = 0;
	totalScreen.w = SCREEN_WIDTH;
	totalScreen.h = SCREEN_HEIGHT;

	//background animation
	backgroundSrcRect.x = 0;
	backgroundSrcRect.y = 0;
	backgroundSrcRect.w = 1300;
	backgroundSrcRect.h = 975;

	//for Title

	gameTitle = LoadText(font, "REX", redColor);

	forGameTitle.x = 250;
	forGameTitle.y = 20;
	forGameTitle.w = 150;
	forGameTitle.h = 85;
	//forPlayButton
	/*
	playButton = LoadImage("PlayButton.png");

	forPlayButton.x = 80;
	forPlayButton.y = 300;
	forPlayButton.w = 100;
	forPlayButton.h = 100;
	*/

	continueButton = LoadText(font, "Continue", textColor);

	forContinueButton.x = 45;
	forContinueButton.y = 100;
	forContinueButton.w = 200;
	forContinueButton.h = 45;

	playButton = LoadText(font, "New Game", textColor);

	forPlayButton.x = 45;
	forPlayButton.y = forContinueButton.y + 55;
	forPlayButton.w = 200;
	forPlayButton.h = 45;

	instructionsButton = LoadText(font, "Instructions", textColor);
	
	forInstuctionButton.x = 45;
	forInstuctionButton.y = forPlayButton.y + 55;
	forInstuctionButton.w = 220;
	forInstuctionButton.h = 45;




	//forScoreButton
	/*
	scoreButton = LoadImage("HighestScore.png");
	
	forScoreButton.x = 520;
	forScoreButton.y = 0;
	forScoreButton.h = 80;
	forScoreButton.w = 120;
	*/
	scoreButton = LoadText(font, "Highest Scores", textColor);

	forScoreButton.x = forPlayButton.x;
	forScoreButton.y = forInstuctionButton.y + 55;
	forScoreButton.h = forPlayButton.h;
	forScoreButton.w = 280;
	
	
	//forSettingsButton
	settingsButton = LoadText(font, "Settings", textColor);

	forSettingsButton.x = forPlayButton.x;
	forSettingsButton.y = forScoreButton.y + 55;
	forSettingsButton.w = 180;
	forSettingsButton.h = forPlayButton.h;

	//forExitButton

	exitButton = LoadText(font, "Quit", textColor);

	forExitButton.x = forPlayButton.x;
	forExitButton.y = forSettingsButton.y + 55;
	forExitButton.h = forPlayButton.h;
	forExitButton.w = 95;

	//forArrow
	//arrowIndicator = LoadImage("Arrow.png");
	arrowIndicator = LoadText(font, " >>", redColor);

	forArrowIndicator.x = 0;
	forArrowIndicator.y = forContinueButton.y;
	forArrowIndicator.w = 33;
	forArrowIndicator.h = 45;

	//wood
	woodback = LoadImage("wood-back.png");
	greenBack = LoadImage("Green.png");

}

void Module::LoadSettingsMedia()
{
	//title
	settingsTitle = LoadText(font, "Settings", redColor);

	forSettingsTitle.x = 250;
	forSettingsTitle.y = 20;
	forSettingsTitle.w = 140;
	forSettingsTitle.h = 70;

	//Back Button
	settingsBack = LoadText(font, "BACK", textColor);

	forSettingsBack.x = SCREEN_WIDTH - 110;
	forSettingsBack.h = 40;
	forSettingsBack.w = 90;
	forSettingsBack.y = 20;

	//Fullscreen
	fullscreenTitle = LoadText(font, "Fullscreen", textColor);

	forFullscreen.x = 130;
	forFullscreen.y = 90;
	forFullscreen.w = 140;
	forFullscreen.h = 45;

	//toggleButton

	fullscreenOff = LoadText(font, "OFF", textColor);
	fullscreenOn = LoadText(font, " ON", redColor);

	forFullscreenToggle.x = 400;
	forFullscreenToggle.y = forFullscreen.y;
	forFullscreenToggle.w = 80;
	forFullscreenToggle.h = forFullscreen.h;
}

void Module::DestroySettingsMedia()
{
	SDL_DestroyTexture(settingsTitle);
	SDL_DestroyTexture(settingsBack);
	SDL_DestroyTexture(fullscreenTitle);
	SDL_DestroyTexture(fullscreenOn);
	SDL_DestroyTexture(fullscreenOff);
}

void Module::LoadScoreData()
{
	//Loading DATA
	highScores.clear();
	int Input;
	FILE* ScoreFile = fopen("HighestScores.dat", "r");
	int num;
	char playerName[100];
	while (fscanf(ScoreFile, "%d %s", &num, playerName) != EOF)
	{
		pair<int, string> thisInput;
		thisInput.first = num;
		string thisName = playerName;
		thisInput.second = thisName;

		highScores.push_back(thisInput);
	}
	
	cout << "Eee" << endl;
	fclose(ScoreFile);
	while (highScores.size() < 10)
	{
		highScores.push_back(make_pair(0, "N/A"));
	}
	std::sort(highScores.begin(), highScores.end(), compareScores);
	for (int i = 0; i < 5; i++)
	{
		std::cout << i + 1 << ".\t" << highScores[i].second << "\t" << highScores[i].first << endl;
	}
	SDL_Color textColor = { 0,0,0 };
	//Loading Texture
	for (int i = 0; i < 5; i++)
	{
		string s = highScores[i].second;
		int value = highScores[i].first;
		char nameP[100],name[100];
		strcpy(nameP,s.c_str());
		sprintf(name, "%-7s", nameP);
		
		char num[100]; sprintf(num, "%5d", value);
		printf("%s\n", num);
		scoreName[i] = LoadText(font, name, textColor);
		scoreValue[i] = LoadText(font, num, textColor);
	}
}

void Module::WinScreen()
{
	bool quit = false;
	SDL_Texture* Win = LoadText(font, "You Win", textColor);
	SDL_Rect rect = { 250, 220, 140, 40 };
	SDL_Rect bRect = { 240, 210, 160, 60 };
	int start = SDL_GetTicks(), now;
	while (!quit)
	{
		cout << "HERE" << endl;
		AnimateBackground();
		SDL_RenderCopy(renderer, background, &backgroundSrcRect, NULL);
		SDL_RenderCopy(renderer, greenBack, NULL, &bRect);
		SDL_RenderCopy(renderer, Win, NULL, &rect);
		SDL_RenderPresent(renderer);
		now = SDL_GetTicks();
		if (now - start > 3000) quit = true;
	}
	SDL_DestroyTexture(Win);
}

void Module::ClearScore()
{
	FILE *scoreFile = fopen("HighestScores.dat", "w");
	fclose(scoreFile);
}

void Module::LoadScoreMedia()
{
	//Score Title

	SDL_Color blackColor = { 0,0,0 };

	highScoreTitle = LoadText(font, "Highest Scores", redColor);

	forHighScoreTitle.x = 180;
	forHighScoreTitle.y = 20;
	forHighScoreTitle.w = 260;
	forHighScoreTitle.h = 50;


	//Loading Numbers

	for (int i = 1; i <= 5; i++)
	{
		char s[100];
		sprintf(s, "%d.", i);
		scoreNum[i - 1] = LoadText(font, s, blackColor);
	}

	//Loading Rectangles
	rScoreNum[0].x = 130;
	rScoreNum[0].y = 90;
	rScoreNum[0].w = 40;
	rScoreNum[0].h = 36;

	for (int i = 1; i < 5; i++)
	{
		rScoreNum[i].x = rScoreNum[i - 1].x;
		rScoreNum[i].y = rScoreNum[i - 1].y + 45;
		rScoreNum[i].w = rScoreNum[i - 1].w;
		rScoreNum[i].h = rScoreNum[i - 1].h;
	}

	rScoreName[0].x = rScoreNum[0].x + 80;
	rScoreName[0].y = rScoreNum[0].y;
	rScoreName[0].w = 120;
	rScoreName[0].h = rScoreNum[0].h;

	for (int i = 1; i < 5; i++)
	{
		rScoreName[i].x = rScoreName[i - 1].x;
		rScoreName[i].y = rScoreName[i - 1].y + 45;
		rScoreName[i].w = rScoreName[i - 1].w;
		rScoreName[i].h = rScoreName[i - 1].h;
	}

	rScoreValue[0].x = rScoreName[0].x + 150;
	rScoreValue[0].y = rScoreName[0].y;
	rScoreValue[0].w = rScoreName[0].w;
	rScoreValue[0].h = rScoreName[0].h;

	for (int i = 1; i < 5; i++)
	{
		rScoreValue[i].x = rScoreValue[i - 1].x;
		rScoreValue[i].y = rScoreValue[i - 1].y + 45;
		rScoreValue[i].w = rScoreValue[i - 1].w;
		rScoreValue[i].h = rScoreValue[i - 1].h;
	}

	//BackButton

	backfromScore = LoadText(font, "BACK", textColor);
	forScoreBack.x = SCREEN_WIDTH - 110;
	forScoreBack.h = 40;
	forScoreBack.w = 90;
	forScoreBack.y = 20;

	//resetButton

	resetScore = LoadText(font, "RESET", redColor);
	forResetScore.x = rScoreNum[4].x;
	forResetScore.y = rScoreName[4].y + 50;
	forResetScore.w = 110;
	forResetScore.h = rScoreName[4].h + 10;

	forWoodBack.x = rScoreNum[0].x - 30;
	forWoodBack.y = rScoreNum[0].y - 15;
	forWoodBack.w = 400;
	forWoodBack.h = 290;

}

void Module::DestroyScoreMedia()
{
	SDL_DestroyTexture(highScoreTitle);
	SDL_DestroyTexture(backfromScore);
	SDL_DestroyTexture(resetScore);
	for (int i = 0; i < 5; i++)
	{
		SDL_DestroyTexture(scoreNum[i]);
		SDL_DestroyTexture(scoreValue[i]);
		SDL_DestroyTexture(scoreName[i]);
	}
}

void Module::LoadResumeMedia()
{
	//gamePaused
	gamePaused = LoadText(font, "Game Paused", redColor);

	forGamePaused.x = 180;
	forGamePaused.y = 80;
	forGamePaused.w = 260;
	forGamePaused.h = 70;

	//SDL_RenderCopy(renderer, gamePaused, NULL, &forGamePaused);

	//resumeButton
	resumeButton = LoadText(font, "Resume", textColor);

	forResumeButton.x = 45;
	forResumeButton.y = 180;
	forResumeButton.w = 140;
	forResumeButton.h = 45;

	//leaveGame
	leaveGame = LoadText(font, "Leave", textColor);
	
	forLeaveGame.x = forResumeButton.x;
	forLeaveGame.y = forResumeButton.y + 55;
	forLeaveGame.w = 120;
	forLeaveGame.h = forResumeButton.h;

	//Save and Leave

	saveandLeave = LoadText(font, "Save and Leave", textColor);

	forSaveAndLeave.x = forLeaveGame.x;
	forSaveAndLeave.y = forLeaveGame.y + 55;
	forSaveAndLeave.w = 310;
	forSaveAndLeave.h = forLeaveGame.h;

	//arrow

	resumeArrow = LoadText(font, " >>", redColor);

	forResumeArrow.x = 0;
	forResumeArrow.y = forResumeButton.y;
	forResumeArrow.w = 33;
	forResumeArrow.h = 45;
}

void Module::DestroyResumeMedia()
{
	SDL_DestroyTexture(gamePaused);
	SDL_DestroyTexture(resumeButton);
	SDL_DestroyTexture(leaveGame);
	SDL_DestroyTexture(saveandLeave);
	SDL_DestroyTexture(resumeArrow);
}

int Module::HandleEnterinResume(int currentOption)
{
	switch (currentOption)
	{
	case 0:
		Resume();
		return 1;
		break;
	case 1:
		Resume();
		return 0;
		break;
	default:
		break;
	}
	return 1;
}

void Module::HandleArrowinResume(int currentOption)
{
	if (currentOption == 0) forResumeArrow.y = forResumeButton.y;
	else if (currentOption == 1) forResumeArrow.y = forLeaveGame.y;
}

void Module::DestroyMedia()
{
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(scoreButton);
	SDL_DestroyTexture(playButton);
	SDL_DestroyTexture(exitButton);
	SDL_DestroyTexture(settingsButton);
	SDL_DestroyTexture(arrowIndicator);
	SDL_DestroyTexture(gameTitle);
	SDL_DestroyTexture(instructionsButton);
	SDL_DestroyTexture(woodback);
	SDL_DestroyTexture(greenBack);
}

SDL_Texture * Module::LoadText(TTF_Font * font, const char * Text, SDL_Color color)
{
	SDL_Surface* tmp = TTF_RenderText_Solid(font, Text, color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}

SDL_Texture * Module::LoadImage(const char * ImgName)
{
	SDL_Surface* tmp = IMG_Load(ImgName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
	SDL_FreeSurface(tmp);
	return tex;
}

void Module::HandleArrow(int currentOption)
{
	//cout << currentOption << endl;
	switch (currentOption)
	{
	case 5:
		forArrowIndicator.y = forContinueButton.y;
		break;
	case 0:
		forArrowIndicator.y = forPlayButton.y;
		break;
	case 1:
		forArrowIndicator.y = forInstuctionButton.y;
		break;
	case 2:
		forArrowIndicator.y = forScoreButton.y;
		break;
	case 3:
		forArrowIndicator.y = forSettingsButton.y;
		break;
	case 4:
		forArrowIndicator.y = forExitButton.y;
		break;
	default:
		break;
	}
}

void DeleteSaved()
{
	ofstream out("GameSave.dat");
	out << -1 << endl;
	out.close();
}

void Module::HandleEnterKeyPress(int currentOption)
{
	switch (currentOption)
	{
	case 0 :
		//DeleteSaved();
		isContinue = 0;
		StartNewGame();
		break;
	case 1 :
		InstructionMenu();
		break;
	case 2 :
		HighestScoreMenu();
		break;
	case 3 :
		SettingsMenu();
		break;
	case 4:
		Exit();
		break;
	case 5:
		isContinue = 1;
		StartNewGame();
		//cout << "HEllo " << endl;
		break;
	}
}

void Module::CreateWindowRenderer()
{
	if(!fullscreen) window = SDL_CreateWindow("REX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	else window = SDL_CreateWindow("REX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, fullscreen);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	LoadMedia();
}

void Module::DestroyWindowRenderer()
{
	DestroyMedia();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

bool Module::isInside(int x, int y, SDL_Rect box)
{
	if (x < box.x) return false;
	if (x > box.x + box.w) return false;
	if (y < box.y) return false;
	if (y > box.y + box.h) return false;
	return true;
}

void Module::AnimateBackground()
{
	static bool up = 0;
	static double y = 0.0;
	static double x = 60.0;
	static bool right = 1;
	if (right) x += 0.04;
	else x -= 0.04;
	if(!up) y += 0.02;
	else y -= 0.02;
	if (y >= 40) up = 1;
	else if (y <= 0) up = 0;
	if (x >= 150) right = 0;
	else if (x <= 0) right = 1;
	backgroundSrcRect.y = y;
	backgroundSrcRect.x = x;
}

void Module::AddHighScore(int x)
{
	FILE *scoreFile = fopen("HighestScores.dat", "a");
	fprintf(scoreFile, "%d MRIDUL\n", x);
	fclose(scoreFile);
}

string Module::HighestScoreInput(int x)
{
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( renderer );
	//cout << "HELLO " << endl;

	SDL_StartTextInput();
	string inputText;

	bool inputTaken = false;
	char scoreValue[100];
	sprintf(scoreValue, "Your Score: %6d", x);
	SDL_Texture* textureR = NULL;
	SDL_Texture* YourScore = LoadText(font, scoreValue, { 200,200,0 });
	SDL_Texture* InputRequired = LoadText(font, "Please Enter Your Name: ", {200, 200, 0});
	SDL_Rect dest2 = {50, 200, 540, 50};
	SDL_Rect dest3 = { 110, 100, 420, 50 };

	while( !inputTaken )
	{
		//SDL_RenderPresent(renderer);
		bool renderText = false;

		while( SDL_PollEvent( &event ) != 0 )
		{
			if( event.type == SDL_QUIT )
			{
				inputTaken = true;
			}
			
			else if( event.type == SDL_KEYDOWN )
			{
				if((event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_SPACE) && inputText.length() > 0)
				{
					inputTaken = true;
				}
				if( event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
				{
					inputText.pop_back();
					renderText = true;
				}
				
				else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
				{
					SDL_SetClipboardText( inputText.c_str() );
				}
				
				else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
				{
					inputText = SDL_GetClipboardText();
					renderText = true;
				}
			}
			//Special text input event
			else if( event.type == SDL_TEXTINPUT )
			{
				//Not copy or pasting
				if( !( SDL_GetModState() & KMOD_CTRL && ( event.text.text[ 0 ] == 'c' || event.text.text[ 0 ] == 'C' || event.text.text[ 0 ] == 'v' || event.text.text[ 0 ] == 'V' ) ) )
				{
					//Append character
					inputText += event.text.text;
					renderText = true;
				}
			}
		}

		if( renderText )
		{
			if( inputText != "" )
			{
				//gInputTextTexture.loadFromRenderedText( inputText.c_str(), textColor );
				textureR = LoadText(font, inputText.c_str(), {0, 255, 0});
			}
			else
			{
				
				//gInputTextTexture.loadFromRenderedText( " ", textColor );
				textureR = LoadText(font, " ", {0, 255, 0});
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0xFF );
		SDL_RenderClear( renderer );
		SDL_RenderCopy(renderer, InputRequired, NULL, &dest2);
		SDL_RenderCopy(renderer, YourScore, NULL, &dest3);

		//Render text textures
		SDL_Rect dest = {200, 300, inputText.length() * 40, 50};
		SDL_RenderCopy(renderer, textureR, NULL, &dest);
		//gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0 );
		//gInputTextTexture.render( ( SCREEN_WIDTH - gInputTextTexture.getWidth() ) / 2, gPromptTextTexture.getHeight() );

		//Update screen
		SDL_RenderPresent( renderer );
	}

	cout << inputText << endl;
	FILE *scoreFile = fopen("HighestScores.dat", "a");
	fprintf(scoreFile, "%d %s\n", x, inputText.c_str());
	fclose(scoreFile);

	return inputText;
	
}


/*
bool Module::cmp(int a, int b)
{
	return a > b;
} */
