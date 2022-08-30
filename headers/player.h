typedef struct
{
    int id;
    int numberOfPieces;
} Player;

int CheckLocationInColumn(Board board, int columnNumber);
void DrawTurn(Player player, Texture2D pieceTexture, int *position, float scaleFactor, Texture2D boardTexture, Texture2D highlitePieceTexture, int nearestPossibleRow);
void Play(Player player, Texture2D pieceTexture, Board *board, Texture2D boardTexture, Texture2D highlitePieceTexture, int *turn, int *position, Sound coinSound);


int CheckLocationInColumn(Board board, int columnNumber)
{
    int i;

    for (i = 0; i < 6; i++)
    {
        if (board.canvas[i][columnNumber] != 0)
        {
            return i - 1;
        }
    }

    return 5;
}

void DrawTurn(Player player, Texture2D pieceTexture, int *position, float scaleFactor, Texture2D boardTexture, Texture2D highlitePieceTexture, int nearestPossibleRow)
{
    int x, y;
    int boardX, boardY;
    int space;

    int highliteX, highliteY;

    space = 5;

    boardX = GetBoardX(boardTexture, scaleFactor);
    boardY = GetBoardY(boardTexture, scaleFactor);

    x = boardX + scaleFactor * space + scaleFactor * (*position) * (space + 9);
    y = GetScreenHeight() - scaleFactor * (boardTexture.height + 20);

    DrawTextureEx(pieceTexture, (Vector2){x, y}, 0, scaleFactor, RAYWHITE);

    highliteX = x;
    highliteY = boardY + scaleFactor * space + scaleFactor * nearestPossibleRow * (space + 9);

    if (nearestPossibleRow >= 0)
        DrawTextureEx(highlitePieceTexture, (Vector2){highliteX, highliteY}, 0, scaleFactor, RAYWHITE);
}

void Play(Player player, Texture2D pieceTexture, Board *board, Texture2D boardTexture, Texture2D highlitePieceTexture, int *turn, int *position, Sound coinSound)
{
    float scaleFactor = 6;
    int nearestPossibleRow;

    if ((*position) > 6)
        (*position) = 6;

    else if (*position < 0)
        (*position) = 0;

    if ((*position) >= 0 && (*position) <= 6)
    {
        if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
        {
            (*position) += 1;
        }

        if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
        {
            (*position) -= 1;
        }
    }

    nearestPossibleRow = CheckLocationInColumn(*board, *position);
    DrawTurn(player, pieceTexture, position, scaleFactor, boardTexture, highlitePieceTexture, nearestPossibleRow);

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER))
    {
        if (player.id == 1)
        {
            nearestPossibleRow = CheckLocationInColumn(*board, *position);

            if (nearestPossibleRow >= 0)
            {
                (*board).canvas[nearestPossibleRow][*position] = 1;
                PlaySound(coinSound);

                (*turn) = 2;
            }
        }

        else if (player.id == 2)
        {
            nearestPossibleRow = CheckLocationInColumn(*board, *position);

            if (nearestPossibleRow >= 0)
            {
                (*board).canvas[nearestPossibleRow][*position] = 2;
                PlaySound(coinSound);

                (*turn) = 1;
            }
        }
    }
}
