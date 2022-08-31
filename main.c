#include "include/raylib.h"
#include "headers/floor.h"
#include "headers/board.h"
#include "headers/player.h"
#include "headers/winCondition.h"
#include "headers/button.h"
#include "headers/playAgain.h"
#include <stdlib.h>
#include <stdbool.h>

#define SCALE_FACTOR_TOP_RIGHT_BUTTONS 3.0
#define SCALE_FACTOR_BOARD_AND_PIECES 6.0

bool pause = false;
bool isSoundOn = true;
bool hasAPlayerWon = false;
int turn = 1;
int position = 0;

int winnerPiecesCoordinates[8] = {0, 0,
								  0, 0,
								  0, 0,
								  0, 0};

int main()
{
	int screenConstant = 300;
	InitWindow(4 * screenConstant, 3 * screenConstant, "Connect 4");

	SetTargetFPS(144);

	InitAudioDevice();

	Sound coinSound = LoadSound("sounds/coin.wav");

	Image iconImage = LoadImage("images/redPiece.png");
	SetWindowIcon(iconImage);

	Player player1;
	player1.id = 1;
	player1.numberOfPieces = 0;

	Player player2;
	player2.id = 2;
	player2.numberOfPieces = 0;

	Board board;
	ResetBoard(&board);
	Texture2D boardTexture = LoadTexture("images/board.png");

	Texture2D yellowPieceTexture = LoadTexture("images/yellowPiece.png");
	Texture2D redPieceTexture = LoadTexture("images/redPiece.png");
	Texture2D highlitePieceTexture = LoadTexture("images/highlitePiece.png");

	Texture2D dayBackgroundTexture = LoadTexture("images/background/day.png");

	Button volumeOnButton;
	Button volumeOffButton;
	Button exitGameButton;
	Button restartGameButton;

	volumeOnButton.texture = LoadTexture("images/buttons/buttonSoundOn.png");
	volumeOffButton.texture = LoadTexture("images/buttons/buttonSoundOff.png");
	exitGameButton.texture = LoadTexture("images/buttons/buttonExitGame.png");
	restartGameButton.texture = LoadTexture("images/buttons/buttonRestartGame.png");

	Button topRightButtons[3] = {exitGameButton,
								 volumeOffButton,
								 restartGameButton};

	Floor floor;
	floor.texture = LoadTexture("images/floor/floor.png");
	floor.x = 0;
	floor.y = GetScreenHeight() - floor.texture.height;

	Button playAgainButton;
	playAgainButton.texture = LoadTexture("images/buttons/buttonPlayAgain.png");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTextureEx(dayBackgroundTexture, (Vector2){0, 0}, 0, 1.0f, RAYWHITE);

		DrawTopRightButtons(topRightButtons, isSoundOn, &volumeOnButton);
		DrawBoard(board, boardTexture, yellowPieceTexture, redPieceTexture, floor);
		DrawFloor(floor);

		if (hasAPlayerWon == false)
		{
			if (turn == 1)
				Play(player1, yellowPieceTexture, &board, boardTexture, highlitePieceTexture, &turn, &position, coinSound, isSoundOn, floor);

			else if (turn == 2)
				Play(player2, redPieceTexture, &board, boardTexture, highlitePieceTexture, &turn, &position, coinSound, isSoundOn, floor);

			if (CheckWin(board, player1, winnerPiecesCoordinates))
			{
				hasAPlayerWon = true;
				HighliteWinnerPieces(winnerPiecesCoordinates, highlitePieceTexture, boardTexture, floor);
			}

			if (CheckWin(board, player2, winnerPiecesCoordinates))
			{
				hasAPlayerWon = true;
				HighliteWinnerPieces(winnerPiecesCoordinates, highlitePieceTexture, boardTexture, floor);
			}
		}

		else
		{
			HighliteWinnerPieces(winnerPiecesCoordinates, highlitePieceTexture, boardTexture, floor);
			DrawPlayAgainButton(&playAgainButton);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
				CheckCollisionPointRec(GetMousePosition(), GetPlayAgainButtonRec(playAgainButton, 4.0)))
			{
				hasAPlayerWon = false;
				ResetBoard(&board);
			}
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			CheckCollisionPointRec(GetMousePosition(), GetTopRightButtonRec(2, topRightButtons, SCALE_FACTOR_TOP_RIGHT_BUTTONS)) &&
			hasAPlayerWon == false)
		{
			ResetBoard(&board);
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			CheckCollisionPointRec(GetMousePosition(), GetTopRightButtonRec(1, topRightButtons, SCALE_FACTOR_TOP_RIGHT_BUTTONS)))
		{
			if (isSoundOn)
				isSoundOn = false;
			else
				isSoundOn = true;
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			CheckCollisionPointRec(GetMousePosition(), GetTopRightButtonRec(0, topRightButtons, SCALE_FACTOR_TOP_RIGHT_BUTTONS)))
		{
			CloseWindow();
			exit(1);
		}

		EndDrawing();
	}

	UnloadTexture(boardTexture);
	UnloadTexture(yellowPieceTexture);
	UnloadTexture(redPieceTexture);

	UnloadTexture(dayBackgroundTexture);

	UnloadTexture(floor.texture);
	UnloadTexture(playAgainButton.texture);

	UnloadSound(coinSound);

	CloseAudioDevice();
	CloseWindow();
}
