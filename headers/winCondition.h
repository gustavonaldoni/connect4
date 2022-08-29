void AddWinnerPieceToList(int i, int j, int winnerPiecesCoordinates[], int position)
{
    winnerPiecesCoordinates[position] = i;
    winnerPiecesCoordinates[position + 1] = j;
}

void HighliteWinnerPieces(int winnerPiecesCoordinates[], Texture2D highlitePieceTexture, Texture2D boardTexture)
{
    int space;
    int boardX, boardY;
    int x, y;
    int x1, y1, x2, y2, x3, y3, x4, y4;
    float scaleFactor;

    space = 5;
    scaleFactor = 6;

    boardX = GetBoardX(boardTexture, scaleFactor);
    boardY = GetBoardY(boardTexture, scaleFactor);

    x = boardX + (space * scaleFactor);
    y = boardY + (space * scaleFactor);

    x1 = x + (space + 9) * scaleFactor * winnerPiecesCoordinates[1];
    y1 = y + (space + 9) * scaleFactor * winnerPiecesCoordinates[0];

    x2 = x + (space + 9) * scaleFactor * winnerPiecesCoordinates[3];
    y2 = y + (space + 9) * scaleFactor * winnerPiecesCoordinates[2];

    x3 = x + (space + 9) * scaleFactor * winnerPiecesCoordinates[5];
    y3 = y + (space + 9) * scaleFactor * winnerPiecesCoordinates[4];

    x4 = x + (space + 9) * scaleFactor * winnerPiecesCoordinates[7];
    y4 = y + (space + 9) * scaleFactor * winnerPiecesCoordinates[6];

    DrawTextureEx(highlitePieceTexture, (Vector2){x1, y1}, 0, scaleFactor, RAYWHITE);
    DrawTextureEx(highlitePieceTexture, (Vector2){x2, y2}, 0, scaleFactor, RAYWHITE);
    DrawTextureEx(highlitePieceTexture, (Vector2){x3, y3}, 0, scaleFactor, RAYWHITE);
    DrawTextureEx(highlitePieceTexture, (Vector2){x4, y4}, 0, scaleFactor, RAYWHITE);

}

bool CheckWin(Board board, Player player, int winnerPiecesCoordinates[])
{
    int i, j;

    // Check horizontal win
    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (board.canvas[i][j] == board.canvas[i][j + 1] &&
                board.canvas[i][j + 1] == board.canvas[i][j + 2] &&
                board.canvas[i][j + 2] == board.canvas[i][j + 3] &&
                board.canvas[i][j] == player.id)
            {
                AddWinnerPieceToList(i, j, winnerPiecesCoordinates, 0);
                AddWinnerPieceToList(i, j + 1, winnerPiecesCoordinates, 2);
                AddWinnerPieceToList(i, j + 2, winnerPiecesCoordinates, 4);
                AddWinnerPieceToList(i, j + 3, winnerPiecesCoordinates, 6);
                return true;
            }
        }
    }

    // Check vertical win
    for (j = 0; j < 7; j++)
    {
        for (i = 0; i < 3; i++)
        {
            if (board.canvas[i][j] == board.canvas[i + 1][j] &&
                board.canvas[i + 1][j] == board.canvas[i + 2][j] &&
                board.canvas[i + 2][j] == board.canvas[i + 3][j] &&
                board.canvas[i][j] == player.id)
            {
                AddWinnerPieceToList(i, j, winnerPiecesCoordinates, 0);
                AddWinnerPieceToList(i + 1, j, winnerPiecesCoordinates, 2);
                AddWinnerPieceToList(i + 2, j, winnerPiecesCoordinates, 4);
                AddWinnerPieceToList(i + 3, j, winnerPiecesCoordinates, 6);
                return true;
            }
        }
    }

    // Check diagonal win -> left to right
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (board.canvas[i][j] == board.canvas[i + 1][j + 1] &&
                board.canvas[i + 1][j + 1] == board.canvas[i + 2][j + 2] &&
                board.canvas[i + 2][j + 2] == board.canvas[i + 3][j + 3] &&
                board.canvas[i][j] == player.id)
            {
                AddWinnerPieceToList(i, j, winnerPiecesCoordinates, 0);
                AddWinnerPieceToList(i + 1, j + 1, winnerPiecesCoordinates, 2);
                AddWinnerPieceToList(i + 2, j + 2, winnerPiecesCoordinates, 4);
                AddWinnerPieceToList(i + 3, j + 3, winnerPiecesCoordinates, 6);
                return true;
            }
        }
    }

    // Check diagonal win -> right to left
    for (i = 0; i < 3; i++)
    {
        for (j = 6; j > 2; j--)
        {
            if (board.canvas[i][j] == board.canvas[i + 1][j - 1] &&
                board.canvas[i + 1][j - 1] == board.canvas[i + 2][j - 2] &&
                board.canvas[i + 2][j - 2] == board.canvas[i + 3][j - 3] &&
                board.canvas[i][j] == player.id)
            {
                AddWinnerPieceToList(i, j, winnerPiecesCoordinates, 0);
                AddWinnerPieceToList(i + 1, j - 1, winnerPiecesCoordinates, 2);
                AddWinnerPieceToList(i + 2, j - 2, winnerPiecesCoordinates, 4);
                AddWinnerPieceToList(i + 3, j - 3, winnerPiecesCoordinates, 6);
                return true;
            }
        }
    }

    return false;
}