#include "include/raylib.h"
#include "headers/board.h"
#include "headers/player.h"
#include "headers/winCondition.h"
#include <stdlib.h>
#include <stdbool.h>

bool pause = false;
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

	Texture2D nightBackgroundTexture = LoadTexture("images/background/night2.png");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawBoard(board, boardTexture, yellowPieceTexture, redPieceTexture);
		
		if (turn == 1)
			Play(player1, yellowPieceTexture, &board, boardTexture, highlitePieceTexture, &turn, &position, coinSound);
		
		else if (turn == 2)
			Play(player2, redPieceTexture, &board, boardTexture, highlitePieceTexture, &turn, &position, coinSound);

		if (CheckWin(board, player1, winnerPiecesCoordinates))
		{
			HighliteWinnerPieces(winnerPiecesCoordinates, highlitePieceTexture, boardTexture);
			DrawText("PLAYER 1 WINS", (GetScreenWidth() - MeasureText("PLAYER 1 WINS", 30)) / 2, 100, 30, BLACK);
		}
			
		if (CheckWin(board, player2, winnerPiecesCoordinates))
		{
			HighliteWinnerPieces(winnerPiecesCoordinates, highlitePieceTexture, boardTexture);
			DrawText("PLAYER 2 WINS", (GetScreenWidth() - MeasureText("PLAYER 2 WINS", 30)) / 2, 100, 30, BLACK);
		}

		EndDrawing();
	}

	UnloadTexture(boardTexture);
	UnloadTexture(yellowPieceTexture);
	UnloadTexture(redPieceTexture);

	UnloadTexture(nightBackgroundTexture);

	UnloadSound(coinSound);

	CloseAudioDevice();
	CloseWindow();
}
